#include "pch.h"
#include "../../Compiler/Lexer/Lexer.h"

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

class LexerForTests : public ::testing::Test {
protected:
	Lexer::Builder b_lexer;
	LexerForTests() {
		b_lexer = Lexer::Builder()
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

			.addToken(Character(','), TokenType::COMMA)
			.addToken(Character(';'), TokenType::SEMICOLON)
			.addToken(Character('('), TokenType::PARENTHESIS)
			.addToken(Character(')'), TokenType::PARENTHESIS)

			.addToken(Comment, TokenType::IGNORE)
			.addToken(Whitespace, TokenType::IGNORE)
			.addToken(Identifier, TokenType::ID)
			.addToken(Integer, TokenType::LITERAL);
	}
};

TEST_F(LexerForTests, example1) {
	std::stringstream ss(
		R"(
		[b³¹d: druga deklaracja zmiennej a w linii 2]
		PROCEDURE pa(a, a) IS
		VAR c, d
		BEGIN
		c := a;
		a:= c + d;
		END

		PROGRAM IS
		VAR a, b
		BEGIN
		READ a;
		pa(a, b);
		WRITE b;
		END)"
	);
	auto lex = b_lexer.build(ss);
	for (auto i : lex.getTokens()) {
		std::cout << i.value << std::endl;
	}
}