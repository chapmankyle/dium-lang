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
#include <string>

#define ESC                      "\033["
#define BOLD                     "1;"
#define ASCII_RESET              ESC "m"

#define BLACK                    "30m"
#define RED                      "31m"
#define GREEN                    "32m"
#define YELLOW                   "33m"
#define BLUE                     "34m"
#define MAGENTA                  "35m"
#define CYAN                     "36m"
#define WHITE                    "37m"

#define HIGH_BLACK               "90m"
#define HIGH_RED                 "91m"
#define HIGH_GREEN               "92m"
#define HIGH_YELLOW              "93m"
#define HIGH_BLUE                "94m"
#define HIGH_MAGENTA             "95m"
#define HIGH_CYAN                "96m"
#define HIGH_WHITE               "97m"

#define ASCII_BLACK              ESC BLACK
#define ASCII_RED                ESC RED
#define ASCII_GREEN              ESC GREEN
#define ASCII_YELLOW             ESC YELLOW
#define ASCII_BLUE               ESC BLUE
#define ASCII_MAGENTA            ESC MAGENTA
#define ASCII_CYAN               ESC CYAN
#define ASCII_WHITE              ESC WHITE

#define ASCII_BOLD_BLACK         ESC BOLD BLACK
#define ASCII_BOLD_RED           ESC BOLD RED
#define ASCII_BOLD_GREEN         ESC BOLD GREEN
#define ASCII_BOLD_YELLOW        ESC BOLD YELLOW
#define ASCII_BOLD_BLUE          ESC BOLD BLUE
#define ASCII_BOLD_MAGENTA       ESC BOLD MAGENTA
#define ASCII_BOLD_CYAN          ESC BOLD CYAN
#define ASCII_BOLD_WHITE         ESC BOLD WHITE

#define ASCII_HIGH_BLACK         ESC HIGH_BLACK
#define ASCII_HIGH_RED           ESC HIGH_RED
#define ASCII_HIGH_GREEN         ESC HIGH_GREEN
#define ASCII_HIGH_YELLOW        ESC HIGH_YELLOW
#define ASCII_HIGH_BLUE          ESC HIGH_BLUE
#define ASCII_HIGH_MAGENTA       ESC HIGH_MAGENTA
#define ASCII_HIGH_CYAN          ESC HIGH_CYAN
#define ASCII_HIGH_WHITE         ESC HIGH_WHITE

#define ASCII_BOLD_HIGH_BLACK    ESC BOLD HIGH_BLACK
#define ASCII_BOLD_HIGH_RED      ESC BOLD HIGH_RED
#define ASCII_BOLD_HIGH_GREEN    ESC BOLD HIGH_GREEN
#define ASCII_BOLD_HIGH_YELLOW   ESC BOLD HIGH_YELLOW
#define ASCII_BOLD_HIGH_BLUE     ESC BOLD HIGH_BLUE
#define ASCII_BOLD_HIGH_MAGENTA  ESC BOLD HIGH_MAGENTA
#define ASCII_BOLD_HIGH_CYAN     ESC BOLD HIGH_CYAN
#define ASCII_BOLD_HIGH_WHITE    ESC BOLD HIGH_WHITE

/* Position in the source file */
struct SourcePosition {
	int line = 1;
	int column = 1;
};

extern SourcePosition position;
extern std::string sname;

/**
 * Formats a string.
 * @param fmt Format to apply.
 * @param ... Variable arguments.
 */
template <typename ...Args>
static std::string _customFormat(const char *fmt, Args... args) {
	int sizeFormatted = std::snprintf(nullptr, 0, fmt, args...) + 1;
	if (sizeFormatted <= 0) {
		return "";
	}

	auto size = static_cast<size_t>(sizeFormatted);
	std::unique_ptr<char[]> buffer(new char[size]);
	std::snprintf(buffer.get(), size, fmt, args...);
	return std::string(buffer.get(), buffer.get() + size - 1);
}

/**
 * Prints to the standard error output.
 * @param pre Prefix to apply.
 * @param pos Position in the source file.
 * @param fmt Format to apply.
 * @param ... Variable arguments.
 */
template <typename ...Args>
static void _customPrint(const char *pre, const SourcePosition *pos, const char *fmt, Args... args) {
	std::string message = "";

	if (sname.length() > 0) {
		message += _customFormat("%s%s:%s", ASCII_BOLD_WHITE, sname.c_str(), ASCII_RESET);
	}

	if (pos != nullptr) {
		message += _customFormat(" %s%d:%d%s", ASCII_BOLD_WHITE, pos->line, pos->column, ASCII_RESET);
	}

	if (pre != nullptr) {
		message += _customFormat(" %s ", pre);
	} else {
		message += " ";
	}

	message += _customFormat(fmt, args...);
	std::cerr << message << std::endl;
}

/**
 * Displays an error message with the current position prepended.
 * @param fmt Formatted string.
 * @param ... Variable arguments.
 */
template <typename ...Args>
void printErr(const char *fmt, Args... args) {
	const char *pre = ASCII_BOLD_RED "Error:" ASCII_RESET;
	_customPrint(pre, &position, fmt, args...);
	exit(2);
}

/**
 * Displays a warning message with the current position prepended.
 * @param fmt Formatted string.
 * @param ... Variable arguments.
 */
template <typename ...Args>
void printWarn(const char *fmt, Args... args) {
	const char *pre = ASCII_BOLD_YELLOW "Warning:" ASCII_RESET;
	_customPrint(pre, &position, fmt, args...);
	exit(2);
}

#endif // ERROR_HPP
