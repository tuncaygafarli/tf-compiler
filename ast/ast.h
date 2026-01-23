#pragma once
#include <iostream>
#include <string>
#include <memory>
#include <map>

using SymbolTable = std::map<std::string, double>;

class ASTNode {
public :
	virtual ~ASTNode() = default;
	virtual double evaluate(SymbolTable& env) const = 0;
};

class NumberNode : public ASTNode {
	double value;
public :
	NumberNode(double val);
	double evaluate(SymbolTable& env) const override;
};

class VariableNode : public ASTNode {
	std::string name;
public:
	VariableNode(std::string& name);
	double evaluate(SymbolTable& env) const override;
};

class AssignmentNode : public ASTNode {
	std::string identifier;
	std::unique_ptr<ASTNode> rhs;	
public:
	AssignmentNode(std::string id, std::unique_ptr<ASTNode> rhs_ptr);
	double evaluate(SymbolTable& env) const override;
};

class BinOpNode : public ASTNode {
	char op;
	std::unique_ptr<ASTNode> left;
	std::unique_ptr<ASTNode> right;
public:
	BinOpNode(char op, std::unique_ptr<ASTNode> left, std::unique_ptr<ASTNode> right);
	double evaluate(SymbolTable& env) const override;
};