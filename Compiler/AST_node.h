#pragma once

#include <vector>
#include <string>

class IVisiotr {

};

namespace AST{
class IAST_Node {
	virtual void accept(IVisiotr* visitor)=0;
};

class IExpresion : IAST_Node {

};


class IValue : public IExpresion {

};
class Identifier : public IAST_Node {

};
class Varible : public IValue{
	Identifier* id;
};
class Literal : public IValue {
	std::string value;
};

class Operator : public IExpresion {
	IExpresion* left;
	char op;
	IExpresion* right;
};

class Condision : public IAST_Node {
	enum class Cond{ EQ, NEQ,GT,GE,LT,LE};
	IExpresion* left;
	Cond cond;
	IExpresion* right;
};

class ICommand : public IAST_Node{

};
class Command_Asign : public ICommand {
	Identifier* id;
	IExpresion* exp;
};
class Command_If_Else : public ICommand {
	Condision* con;
	std::vector<ICommand*> then;
	std::vector<ICommand*> otherwise;
};

class Command_While : public ICommand {
	Condision* con;
	std::vector<ICommand*> commands;
};

class Command_RepeatUntil : public ICommand {
	std::vector<ICommand*> commands;
	Condision* con;
};

class Command_ProcedureCall : public ICommand {
	std::strong_ordering name;
	std::vector<Declaration*> arguments;
};
class Command_Write : public ICommand {
	Identifier* id;
};
class Command_Read : public ICommand {
	Identifier* id;
};

class Declaration : public IAST_Node {
	std::vector<Identifier*> ids;
};

class Procedure_head : public IAST_Node{
	Identifier* name;
	std::vector<Declaration*> arguments;
};

class Procedure : public IAST_Node {
	Procedure_head* head;
	std::vector<Declaration*> vars;
	std::vector<ICommand*> commands;
};

class Program_all : public IAST_Node {
	Procedure* main;
	std::vector<Procedure*> procedures;
};

}