/**
 * @file       lexer.cpp
 * @brief      Implementation of the lexer
 * @copyright  Copyright (c) 2022-present
 * @author     Kyle Chapman
 * @date       2022-07-24
 */

#include <cctype>
#include "error.hpp"
#include "lexer.hpp"

/* Single reserved word */
struct ReservedWord {
	const char *word;  /* Actual word */
	TokenType   type;  /* Token type */
};

/* List of reserved words */
static ReservedWord reservedWords[] = {
	{ "and",      TOK_AND },
	{ "bool",     TOK_BOOL },
	{ "break",    TOK_BREAK },
	{ "char",     TOK_CHAR },
	{ "continue", TOK_CONTINUE },
	{ "dec",      TOK_DEC },
	{ "else",     TOK_ELSE },
	{ "elsif",    TOK_ELSIF },
	{ "exit",     TOK_EXIT },
	{ "false",    TOK_FALSE },
	{ "for",      TOK_FOR },
	{ "func",     TOK_FUNC },
	{ "if",       TOK_IF },
	{ "in",       TOK_IN },
	{ "num",      TOK_NUM },
	{ "or",       TOK_OR },
	{ "print",    TOK_PRINT },
	{ "println",  TOK_PRINTLN },
	{ "range",    TOK_RANGE },
	{ "return",   TOK_RETURN },
	{ "string",   TOK_STR },
	{ "true",     TOK_TRUE },
	{ "void",     TOK_VOID },
	{ "while",    TOK_WHILE }
};

#define NUM_RESERVED_WORDS (sizeof(reservedWords) / sizeof(ReservedWord))
#define MAX_STR_LEN 1024

/* Source file */
static std::ifstream srcFile;

/* Current character in the source file */
static char currChar;

/* Position inside the source file */
SourcePosition position;


bool init(const char *path) {
	srcFile.open(path);

	// File could not be opened
	if (!srcFile || !srcFile.is_open()) {
		// TODO: Output error saying file could not be opened
		return false;
	}

	position.line = 1;
	position.column = 0;
	nextChar();
	return true;
}

void close() {
	srcFile.close();
}

bool isNewLine(const char c) {
	if (c == '\n' || c == '\r') {
		return true;
	}

	return false;
}

void nextChar() {
	// Do nothing if we have no more characters to read
	if (srcFile.eof()) {
		return;
	}

	char last = currChar;
	srcFile.get(currChar);

	if (isNewLine(last)) {
		position.line += 1;
		position.column = 0;
	} else {
		position.column += 1;
	}
}

void skipComment(bool single) {
	// Only need to read to end of current line (single-line comment)
	if (single && currChar == '/') {
		while (!isNewLine(currChar) && !srcFile.eof()) {
			nextChar();
		}
		return;
	}

	// Take away 2 from column since the multi-line comment is 2 characters long "/-"
	SourcePosition start{ position.line, position.column - 2 };
	bool closed = false;

	// Keep checking characters while the comment is not closed
	while (!closed) {
		if (srcFile.eof()) {
			position = start;
			printErr("Comment not closed");
			return;
		}

		// Could close the comment (-/)
		if (currChar == '-') {
			nextChar();
			if (currChar == '/') {
				nextChar();
				closed = true;
				break;
			}
			continue;
		}

		// Could be a nested comment (/-)
		if (currChar == '/') {
			nextChar();
			if (currChar == '-') {
				nextChar();
				skipComment(false);
			}
			continue;
		}

		nextChar();
	}
}

void getToken(Token *token) {
	// Reached the end of the file before even starting
	if (srcFile.eof()) {
		token->type = TOK_EOF;
		return;
	}

	// Skip whitespace
	while (isspace(currChar)) {
		nextChar();

		// Reached the end of file without reading any actual tokens
		if (srcFile.eof()) {
			token->type = TOK_EOF;
			return;
		}
	}

	if (isdigit(currChar)) {
		// TODO: Process number
	} else if (isalnum(currChar) || currChar == '_') {
		// TODO: Process word
	} else {
		switch (currChar) {
		case '"':
			nextChar();
			// TODO: Process string
			break;
		case '\'':
			nextChar();
			// TODO: Process character
			break;
		case '=':
			nextChar();
			if (currChar == '>') {
				token->type = TOK_ARROW;
				nextChar();
			} else {
				token->type = TOK_EQ;
			}
			break;
		case '>':
			nextChar();
			if (currChar == '=') {
				token->type = TOK_GE;
				nextChar();
			} else {
				token->type = TOK_GT;
			}
			break;
		case '<':
			nextChar();
			if (currChar == '=') {
				token->type = TOK_LE;
				nextChar();
			} else {
				token->type = TOK_LT;
			}
			break;
		case '!':
			nextChar();
			if (currChar == '=') {
				token->type = TOK_NE;
				nextChar();
			} else {
				token->type = TOK_NOT;
			}
			break;
		case '-':
			token->type = TOK_MINUS;
			nextChar();
			break;
		case '+':
			token->type = TOK_PLUS;
			nextChar();
			break;
		case '/':
			nextChar();
			if (currChar == '-') {
				nextChar();
				skipComment(false);
				getToken(token);
			} else if (currChar == '/') {
				skipComment(true);
				getToken(token);
			} else {
				token->type = TOK_DIV;
			}
			break;
		case '*':
			token->type = TOK_MUL;
			nextChar();
			break;
		case '%':
			token->type = TOK_MOD;
			nextChar();
			break;
		case '.':
			token->type = TOK_DOT;
			nextChar();
			break;
		case '[':
			nextChar();
			if (currChar == ']') {
				token->type = TOK_ARRAY;
				nextChar();
			} else {
				token->type = TOK_LBRACK;
			}
			break;
		case ']':
			token->type = TOK_RBRACK;
			nextChar();
			break;
		case ',':
			token->type = TOK_COMMA;
			nextChar();
			break;
		case '(':
			token->type = TOK_LPAR;
			nextChar();
			break;
		case ')':
			token->type = TOK_RPAR;
			nextChar();
			break;
		default:
			printErr("Illegal character '%c' (ASCII #%d) found", currChar, currChar);
			break;
		}
	}
}
