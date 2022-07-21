/**
 * @file       token.hpp
 * @brief      Data type definitions for the lexer
 * @copyright  Copyright (c) 2022-present
 * @author     Kyle Chapman
 * @date       2022-07-19
 */

#pragma once

#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>

/** Maximum length of an identifier */
#define MAX_ID_LENGTH 32

/** Types of tokens that we recognise */
enum class TokenType {

	_EOF,     /* end-of-file */
	ID,       /* identifier */
	BOOL,     /* boolean literal */
	CHAR,     /* character literal */
	STR,      /* string literal */
	NUM,      /* number literal (no decimals) */
	DEC,      /* floating-point literal (decimals) */

	/* Reserved words */
	AND,
	BREAK,
	CONTINUE,
	ELSE,
	ELSIF,
	EXIT,
	FALSE,
	FOR,
	FUNC,
	IF,
	INFER,
	OR,
	PRINT,
	RETURN,
	TRUE,
	VOID,
	WHILE

};

/** Token data type */
struct Token {
	TokenType    type;                     /* Type of the token */
	char         lexeme[MAX_ID_LENGTH+1];  /* Lexeme (for identifiers) */
	bool         bvalue;                   /* Boolean value (for booleans) */
	int          ivalue;                   /* Numeric value (for integers) */
	double       dvalue;                   /* Decimal value (for floating-point numbers) */
	std::string  svalue;                   /* String value (for strings) */
};

#endif // TOKEN_HPP
