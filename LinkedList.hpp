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
	bool removeHead();
	bool removeTail();
	void Clear();

	// Operators
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept;
	LinkedList<T>& operator=(const LinkedList<T>& rhs);

	// Construction/Destruction
	LinkedList();
	LinkedList(const LinkedList<T>& list);
	LinkedList(LinkedList<T>&& other) noexcept;
	~LinkedList();

private:
	// Stores pointers to first and last nodes and count
	Node* head;
	Node* tail;
	unsigned int count;

};


