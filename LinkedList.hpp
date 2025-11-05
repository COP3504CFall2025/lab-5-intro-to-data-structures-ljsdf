#pragma once
#include <iostream>

template <typename T>
class LinkedList {
	struct Node {
		T data;
		Node* prev;
		Node* next;
	};
public:
	// Behaviors
	void printForward() const {
		Node* index = head;
		while (index != nullptr) {
			std::cout << index->data << std::endl;
			index = index->next;
		}
	};
	void printReverse() const {
		Node* index = tail;
		while (index != nullptr) {
			std::cout << index->data << std::endl;
			index = index->prev;
		}
	};

	// Accessors
	[[nodiscard]] unsigned int getCount() const {
		return count;
	};
	Node* getHead() {
		return head;
	};
	const Node* getHead() const {
		return head;
	};
	Node* getTail() {
		return tail;
	};
	const Node* getTail() const {
		return tail;
	};

	// Insertion
	void addHead(const T& data) {
		head = new Node(data,nullptr,head);
		count++;
	};
	void addTail(const T& data) {
		tail = new Node(data,tail,nullptr);
		count++;
	};

	// Removal
	bool removeHead() {
		if (head->next==nullptr) return false;
		Node* temp = head;
		head = head->next;
		delete temp;
		count--;
		return true;
	};
	bool removeTail() {
		if (head->prev==nullptr) return false;
		Node* temp = tail;
		tail = tail->prev;
		delete temp;
		count--;
		return true;
	};
	void Clear() {
		Node* deleteing = head;
		Node* next = nullptr;
		while (deleteing) {
			next = deleteing->next;
			delete deleteing;
			deleteing = next;
		}
		count = 0;
		head = nullptr;
		tail = nullptr;
	};

	// Operators
	LinkedList<T>& operator=(LinkedList<T>&& rhs) noexcept { //move
		if (&rhs == this) return *this;
		Clear();

		head = rhs.head;
		tail = rhs.tail;
		count = rhs.count;

		rhs.head = nullptr;
		rhs.tail = nullptr;
		rhs.count = 0;

		return *this;
	};
	LinkedList<T>& operator=(const LinkedList<T>& rhs) { // copy
		if (&rhs == this) return *this;
		Clear();

		Node* current = rhs.head;
		while (current != nullptr) {
			addTail(current->data);
			current = current->next;
		}

		return *this;
	};

	// Construction/Destruction
	LinkedList(): head(nullptr), tail(nullptr), count(0) {};
	LinkedList(const LinkedList<T>& list): head(nullptr), tail(nullptr), count(0) {
		Node* current = list.head;
		while (current != nullptr) {
			addTail(current->data);
			current = current->next;
		};
	}
	LinkedList(LinkedList<T>&& other) noexcept: head(other.head), tail(other.tail), count(other.count)  {
		other.head = nullptr;
		other.tail = nullptr;
		other.count = 0;
	};
	~LinkedList() {
		Clear();
	};

private:
	// Stores pointers to first and last nodes and count
	Node* head;
	Node* tail;
	unsigned int count;

};


