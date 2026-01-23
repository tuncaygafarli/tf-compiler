#include "ast.h"
#include <stdexcept>

NumberNode::NumberNode(double val) : value(val) {}
double NumberNode::evaluate(SymbolTable& env) const { return value; }

VariableNode::VariableNode(std::string& name) : name(name) {};
double VariableNode::evaluate(SymbolTable& env) const {
	if (env.find(name) != env.end()) {
		return env[name];
	}

	throw std::runtime_error("Undefined variable " + name);
}

AssignmentNode::AssignmentNode(std::string id, std::unique_ptr<ASTNode> rhs_ptr)
    : identifier(std::move(id)), rhs(std::move(rhs_ptr)) {
}

double AssignmentNode::evaluate(SymbolTable& env) const {
    double val = rhs->evaluate(env);
    env[identifier] = val;
    return val;
}

BinOpNode::BinOpNode(char op, std::unique_ptr<ASTNode> left, std::unique_ptr<ASTNode> right)
    : op(op), left(std::move(left)), right(std::move(right)) {
}

double BinOpNode::evaluate(SymbolTable& env) const {
    double l = left->evaluate(env);
    double r = right->evaluate(env);
    switch (op) {
    case '+': return l + r;
    case '-': return l - r;
    case '*': return l * r;
    case '/': return l / r;
    default: return 0;
    }
}