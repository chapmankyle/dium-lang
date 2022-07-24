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
enum TokenType : int32_t {

	TOK_EOF = -1,  /* end-of-file */
	TOK_ID,        /* identifier */
	TOK_BOOL,      /* boolean literal */
	TOK_CHAR,      /* character literal */
	TOK_STR,       /* string literal */
	TOK_NUM,       /* number literal (no decimals) */
	TOK_DEC,       /* floating-point literal (decimals) */
	TOK_ARRAY,     /* array of any given type */

	/* Reserved words */
	TOK_AND,
	TOK_BREAK,
	TOK_CONTINUE,
	TOK_ELSE,
	TOK_ELSIF,
	TOK_EXIT,
	TOK_FALSE,
	TOK_FOR,
	TOK_FUNC,
	TOK_IF,
	TOK_IN,
	TOK_OR,
	TOK_PRINT,
	TOK_PRINTLN,
	TOK_RANGE,
	TOK_RETURN,
	TOK_TRUE,
	TOK_VOID,
	TOK_WHILE,

	/* Relational operators */
	TOK_EQ,        /* equal */
	TOK_GE,        /* greater than equal to */
	TOK_GT,        /* greater than */
	TOK_LE,        /* less than equal to */
	TOK_LT,        /* less than */
	TOK_NE,        /* not equal */

	/* Arithmetic operators */
	TOK_MINUS,
	TOK_PLUS,
	TOK_DIV,
	TOK_MUL,
	TOK_MOD,

	/* Non-alphabetic characters */
	TOK_DOT,       /* . */
	TOK_LBRACK,    /* left bracket '[' */
	TOK_RBRACK,    /* right bracket ']' */
	TOK_COMMA,
	TOK_LPAR,      /* left parenthesis '(' */
	TOK_RPAR,      /* right parenthesis ')' */
	TOK_ARROW      /* return type '=>' */

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
