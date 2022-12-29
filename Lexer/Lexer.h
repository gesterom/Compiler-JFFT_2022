#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#include<string>
#include <vector>
#include <functional>
#include <fstream>

enum class TokenType{
	END_OF_FILE,
	IGNORE,
	ERROR,
	LITERAL,
	OPERATOR,
	COMMPARE,
	ASSIGN,
	ID,
	KEYWORD,
	SEMICOLON,
	PARENTHESIS,
	COMMA
};

struct Token {
	TokenType type = TokenType::END_OF_FILE;
	std::string value;
};

struct Buffor {
	public:
	std::string filecontent;
	uint32_t lexeme = 0;
	char operator[](int a) const;
	std::string range(int a,int b) const;
};

typedef std::function<bool(const Buffor&, int&)> Regex;

Regex Keyword(std::string str);

Regex Operator(std::string str);
Regex Character(char ch);

bool Whitespace(const Buffor& buff, int& i);
bool Identifier(const Buffor& buff,int& i);
bool Integer(const Buffor& buff, int& i);
bool Comment(const Buffor& buff,int& i);

class Lexer {
	Lexer(std::istream& in);
	std::vector<std::pair<Regex, TokenType> > vec;
	Buffor buff;
	public:
		class Builder {
			std::vector<std::pair<Regex, TokenType> > vec;
			public:
			Builder();
			Builder& addToken(Regex match, TokenType type);
			Lexer build(std::istream& in);
		};
	Token getNextToken();
	std::vector<Token> getTokens();
	Token errorHandling(Buffor& buff);
	bool isNextToken();
};