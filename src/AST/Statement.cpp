/*
 * Statement.cpp
 *
 *  Created on: May 19, 2016
 *      Author: mitthy
 */

#include "AST/Statement.h"
#include <iostream>
#include <vector>
#include <string>
#include "Exceptions.h"
using namespace AST;
using namespace std;
DeclareVariableNode::DeclareVariableNode(vector<VariableNode*>* declaredVar) :
		vec(declaredVar), arrSize(0), isArray(false) {

}
DeclareVariableNode::DeclareVariableNode(vector<VariableNode*>* declaredVar,
		size_t arrSize) :
		vec(declaredVar), arrSize(arrSize), isArray(true) {

}
void DeclareVariableNode::printNode() const {
	VariableNode* firstVar = (*vec)[0];
	auto typePtr = ExprType::makeType(firstVar->getType());
	cout << "Declaracao de ";
	if(isArray) {
		cout <<"arranjo " << typePtr->getTypeNameMasculino() << " de tamanho " << arrSize;
	}
	else {
		cout << "variavel " << typePtr->getTypeName();
	}
	cout << ":";
	string prefix = " ";
	for (auto& var : *(vec)) {
		cout << prefix << var->getName();
		prefix = ", ";
	}
}

IfNode::IfNode(ExpressionNode* condition, BlockNode* thenNode,
		BlockNode* elseNode) :
		condition(condition), thenNode(thenNode), elseNode(elseNode) {
	if (condition->getType() != TBOOL) {
		throw InvalidType(condition->getType());
	}
}

IfNode::IfNode(ExpressionNode* condition, BlockNode* then) :
		condition(condition), thenNode(then), elseNode(nullptr) {
	if (condition->getType() != TBOOL) {
		throw InvalidType(condition->getType());
	}
}

void IfNode::printNode() const {
	cout << "if (";
	condition->printNode();
	cout << ")" << endl;
	cout << "then " << endl;
	thenNode->printNode();
	if (elseNode) {

		cout << "else " << endl;
		elseNode->printNode();
	}
	cout << "end if";
}

DefineVariableNode::DefineVariableNode(VariableNode* var, ExpressionNode* value) : var(var), expr(value) {
	if(var->isArray()) {
		throw InvalidType(TERROR);
	}
}

void DefineVariableNode::printNode() const {
	cout << "Atribuicao de valor para ";
	var->printNode();
	cout << ": ";
	expr->printNode();
}


WhileNode::WhileNode(ExpressionNode* condition, BlockNode* statements) : condition(condition), statements(statements){
	if(condition->getType() != TBOOL) {
		throw InvalidType(condition->getType());
	}
}


void WhileNode::printNode() const {
	cout << "While ";
	condition->printNode();
	cout << endl << "do" << endl;
	statements->printNode();
	cout << "End while";
}