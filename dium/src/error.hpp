/**
 * @file       error.hpp
 * @brief      Definitions for error reporting
 * @copyright  Copyright (c) 2022-present
 * @author     Kyle Chapman
 * @date       2022-07-24
 */

#pragma once

#ifndef ERROR_HPP
#define ERROR_HPP

#include <iostream>

/* Position in the source file */
struct SourcePosition {
	int line;
	int column;
};

extern SourcePosition position;

/**
 * Displays an error message.
 * @param fmt Format string.
 * @param ... Variable arguments to the format string.
 */
void eprint(const char *fmt, ...);

/**
 * Displays a warning message with the current position prepended.
 * @param fmt Format string.
 * @param ... Variable arguments to the format string.
 */
void wprint(const char *fmt, ...);

/**
 * Displays an error message with the current position prepended.
 * @param fmt Format string.
 * @param ... Variable arguments to the format string.
 */
void peprint(const char *fmt, ...);

/**
 * Displays a warning message with the current position prepended.
 * @param fmt Format string.
 * @param ... Variable arguments to the format string.
 */
void pwprint(const char *fmt, ...);

#endif // ERROR_HPP
