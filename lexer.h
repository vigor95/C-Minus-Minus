#pragma once

#include "common.h"
#include "token.h"

class Lexer {
private:
    int cur_line = 1;
    bool space = false;
    Token token;

    void tok_number(std::string::iterator &);
    void tok_ident (std::string::iterator &);
    void tok_string(std::string::iterator &);
    void tok_char  (std::string::iterator &);
    void tok_symbol(std::string::iterator &);
    void skip_line (std::string::iterator &);

    char replace_escape(std::string::iterator &);

public:
    Token run(std::string);
};
