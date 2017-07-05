#ifndef ESTRUTURAS_HPP
#define ESTRUTURAS_HPP

#include <string>
#include <sstream>
#include <exception>

using namespace std;

/////////////////////////////////////////////////////////////////////////////////////
////////////////////////      Definição das Classes      ////////////////////////////

class DataStructureException : public std::exception {
	
	private:
		const char* message;

	public:
		DataStructureException(const char* message);
		virtual const char* what ();

};

class IndexOutOfBoundsException : public std::exception {
	
	private:
		const char* message;

	public:
		IndexOutOfBoundsException(const char* message);
		virtual const char* what ();

};

class Stack {

	private:
		class Node {
			friend class Stack;
			private:
				int data;
				Node* next;
			public:
				Node (int data, Node* next);
		} *top;
		int stackSize;

		void empty ();
		void push (int element);
		int pop ();
		string roam ();

	public:
		Stack () {top = NULL; stackSize = 0;}
		~Stack();
		int size ();
		bool isEmpty ();
		int peek ();
		Stack& operator << (const int& rhs);
		Stack& operator >> (int& rhs);
		Stack& operator >> (string& rhs);

};

class Queue {

	private:
		class Node {
			friend class Queue;
			private:
				int data;
				Node* next;
			public:
				Node (int data) {this -> data = data; next = NULL;}
		};
		Node* first;
		Node* last;
		int queueSize;

		void empty ();
		void enqueue (int element);
		int dequeue ();
		string roam ();

	public:
		Queue () {first = NULL; last = NULL; queueSize = 0;}
		~Queue();
		int size ();
		bool isEmpty ();
		int peek ();
		Queue& operator << (const int& rhs);
		Queue& operator >> (int& rhs);
		Queue& operator >> (string& rhs);

};

class List {

	private:
		class Node {
			friend class List;
			private:
				int data;
				Node* next;
				Node* prev;
			public:
				Node (int data, Node* next, Node* prev);
		};
		Node* first;
		Node* last;
		int listSize;

		void empty ();
		void insertFirst (int element);
		string roam ();

	public:
		List () {first = NULL; last = NULL; listSize = 0;}
		List (const List& obj);
		~List();
		int size ();
		bool isEmpty ();
		void insertL (int element);
		void insertR (int element);
		void insertAtPosition (int element, int position);
		void remove (int position);
		int pull (int position);
		int get (int position);
		List& operator >> (string& rhs);

};

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

#endif
