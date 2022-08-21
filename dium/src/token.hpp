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
#include <string>
#include <optional>

/** Maximum length of an identifier */
#define MAX_ID_LENGTH 32

/** Types of tokens that we recognise */
enum TokenType : int32_t {

	TOK_EOF = 0,   /* end-of-file */
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
	TOK_ASSIGN,    /* assigns a value to a variable, '=' */
	TOK_EQ,        /* is equal to, '==' */
	TOK_GE,        /* greater than equal to */
	TOK_GT,        /* greater than */
	TOK_LE,        /* less than equal to */
	TOK_LT,        /* less than */
	TOK_NE,        /* not equal */
	TOK_NOT,       /* not */

	/* Arithmetic operators */
	TOK_MINUS,
	TOK_PLUS,
	TOK_DIV,
	TOK_MUL,
	TOK_MOD,

	/* Non-alphabetic characters */
	TOK_AT,        /* @, used for array indexing (e.g. arr@1, which is the value at position 1 inside array `arr`) */
	TOK_DOT,       /* . */
	TOK_LBRACK,    /* left bracket '[' */
	TOK_RBRACK,    /* right bracket ']' */
	TOK_COMMA,     /* , */
	TOK_LPAR,      /* left parenthesis '(' */
	TOK_RPAR,      /* right parenthesis ')' */
	TOK_LCURL,     /* left curly brace '{' */
	TOK_RCURL,     /* right curly brace '}' */
	TOK_ARROW,     /* return type '=>' */

	TOK_NONE

};

/** Token data type */
struct Token {
	/** Type of the token */
	TokenType type;

	/** Identifier */
	std::optional<std::string> identifier;

	/** Value (for strings) */
	std::optional<std::string> string;

	/** Value (for characters) */
	std::optional<char> character;

	/** Value (for numbers) */
	std::optional<int> ivalue;

	/** Value (for decimals) */
	std::optional<double> dvalue;
};

/**
 * Returns a string representation of the token type.
 * @param type Type of token to get the string representation of.
 * @returns String representing the token type.
 */
const char *getTokenString(TokenType type);

#endif // TOKEN_HPP
