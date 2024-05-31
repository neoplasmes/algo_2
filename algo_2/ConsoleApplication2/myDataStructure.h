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
		//Выделили память для нового элемента, сохранили указатель на него
		Node* newNode = new Node(value);
		this->size++;

		if (isEmpty()) {
			first = newNode;
			last = newNode;
			return;
		}

		Node* tempOfLast = last;
		//дали последнему элементу указатель на следующий, новый
		last->nextptr = newNode;
		//обновили УКАЗАТЕЛЬ LAST на последний элемент
		last = newNode;
		//дали новому элементу(который теперь last) указатель на предыдущий (предыдущий last - tempOfLast)
		last->prevptr = tempOfLast;
	}

	void removeBack() {
		if (isEmpty()) { return; }
		this->size--;

		Node* temp = last;
		last = temp->prevptr;
		if (last == nullptr) {//такое может быть при удалении последнего элемента
			first = nullptr;
		}
		else {
			last->nextptr = nullptr;
		}
		//удаляем объект, который БЫЛ последним
		delete temp;
	}

	virtual Type getBack() {
		if (isEmpty()) {
			throw std::exception("list is empty");
		}
		return last->value;
	}

	//удаляет элемент в конце списка и возвращает его копию
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
		//Выделили память для нового элемента, сохранили указатель на него
		Node* newNode = new Node(value);
		this->size++;

		if (this->isEmpty()) {
			first = newNode;
			last = newNode;
			return;
		}

		Node* tempOfFirst = first;
		//дали старому первому элементу указатель на новый первый, который теперь предыдущий для него
		first->prevptr = newNode;
		//обновли УКАЗАТЕЛь на первый элемент
		first = newNode;
		//для нового первого элемента следующий элемент теперь старый первый 
		first->nextptr = tempOfFirst;
	}

	void removeFront() {
		if (this->isEmpty()) { return; }
		this->size--;

		Node* temp = first;
		//указываем first на второй элемент
		first = temp->nextptr;

		if (first == nullptr) {//такое может быть при удалении последнего элемента
			last = nullptr;
		}
		else {
			//у первого элемента теперь нет предыдущего элемента
			first->prevptr = nullptr;
		}
		//удаляем объект, который БЫЛ первым
		delete temp;
	}

	virtual Type getFront() {
		if (this->isEmpty()) {
			throw std::exception("list is empty");
		}
		return first->value;
	}

	//удаляет элемент в начале списка и возвращает его копию
	Type popFront() {
		Type temp = getFront();
		removeFront();
		return temp;
	}
};
	



