// Compiler.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "../Lexer/Lexer.h"
//int yywrap() { return -1; }
int main(char** args,int argc)
{
	if(argc < 2) return -1;
	std::ifstream file(args[1]);
	Lexer lexer = Lexer::Builder(file)
		.addToken(Keyword("PROCEDURE"), TokenType::KEYWORD)
		.addToken(Keyword("PROGRAM"), TokenType::KEYWORD)
		.addToken(Keyword("IS"), TokenType::KEYWORD)
		.addToken(Keyword("VAR"), TokenType::KEYWORD)
		.addToken(Keyword("BEGIN"), TokenType::KEYWORD)
		.addToken(Keyword("END"), TokenType::KEYWORD)
		.addToken(Keyword("IF"), TokenType::KEYWORD)
		.addToken(Keyword("THEN"), TokenType::KEYWORD)
		.addToken(Keyword("ELSE"), TokenType::KEYWORD)
		.addToken(Keyword("ENDIF"), TokenType::KEYWORD)
		.addToken(Keyword("WHILE"), TokenType::KEYWORD)
		.addToken(Keyword("DO"), TokenType::KEYWORD)
		.addToken(Keyword("ENDWHILE"), TokenType::KEYWORD)
		.addToken(Keyword("REPEAT"), TokenType::KEYWORD)
		.addToken(Keyword("UNTIL"), TokenType::KEYWORD)
		.addToken(Keyword("READ"), TokenType::KEYWORD)
		.addToken(Keyword("WRITE"), TokenType::KEYWORD)

		.addToken(Operator("+"), TokenType::OPERATOR)
		.addToken(Operator("-"), TokenType::OPERATOR)
		.addToken(Operator("*"), TokenType::OPERATOR)
		.addToken(Operator("/"), TokenType::OPERATOR)
		.addToken(Operator("%"), TokenType::OPERATOR)

		.addToken(Operator("="), TokenType::COMMPARE)
		.addToken(Operator("!="), TokenType::COMMPARE)
		.addToken(Operator(">="), TokenType::COMMPARE)
		.addToken(Operator("<="), TokenType::COMMPARE)
		.addToken(Operator(">"), TokenType::COMMPARE)
		.addToken(Operator("<"), TokenType::COMMPARE)

		.addToken(Character(','),TokenType::COMMA)
		.addToken(Character(';'),TokenType::SEMICOLON)

		.addToken(Whitespace,TokenType::IGNORE)
		.addToken(Identifier,TokenType::ID)
		.addToken(Integer,TokenType::LITERAL)
		.build();
    std::cout << "Hello World!\n";
}