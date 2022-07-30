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
	std::string word;  /* Actual word */
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

// --------------- function prototypes -------------------------

static void resetToken(Token *token);
static void processWord(Token *token);
static void processNumber(Token *token);
static void skipComment(bool single);

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
		printErr("File could not be opened");
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
		position.column = 1;
	} else {
		position.column += 1;
	}
}

/**
 * Resets the given token.
 * @param token Token to reset.
 */
void resetToken(Token *token) {
	if (token->identifier) {
		token->identifier.reset();
	}

	if (token->string) {
		token->string.reset();
	}

	if (token->character) {
		token->character.reset();
	}

	if (token->ivalue) {
		token->ivalue.reset();
	}

	if (token->dvalue) {
		token->dvalue.reset();
	}
}

void getToken(Token *token) {
	// Reached the end of the file before even starting
	if (srcFile.eof()) {
		token->type = TOK_EOF;
		return;
	}

	// Reset token fields
	resetToken(token);

	// Skip whitespace
	while (isspace(currChar)) {
		nextChar();

		// Reached the end of file without reading any actual tokens
		if (srcFile.eof()) {
			token->type = TOK_EOF;
			return;
		}
	}

	if (isalpha(currChar) || currChar == '_') {
		// Process word
		processWord(token);
	} else if (isdigit(currChar)) {
		// Process number
		processNumber(token);
	} else {
		switch (currChar) {
		case '"':
			// TODO: Process string
			token->type = TOK_STR;
			nextChar();
			break;
		case '\'':
			// TODO: Process character
			token->type = TOK_CHAR;
			nextChar();
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
				token->type = TOK_NONE;
				getToken(token);
			} else if (currChar == '/') {
				skipComment(true);
				token->type = TOK_NONE;
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
		case '{':
			token->type = TOK_LCURL;
			nextChar();
			break;
		case '}':
			token->type = TOK_RCURL;
			nextChar();
			break;
		default:
			printErr("Illegal character '%c' (ASCII #%d) found", currChar, currChar);
			break;
		}
	}
}

/**
 * Processes a word and updates the given token.
 * @param token Token to update after processing.
 */
void processWord(Token *token) {
	std::string word = "";
	int startColumn = position.column;

	int idx = 0;
	while (currChar != ' ' && !srcFile.eof() && (isalnum(currChar) || currChar == '_')) {
		if (idx <= MAX_ID_LENGTH) {
			word += currChar;
			idx += 1;
			nextChar();
		} else {
			position.column = startColumn;
			printErr("Identifier too long (more than 32 characters)");
		}
	}

	// Perform binary search through list of reserved words
	int low = 0;
	int mid = 0;
	int high = sizeof(reservedWords) / sizeof(reservedWords[0]) - 1;
	int cmp = 0;

	while (low <= high) {
		mid = (low + high) / 2;
		cmp = word.compare(reservedWords[mid].word);

		if (cmp < 0) {
			high = mid - 1;
		} else if (cmp > 0) {
			low = mid + 1;
		} else {
			// Found a match, so it is a reserved word
			token->type = reservedWords[mid].type;
			token->identifier = word;
			return;
		}
	}

	// Not a reserved word, so it is an identifier
	token->type = TOK_ID;
	token->identifier = word;
}

/**
 * Processes a number and updates the given token.
 * @param token Token to update after processing.
 */
void processNumber(Token *token) {
	SourcePosition start{ position };

	int number;
	int value;
	int diff;

	value = currChar - '0';
	number = value;
	nextChar();

	// Build up the number until we do not have another number to read
	while (isdigit(currChar)) {
		diff = currChar - '0';

		if (number <= ((INT_MAX - diff) / 10)) {
			number = (10 * value) + diff;
			value = number;
			nextChar();
		} else {
			position = start;
			printErr("Number too large");
		}
	}

	// Update token information
	token->type = TOK_NUM;
	token->ivalue = number;
}

/**
 * Skips comments.
 * @param single `true` if the comment is a single-line comment, `false` if multi-line.
 */
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
