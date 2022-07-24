/**
 * @file       lexer.hpp
 * @brief      Definitions for the implementation of the lexer
 * @copyright  Copyright (c) 2022-present
 * @author     Kyle Chapman
 * @date       2022-07-24
 */

#pragma once

#ifndef LEXER_HPP
#define LEXER_HPP

#include <fstream>
#include "token.hpp"

/**
 * Initialises the lexer.
 * @param path Path to the source file to read from.
 * @returns `true` if the lexer was initialized successfully, `false` otherwise.
 */
bool init(char *path);

/**
 * Closes the lexer and frees all allocated memory.
 */
void close();

/**
 * Checks if the given character is a new line character.
 * @param c Character to check
 * @returns `true` if the character is a new line character, `false` otherwise.
 */
bool isNewLine(const char c);

/**
 * Gets the next character from the source file.
 */
void nextChar();

/**
 * Skips comments.
 * @param single `true` if the comment is a single-line comment, `false` if multi-line.
 */
void skipComment(bool single);

/**
 * Gets the next token from the source file.
 * @param[out] token Next token.
 */
void getToken(Token *token);

#endif // LEXER_HPP
