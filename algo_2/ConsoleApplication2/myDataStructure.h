#pragma once

template <typename Type>
class Stack
{
protected:
	struct Node {
	public:
		Type value;
		Node* nextptr;
		Node* prevptr;

		Node(const Type init) : value(init), nextptr(nullptr), prevptr(nullptr) {}
	};

	Node* first;
	Node* last;
	size_t size;
public:
	Stack() : first(nullptr), last(nullptr), size(0) {}

	Stack(const Stack& other) : first(other.first), last(other.last), size(other.size) {}

	bool isEmpty() {
		return first == nullptr;
	}

	void pushBack(Type value) {
		//�������� ������ ��� ������ ��������, ��������� ��������� �� ����
		Node* newNode = new Node(value);
		this->size++;

		if (isEmpty()) {
			first = newNode;
			last = newNode;
			return;
		}

		Node* tempOfLast = last;
		//���� ���������� �������� ��������� �� ���������, �����
		last->nextptr = newNode;
		//�������� ��������� LAST �� ��������� �������
		last = newNode;
		//���� ������ ��������(������� ������ last) ��������� �� ���������� (���������� last - tempOfLast)
		last->prevptr = tempOfLast;
	}

	void removeBack() {
		if (isEmpty()) { return; }
		this->size--;

		Node* temp = last;
		last = temp->prevptr;
		if (last == nullptr) {//����� ����� ���� ��� �������� ���������� ��������
			first = nullptr;
		}
		else {
			last->nextptr = nullptr;
		}
		//������� ������, ������� ��� ���������
		delete temp;
	}

	virtual Type getBack() {
		if (isEmpty()) {
			throw std::exception("list is empty");
		}
		return last->value;
	}

	//������� ������� � ����� ������ � ���������� ��� �����
	Type popBack() {
		Type temp = getBack();
		removeBack();
		return temp;
	}

	size_t getSize() {
		return this->size;
	}
};




template<typename Type> class Queue : public Stack<Type> {
public:
	using Stack<Type>::Node;
	using Stack<Type>::first;
	using Stack<Type>::last;

	void pushFront(Type value) {
		//�������� ������ ��� ������ ��������, ��������� ��������� �� ����
		Node* newNode = new Node(value);
		this->size++;

		if (this->isEmpty()) {
			first = newNode;
			last = newNode;
			return;
		}

		Node* tempOfFirst = first;
		//���� ������� ������� �������� ��������� �� ����� ������, ������� ������ ���������� ��� ����
		first->prevptr = newNode;
		//������� ��������� �� ������ �������
		first = newNode;
		//��� ������ ������� �������� ��������� ������� ������ ������ ������ 
		first->nextptr = tempOfFirst;
	}

	void removeFront() {
		if (this->isEmpty()) { return; }
		this->size--;

		Node* temp = first;
		//��������� first �� ������ �������
		first = temp->nextptr;

		if (first == nullptr) {//����� ����� ���� ��� �������� ���������� ��������
			last = nullptr;
		}
		else {
			//� ������� �������� ������ ��� ����������� ��������
			first->prevptr = nullptr;
		}
		//������� ������, ������� ��� ������
		delete temp;
	}

	virtual Type getFront() {
		if (this->isEmpty()) {
			throw std::exception("list is empty");
		}
		return first->value;
	}

	//������� ������� � ������ ������ � ���������� ��� �����
	Type popFront() {
		Type temp = getFront();
		removeFront();
		return temp;
	}
};
	



