/**
 * @file       main.cpp
 * @brief      Main file that drives the application.
 * @copyright  Copyright (c) 2022-present
 * @author     Kyle Chapman
 * @date       2022-07-28
 */

#include "error.hpp"
#include "lexer.hpp"

/* Current token */
Token token;

/* Name of the source file */
std::string sname;

/**
 * Main method.
 */
int main(int argc, char *argv[]) {

	const std::string fileName{ "fail.dm" };
	const std::string filePath{ "../examples/" + fileName };

	// Initialize source file name
	sname = fileName;

	// Initialize the lexer
	init(filePath.c_str());

	// Start reading
	getToken(&token);

}
