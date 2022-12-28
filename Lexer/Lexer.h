#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#include<string>
#include <vector>
#include <functional>
#include <fstream>

enum class TokenType{
	END_OF_FILE,
	IGNORE,
	LITERAL,
	OPERATOR,
	COMMPARE,
	ID,
	KEYWORD,
	SEMICOLON,
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
};

typedef std::function<bool(const Buffor&, int&)> Regex;

Regex Keyword(std::string str);

Regex Operator(std::string str);
Regex Character(char ch);

bool Whitespace(const Buffor& buff, int& i);
bool Identifier(const Buffor& buff,int& i);
bool Integer(const Buffor& buff, int& i);

class Lexer {
	Lexer(std::istream& in);
	std::vector<std::pair<Regex, TokenType> > vec;
	//std::istream& in;
	Buffor buff;
	public:
		class Builder {
			std::vector<std::pair<Regex, TokenType> > vec;
			std::istream& in;
			public:
			Builder(std::istream& in);
			Builder& addToken(Regex match, TokenType type);
			Lexer build();
		};
	Token getNextToken();
	std::vector<Token> getTokens();
	bool isNextToken();
};