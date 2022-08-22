#ifndef PARSER_H
#define PARSER_H


typedef enum e_code_clean
{
	E_CODE_INIT = 1<<0,
	E_CODE_CLEAN = 1<<1,
	E_CODE_RESET = 1<<2
} e_code_clean;

void exit_clean_parser(void);

#endif