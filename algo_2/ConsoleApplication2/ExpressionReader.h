#pragma once
#include <string>
#include "binaryNumber.h"
#include "myDataStructure.h"

class ExpressionReader
{
private:
	enum ElementType;

	struct Element {
		ElementType type;
		BinaryNumber value;

		std::string testvalue;

		Element();

		Element(const ElementType& _type, const BinaryNumber& _value);
	};


	class ElementQueue : public Queue<Element> {
	public:
		Element getBack() override;
		Element getFront() override;
	};

	BinaryNumber firstPriority(ElementQueue& remained);
	BinaryNumber secondPriority(ElementQueue& remained);
	BinaryNumber extractDigit(ElementQueue& remained);

	ElementQueue readFromInfix(std::string infixString);
public:
	BinaryNumber calculateFromInfix(const std::string& infixString);

	BinaryNumber calculateFromPostfix(const std::string& expression);

};

class ER_Exception {
private:
	std::string message;
public:
	ER_Exception(const std::string& _message);
	std::string getMessage();
};



class ER_InvalidSymbol : public ER_Exception{
private:
	char cause;
public:
	ER_InvalidSymbol(const char& _cause);
	char getInvalidSymbol();
};


