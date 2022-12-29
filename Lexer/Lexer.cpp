// Lexer.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "Lexer.h"
#include <iostream>

Lexer::Lexer(std::istream& in)
{
	this->buff.filecontent = "";
	char ch;
	while(in.get(ch) && in.good()) {
		//in.get(ch);
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
			res.value = substring(this->buff.filecontent,this->buff.lexeme, this->buff.lexeme + forward);
			this->buff.lexeme += forward;
			return res;
		}
	}
	return errorHandling(this->buff);
}

std::vector<Token> Lexer::getTokens()
{
	std::vector<Token> res;
	while(buff.lexeme<buff.filecontent.size()){
		auto t = getNextToken();
		if(t.type == TokenType::IGNORE) continue;
		if(t.type == TokenType::END_OF_FILE) break;
		res.push_back(t);
	}
	return res;
}

Token Lexer::errorHandling(Buffor& buff)
{
	std::cout <<"Unexpected character on "<< buff.lexeme <<"";
	std::cout<< " [ "<<buff[0] << " ]\n\t: ";
	std::cout<<buff.range(-5,5)<<std::endl;
	exit(-2);
}

bool Lexer::isNextToken()
{
	return false;
}

Lexer::Builder::Builder()
{
}

Lexer::Builder& Lexer::Builder::addToken(Regex match, TokenType type)
{
	vec.push_back(std::make_pair(match, type));
	return *this;
}

Lexer Lexer::Builder::build(std::istream& in)
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
	return true;
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
	return true;
}

bool Comment(const Buffor& buff, int& i)
{
	if(buff[0] == '['){
		for(i=0;i+buff.lexeme < buff.filecontent.size();i++){
			if(buff[i-1]==']') return true;
		}
	}
	return false;
}

char Buffor::operator[](int a) const
{
	return this->filecontent[lexeme + a];
}

int64_t max(int64_t a,int64_t b){
	return (a>b)?a:b;
}

int64_t min(int64_t a,int64_t b){
	return (a<b)?a:b;
}

std::string Buffor::range(int a, int b) const
{
	a = max(this->lexeme+a,0);
	b = min(this->lexeme+b,this->filecontent.size());
	return substring(this->filecontent,a,b);
}
