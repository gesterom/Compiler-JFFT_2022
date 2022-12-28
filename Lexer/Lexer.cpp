// Lexer.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "Lexer.h"

Lexer::Lexer(std::istream& in)
{
	this->buff.filecontent = "";
	while(in.good()){
		char ch;
		in.get(ch);
		this->buff.filecontent+=ch;
	}
}
std::string  substring(std::string str,int begin,int end){
	std::string res;
	for(int i = begin ; i < end;i++){
		res+=str[i];
	}
	return res;
}
Token Lexer::getNextToken()
{
	for(auto& i : this->vec){
		int forward = this->buff.lexeme;
		if(i.first(this->buff,forward)){
			Token res;
			res.type = i.second;
			res.value = substring(this->buff.filecontent,this->buff.lexeme,forward);
			this->buff.lexeme = forward;
			return res;
		}
	}

	return Token();
}

std::vector<Token> Lexer::getTokens()
{
	return std::vector<Token>();
}

bool Lexer::isNextToken()
{
	return false;
}

Lexer::Builder::Builder(std::istream& in) : in(in)
{
}

Lexer::Builder& Lexer::Builder::addToken(Regex match, TokenType type)
{
	vec.push_back(std::make_pair(match, type));
	return *this;
}

Lexer Lexer::Builder::build()
{
	Lexer res(in);
	res.vec = this->vec;
	return res;
}

Regex Keyword(std::string str)
{
	return [str](const Buffor& buff, int& i) ->bool {
		for (i = 0; i < str.size() && i < buff.filecontent.size(); i++) {
			if (buff[i] != str[i]) return false;
		}
		return true;
	};
}

Regex Operator(std::string str)
{
	return Keyword(str);
}

Regex Character(char ch)
{
	return [ch](const Buffor& buff, int& i)->bool {
		if (buff[0] == ch) {
			i = 1;
			return true;
		}
		return false;
	};
}

bool Whitespace(const Buffor& buff, int& i)
{
	if(buff[0] == ' '
		or buff[0] == '\t'
		or buff[0] == '\n'){
		i = 1;
		return true;
	}
	return false;
}

bool Identifier(const Buffor& buff, int& i)
{
	for (i = 0; i < buff.filecontent.size(); i++) {
		if (buff[i] >= 'a' and buff[i] <= 'z') {
			continue;
		}
		else {
			if (i != 0)
				return true;
			else
				return false;
		}
	}
}

bool Integer(const Buffor& buff, int& i)
{
	for(i = 0 ; i < buff.filecontent.size(); i++){
		if (buff[i] >= '0' and buff[i] <= '9') {
			continue;
		}
		else{
			if (i != 0)
				return true;
			else
				return false;
		}
	}
}

char Buffor::operator[](int a) const
{
	return this->filecontent[lexeme + a];
}
