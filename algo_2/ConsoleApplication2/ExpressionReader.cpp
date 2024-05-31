#include "ExpressionReader.h"

enum ExpressionReader::ElementType {
	NUMBER,
	L_BR, R_BR,
	PLUS, MINUS, MUL, DIV,
	UNDEFINED
};

ExpressionReader::Element::Element() : type(UNDEFINED), value(0) {}
ExpressionReader::Element::Element(const ElementType& _type, const BinaryNumber& _value = BinaryNumber(0)) : type(_type), value(_value) {}

//Перегрузка, помогающая с обработкой пустого стека
ExpressionReader::Element ExpressionReader::ElementQueue::getBack() {
	if (this->isEmpty()) {
		return Element();//автоматически создастся UNDEFINED
	}
	return this->last->value;
}

ExpressionReader::Element ExpressionReader::ElementQueue::getFront() {
	if (this->isEmpty()) {
		return Element();//автоматически создастся UNDEFINED
	}
	return this->first->value;
}


ExpressionReader::ElementQueue ExpressionReader::readFromInfix(std::string infixString) {
	ElementQueue expressionQueue;

	for (int i = 0; i < infixString.length(); i++) {
		char letter = infixString[i];
		Element newElement;

		if ('0' <= letter && letter <= '9') {
			Stack<int> digits;
			while ('0' <= infixString[i] && infixString[i] <= '9') {
				digits.pushBack(infixString[i] - '0');
				i++;
			}

			int number = 0;
			int rank = 1;
			while (!digits.isEmpty()) {
				number += digits.popBack() * rank;
				rank *= 10;
			}

			newElement.type = NUMBER;
			newElement.value = BinaryNumber(number);
			newElement.testvalue = std::to_string(number); //удалить
		}
		else if (letter == ' ') {
			continue;
		}
		else {
			newElement.testvalue = std::string(1, letter); //удалить
			switch (letter) {
			case '(':
				newElement.type = L_BR; 
				break;
			case ')':
				newElement.type = R_BR; 
				break;
			case '+':
				newElement.type = PLUS;
				break;
			case '-':
				newElement.type = MINUS;
				break;
			case '*':
				newElement.type = MUL;
				break;
			default:
				throw ER_InvalidSymbol(letter);
				break;
			}
		}

		//UNDEFINED не должен добавиться, т.к. ER_InvalidSymbol выкинет из функции
		expressionQueue.pushBack(newElement);
	}

	return expressionQueue;
}

BinaryNumber ExpressionReader::firstPriority(ElementQueue& remained) {
	BinaryNumber number = secondPriority(remained);

	while (!remained.isEmpty()) {
		Element currentElement = remained.popFront();

		switch (currentElement.type) {
		case PLUS:
		case MINUS:
		case R_BR:
			break;
		default:
			break;
		}
	}
}

BinaryNumber ExpressionReader::calculateFromInfix(const std::string& infixString) {
	ElementQueue expressionQueue = readFromInfix(infixString);

	
}

BinaryNumber ExpressionReader::calculateFromPostfix(const std::string& postfixString) {
	Stack<BinaryNumber> calculatingStack;
	
	for (int i = 0; i < postfixString.length(); i++) {
		char letter = postfixString[i];

		if ('0' <= letter && letter <= '9') {
			Stack<int> digits;
			while ('0' <= postfixString[i] && postfixString[i] <= '9') {
				digits.pushBack(postfixString[i] - '0');
				i++;
			}

			int number = 0;
			int rank = 1;
			while (!digits.isEmpty()) {
				number += digits.popBack() * rank;
				rank *= 10;
			}

			calculatingStack.pushBack(BinaryNumber(number));
		}
		else if (letter == ' ') {
			continue;
		}
		else {
			if (calculatingStack.getSize() < 2) throw ER_Exception("Invalid expression");
			BinaryNumber operand2 = calculatingStack.popBack(); 
			BinaryNumber operand1 = calculatingStack.popBack();

			switch (letter) {
			case '+':
				calculatingStack.pushBack(operand1 + operand2);
				break;
			case '-':
				calculatingStack.pushBack(operand1 - operand2);
				break;
			case '*':
				calculatingStack.pushBack(operand1 * operand2);
				break;
			default: 
				throw ER_InvalidSymbol(letter);
				break;
			}
		}
	}
	
	if (calculatingStack.getSize() > 1) throw ER_Exception("Invalid expression");

	return calculatingStack.getBack();
}


ER_Exception::ER_Exception(const std::string& _message) : message("Error in ExpressionReader: " + _message) {}
std::string ER_Exception::getMessage() {
	return message;
}

ER_InvalidSymbol::ER_InvalidSymbol(const char& _cause) : ER_Exception("invalid symbol \"" + _cause + '\"'), cause(_cause) {}
char ER_InvalidSymbol::getInvalidSymbol() {
	return cause;
}

