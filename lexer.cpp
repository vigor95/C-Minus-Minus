#include "lexer.h"
#include "token.h"

Token Lexer::run(std::string source) {
    cur_line = 1;
    space = false;

    for (auto pos = source.begin(); pos != source.end(); pos++) {
        if (isdigit(*pos))
            tok_number(pos);
        else if (*pos == '_' || isalpha(*pos))
            tok_ident(pos);
        else if (isblank(*pos))
            space = true;
        else if (*pos == '\\')
            skip_line(pos);
        else if (*pos == '/' && *(pos + 1) == '/')
            while (*pos != '\n') pos++;
        else if (*pos == '/' && *(pos + 1) == '*') {
            while (!(*pos == '*' && *(pos + 1) == '/')) pos++;
            pos++;
        }
        else if (*pos == '\"')
            tok_string(pos);
        else if (*pos == '\'')
            tok_char(pos);
        else if (*pos == '\n')
            skip_line(pos), cur_line++;
        else
            tok_symbol(pos);
    }
    puts("over");

    token.add_end_tok();

    return token;
}

void Lexer::tok_number(std::string::iterator &pos) {
    std::string number;
    while (1) {
        char c = *pos;
        bool is_float = strchr("eEpP", *(pos - 1)) && strchr("+-", c);
        if (!isdigit(c) && !isalpha(c) && c != '.' && !is_float)
            break;
        number += *pos++;
    }
    pos--;
    token.add_number_tok(number, cur_line, space);
    space = false;
}

void Lexer::tok_ident(std::string::iterator &pos) {
    std::string ident;
    for (; isalpha(*pos) || isdigit(*pos) || *pos == '_'; pos++)
        ident += *pos;
    pos--;
    token.add_ident_tok(ident, cur_line, space);
    space = false;
}

void Lexer::tok_string(std::string::iterator &pos) {
    std::string content;
    for (pos++; *pos != '\"'; pos++)
        content += (*pos == '\\') ? replace_escape(pos) : *pos;

    token.add_string_tok(content, cur_line, space);
    space = false;
}

void Lexer::tok_char(std::string::iterator &pos) {
    if (*(pos + 1) == '\\') {}
    else {
        pos++;
        std::string ch;
        ch = *pos++;
        token.add_char_tok(ch, cur_line, space);
        space = false;
    }
}

void Lexer::tok_symbol(std::string::iterator &pos) {
    std::string op;
    op = *pos;

    if (
        (*pos == '+' && *(pos + 1) == '+') ||
        (*pos == '-' && *(pos + 1) == '-') ||
        (*pos == '&' && *(pos + 1) == '&') ||
        (*pos == '|' && *(pos + 1) == '|') ||
        (*pos == '-' && *(pos + 1) == '>') ||
        (*pos == '.' && *(pos + 1) == '.')
    )
        op += *++pos;

    if (*pos == '.' && *(pos + 1) == '.')
        op += *++pos;
    else if (*(pos + 1) == '=')
        op += *++pos;
    token.add_symbol_tok(op, cur_line, space);
    space = false;
}

void Lexer::skip_line(std::string::iterator &pos) {
    while (*pos != '\n')
        pos++;
}

char Lexer::replace_escape(std::string::iterator &pos) {
    char c = *++pos;
    switch (c) {
        case '\'': case '"': case '?': case '\\':
            return c;
        case 'a': return '\a';
        case 'b': return '\b';
        case 'f': return '\f';
        case 'n': return '\n';
        case 'r': return '\r';
        case 't': return '\t';
        case 'v': return '\v';
    }
    return c;
}
