// Compiler.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <sstream>
#include "../Lexer/Lexer.h"
//int yywrap() { return -1; }
int main(int argc, char** args)
{

	std::stringstream ss(
		R"(
		[b³¹d: druga deklaracja zmiennej a w linii 2]
		PROCEDURE pa(a, a) IS
		VAR c, d
		BEGIN
		c := a;
		a := c + d;
		END

		PROGRAM IS
		VAR a, b
		BEGIN
		READ a;
		pa(a, b);
		WRITE b;
		END)"
	);

	Lexer lexer = Lexer::Builder()
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

		.addToken(Operator(":="), TokenType::ASSIGN)

		.addToken(Character(','),TokenType::COMMA)
		.addToken(Character(';'),TokenType::SEMICOLON)
		.addToken(Character('('), TokenType::PARENTHESIS)
		.addToken(Character(')'), TokenType::PARENTHESIS)

		.addToken(Comment,TokenType::IGNORE)
		.addToken(Whitespace,TokenType::IGNORE)
		.addToken(Identifier,TokenType::ID)
		.addToken(Integer,TokenType::LITERAL)
		.build(ss);
	for(auto i : lexer.getTokens()){
		std::cout<<i.value<<std::endl;
	}
}