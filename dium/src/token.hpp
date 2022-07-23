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

#include <cstdint>

/** Maximum length of an identifier */
#define MAX_ID_LENGTH 32

/** Types of tokens that we recognise */
enum class TokenType : int32_t {

	_EOF = -1, /* end-of-file */
	ID,        /* identifier */
	BOOL,      /* boolean literal */
	CHAR,      /* character literal */
	STR,       /* string literal */
	NUM,       /* number literal (no decimals) */
	DEC,       /* floating-point literal (decimals) */
	ARRAY,     /* array of any given type */

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
	OR,
	PRINT,
	PRINTLN,
	RETURN,
	TRUE,
	VOID,
	WHILE,

	/* Relational operators */
	EQ,        /* equal */
	GE,        /* greater than equal to */
	GT,        /* greater than */
	LE,        /* less than equal to */
	LT,        /* less than */
	NE,        /* not equal */

	/* Arithmetic operators */
	MINUS,
	PLUS,
	DIV,
	MUL,
	MOD,

	/* Non-alphabetic characters */
	LBRACK,    /* left bracket '[' */
	RBRACK,    /* right bracket ']' */
	COMMA,
	LPAR,      /* left parenthesis '(' */
	RPAR,      /* right parenthesis ')' */
	RET        /* return type '=>' */

};

/** Token data type */
struct Token {
	TokenType    type;                     /* Type of the token */
	char         lexeme[MAX_ID_LENGTH+1];  /* Lexeme (for identifiers) */
	int          value;
	char        *string;
};

/**
 * Returns a string representation of the token type.
 * @param type Type of token to get the string representation of.
 * @returns String representing the token type.
 */
const char *getTokenString(TokenType type);

#endif // TOKEN_HPP
