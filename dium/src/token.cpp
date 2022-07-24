/**
 * @file       token.cpp
 * @brief      Implementation for the tokens
 * @copyright  Copyright (c) 2022-present
 * @author     Kyle Chapman
 * @date       2022-07-23
 */

#include <cassert>
#include "token.hpp"

/* Names of each recognized token */
static const char *tokenNames[] = {
	"end-of-file", "identifier", "boolean", "character", "string", "number", "decimal", "array",
	"'and'", "'break'", "'continue'", "'else'", "'elsif'", "'exit'", "'false'", "'for'", "'func'",
	"'if'", "'or'", "'print'", "'println'", "'return'", "'true'", "'void'", "'while'",
	"'='", "'>='", "'>'", "'<='", "'<'", "'!='", "'-'", "'+'", "'/'", "'*'", "'%'",
	"'['", "']'", "','", "'('", "')'", "'=>'"
};

const char *getTokenString(TokenType type) {
	assert(type >= -1 && type < (sizeof(tokenNames) / sizeof(char *)));
	return tokenNames[type];
}
