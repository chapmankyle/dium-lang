/**
 * @file       main.cpp
 * @brief      Main file that drives the application.
 * @copyright  Copyright (c) 2022-present
 * @author     Kyle Chapman
 * @date       2022-07-28
 */

#include "error.hpp"
#include "lexer.hpp"

#ifdef DIUM_DEBUG
	template<typename ...Args>
	void debugInfo(const char *fmt, Args... args);

	template<typename ...Args>
	void debugStart(const char *fmt, Args... args);

	template<typename ...Args>
	void debugEnd(const char *fmt, Args... args);

	#define DEBUG_START(...) debugStart(__VA_ARGS__)
	#define DEBUG_END(...)   debugEnd(__VA_ARGS__)
	#define DEBUG_INFO(...)  debugInfo(__VA_ARGS__)
#else
	#define DEBUG_START(...)
	#define DEBUG_END(...)
	#define DEBUG_INFO(...)
#endif

/* Current token */
Token token;

/* Name of the source file */
std::string sname;

void parseSource();

/**
 * Main method.
 */
int main(int argc, char *argv[]) {

	const std::string fileName{ "fizzbuzz.dm" };
	const std::string filePath{ "../examples/" + fileName };

	// Initialize source file name
	sname = fileName;

	// Initialize the lexer
	init(filePath.c_str());

	// Start reading
	getToken(&token);
	parseSource();

}

/**
 * Parses the source file.
 */
void parseSource() {
	std::string toPrint;

	while (token.type != TOK_EOF) {
		toPrint = "";

		if (token.identifier) {
			toPrint += (token.type == TOK_ID) ? token.identifier.value() + " " : customFormat("[%s] ", token.identifier.value().c_str());
		}

		if (token.string) {
			toPrint += token.string.value() + " ";
		}

		if (token.character) {
			toPrint += customFormat("%c ", token.character.value());
		}

		if (token.ivalue) {
			toPrint += customFormat("%d ", token.ivalue.value());
		}

		if (token.dvalue) {
			toPrint += customFormat("%d ", token.dvalue.value());
		}

		if (toPrint.length() < 1) {
			toPrint += customFormat("%s ", getTokenString(token.type));
		}

		std::cout << toPrint;
		getToken(&token);
	}

	std::cout << std::endl;
}


#ifdef DIUM_DEBUG

/** Number of spaces to indent when printing */
static int indent = 0;

template<typename ...Args>
void debugStart(const char *fmt, Args... args) {
	debugInfo(fmt, args...);
	indent += 2;
}

template<typename ...Args>
void debugEnd(const char *fmt, Args... args) {
	indent -= 2;
	debugInfo(fmt, args...);
}

template<typename ...Args>
void debugInfo(const char *fmt, Args... args) {
	std::string temp = "";

	for (int idx = 0; idx < indent; idx++) {
		temp += " ";
	}

	temp += fmt;
	std::cout << customFormat(temp.c_str(), args...) << std::endl;
}

#endif
