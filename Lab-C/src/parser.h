#ifndef MATH_LOG_1_PARSER_H
#define MATH_LOG_1_PARSER_H

struct ast* ast_parse(char* string);

void parse_header(
        const char* src,
        struct ast** assumptions,
        size_t* num_assumptions,
        struct ast** res
);

#endif //MATH_LOG_1_PARSER_H
