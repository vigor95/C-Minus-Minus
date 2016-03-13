#include "cic.h"

// 存词法分析的输出，即语法分析的输入
std::vector<Word> word;

static svec end_symbol, split;
static std::map<chars, int> mm;

static std::vector<Word> out;
static chars ch;

static chars lexical_out;

static chars sTs(chars s) {
    if (s == "\\a")	    return iTs(7);
    if (s == "\\b")	    return iTs(8);
    if (s == "\\f")	    return iTs(12);
    if (s == "\\n")	    return iTs(10);
    if (s == "\\r")	    return iTs(13);
    if (s == "\\t")	    return iTs(9);
    if (s == "\\v")	    return iTs(11);
    if (s == "\\\\")	return iTs(92);
    if (s == "\\?") 	return iTs(63);
    if (s == "\'")	    return iTs(39);
    if (s == "\"")	    return iTs(34);
    if (s == "\0")	    return iTs(0);
    if (s[1] == 'x' || s[1] == 'X') {
        return iTs( digit_val(s[2])*16 + digit_val(s[3]) );
    }
    return iTs( digit_val(s[1])*64 + 8*digit_val(s[2]) + digit_val(s[3]) );
}

/*
// number DFA

//  digits         .      digits*    e||E        digit     digits*
// =======> 1(ac) ===>     2(ac)    ======>  3  =======>    4(ac)
//                e||E
//               ======>  3
//                                                 +/-               digit      digits*
//                                            =============>   5   =========>    4(ac)

//    .       digit
// ======> 6 ========>  2

*/

static chars number(chars st, int pos, int state) {
    unsigned i;
    st += "$";

    for (i = pos + 1; i < st.length(); i++)
    switch (state) {
        case 1:
            if (digit(st[i]) == 1)				{ state = 1; break; }
            if (st[i] == '.')	 				{ state = 2; break; }
            if (st[i] == 'e' || st[i] == 'E')	{ state = 3; break; }
            return st.substr(pos, i-pos);
        case 2:
            if (digit(st[i]) == 1) 				{ state = 2; break; }
            if (st[i] == 'e' || st[i] == 'E') 	{ state = 3; break; }
            return st.substr(pos, i-pos);
        case 3:
            if (st[i] == '+')					{ state = 5; break; }
            if (st[i] == '-')					{ state = 5; break; }
            if (digit(st[i]) == 1) 				{ state = 4; break; }
            return "<error>";
        case 4:
            if (digit(st[i]) == 1) 				{ state = 4; break; }
            return st.substr(pos, i-pos);
        case 5:
            if (digit(st[i]) == 1) 				{ state = 4; break; }
            return "<error>";
        case 6:
            if (digit(st[i]) == 1) 				{ state = 2; break; }
            return "<error>";
    }
    return st.substr(pos, i-pos);
}

/*
// ident DFA

//    letter_             letter_ / digit     letter_ / digit
// =============> 1(ac) ==================>        2(ac)

*/

static chars ident(chars st, int pos) {
    unsigned i;
    st += "$";
    for (i = pos + 1; i < st.length(); i++) {
        if (_alpha(st[i]) == 1) continue;
        if (digit(st[i]) == 1) continue;
        return st.substr(pos, i-pos);
    }
    return st.substr(pos, i-pos);
}

// 按照关键字、常量、变量等分离开
static std::vector<Word> wordSplit(chars str, int line) {
    unsigned i, j, k;
    chars ss;
    std::vector<Word> tmp;
    for (i = 0; i < str.length(); i++) {
        if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' ||
            str[i] == '\0' || str[i] == '\r') continue;
        if (str[i] == '\'') {   //char
            if (i+2 < str.length() && str[i+2] == '\'') {
                j = i + 2;
                ss = str.substr(i, j-i+1);
                tmp.push_back(Word("<number>", iTs(str[i+1]), line));
                i = j;
            }
            else if (i+3 < str.length() && str[i+1] == '\\' &&
                    str[i+3] == '\'') {
                j = i + 3;
                ss = str.substr(i+1, j-i-1);
                tmp.push_back(Word("<number>", sTs(ss), line));
                i = j;
            }
            else if (i+5 < str.length() && str[i+1] == '\\' &&
                    str[i+5] == '\'') {
                j = i + 5;
                ss = str.substr(i+1, j-i-1);
                tmp.push_back(Word("<number>", sTs(ss), line));
                i = j;
            }
            else {
                tmp.push_back(Word("error", str.substr(i), line));
                return tmp;
            }
        }
        else if (str[i] == '"') {		  // string
            for (j = i + 1; j < str.length(); j++)
                if (str[j] == '"') break;
            if (j >= str.length()) {
                tmp.push_back(Word("error", str.substr(i), line));
                return tmp;
            }
            ss = str.substr(i, j-i+1);
            for (k = 0; k < ss.length(); k++) if (ss[k] == ' ') ss[k] = 8;
            tmp.push_back(Word("<string>", ss, line));
            i = j;
        }
        else if (digit(str[i])) {    // number
            ss = number(str, i, 1);
            if (ss == "<error>") {
                tmp.push_back(Word("error", str.substr(i), line));
                return tmp;
            }
            tmp.push_back(Word("<number>", ss, line));
            i += ss.length() - 1;
        }
        else if (str[i] == '.' && i+1 < str.length() && digit(str[i+1])) {         // number
            ss = number(str, i, 6);
            if (ss == "<error>") {
                tmp.push_back(Word("error", str.substr(i), line));
            }
            else {
                tmp.push_back(Word("<number>", ss, line));
                i += ss.length() - 1;
            }
        }
        else if (_alpha(str[i])) {   // ident || keyword
            ss = ident(str, i);
            if (ss == "<error>") {
                tmp.push_back(Word("<error>", str.substr(i), line));
                return tmp;
            }

            if (mm.find(ss) != mm.end()) {
                tmp.push_back(Word("<keyword>", ss, line));
            }
            else {
                tmp.push_back(Word("<ident>", ss, line));
            }
            i += ss.length() - 1;
        }
        else {                       // keyword
            for (j = 0; j < split.size(); j++)
                if (str.length() - i >= split[j].length() &&
                        str.substr(i, split[j].length()) == split[j])
                    break;
            if (j < split.size()) {
                tmp.push_back(Word( "<keyword>", split[j], line));
                i += split[j].length() - 1;
            }
            else {
                tmp.push_back(Word("<error>", str.substr(i), line));
                return tmp;
            }
        }
    }
    return tmp;
}

static std::vector<Word> solve(chars str, int kk) {
    std::vector<Word> ret = wordSplit(str, kk);
    return ret;
}

static void readTerms() {
#include "gram.init"
    std::istringstream is;
    chars tmp, str;

    end_symbol.clear();
    mm.clear();

    for (int i = 0; ; i++) {
        str = gram_init[i];
        if (str.length() == 0) break;
        is.clear();
        is.str(str);
        while (is >> tmp) {
            if (!(tmp.length() > 2 && tmp[0] == '<' &&
                tmp[tmp.length()-1] == '>') && tmp != "::="
                    && tmp != "null") {
                if (mm.find(tmp) == mm.end()) {
                    end_symbol.push_back(tmp);
                    mm[tmp] = 1;
                }
            }
        }
    }
}

static int error() {
    unsigned j;
    int success = 0;
    for (j = 0; j < word.size(); j++) {
        if (word[j].type == "<error>")
            success = 1;
    }
    if (success) {
        for (j = 0; j < word.size(); j++) {
            if (word[j].type == "<error>")
                printf("lexical error: %s: %d: %s\n",
                       source[word[j].line].file.c_str(), source[word[j].line].line,
                        word[j].val.c_str());
        }
    }
    return success;
}

int lex() {
    lexical_out  = "lex.out";

    unsigned i, j, k;
    chars ss;

    readTerms();

    split.clear();
    for (i = 0; i < end_symbol.size(); i++) {
        ss = end_symbol[i];
        if (_alpha(ss[0]) == 0)
            split.push_back(ss);
    }
    for (i = 0; i < split.size(); i++) {
        for (j = i + 1; j < split.size(); j++)
            if (split[i].length() < split[j].length()) {
                ss = split[i];
                split[i] = split[j];
                split[j] = ss;
            }
    }

    auto fp = fopen(lexical_out.c_str(), "w");

    word.clear();
    for (i = 0; i < source.size(); i++) {
        out = solve(source[i].code, i);
        k = 0;
        for (j = 0; j < out.size(); j++) {
            if (out[j].val == "EOF") {
                out[j].val = "-1"; out[j].type = "<number>";
            }
            if (out[j].val == "NULL") {
                out[j].val = "0"; out[j].type = "<number>";
            }
            if (out[j].val == "true") {
                out[j].val = "1"; out[j].type = "<number>";
            }
            if (out[j].val == "false") {
                out[j].val = "0"; out[j].type = "<number>";
            }
            if (out[j].val == "short")	 out[j].val = "char";
            if (out[j].val == "long")	 out[j].val = "int";
            if (out[j].val == "float")	 out[j].val = "double";
            if (out[j].val == "signed")	 out[j].val = "int";
            if (out[j].val == "unsigned") out[j].val = "int";

            fprintf(fp, "%d: %s %s\n", out[j].line + 1,
                    out[j].type.c_str(), out[j].val.c_str());
            k = 1;
            word.push_back(out[j]);
        }
    }
    fclose(fp);
    return error();
}
