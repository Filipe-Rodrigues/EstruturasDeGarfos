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

class InformacoesDeAresta {
	private:
		int verticeAlvo;
		int peso;
	public:
		InformacoesDeAresta () {verticeAlvo = -1; peso = 0;}
		InformacoesDeAresta (int verticeAlvo, int peso);
		InformacoesDeAresta (const InformacoesDeAresta& obj);
		void setVerticeAlvo (int verticeAlvo);
		void setPeso (int peso);
		int getVerticeAlvo ();
		int getPeso ();
		InformacoesDeAresta& operator = (const InformacoesDeAresta& rhs);
};

class CelulaDeIncidencia {
	private:
		bool pesoPositivo;
		int peso;
	public:
		CelulaDeIncidencia () {pesoPositivo = true; peso = 0;}
		CelulaDeIncidencia (bool pesoPositivo, int peso);
		CelulaDeIncidencia (const CelulaDeIncidencia& obj);
		void setPesoPositivo (bool pesoPositivo);
		void setPeso (int peso);
		bool temPesoPositivo ();
		int getPeso ();
		CelulaDeIncidencia& operator = (const CelulaDeIncidencia& rhs);
};

class Stack {

	private:
		class Node {
			friend class Stack;
			private:
				int anterior;
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
				int anterior;
				int data;
				Node* next;
			public:
				Node (int data) {this -> data = data; next = NULL;}
		};
		Node* first;
		Node* last;
		int queueSize;

		void enqueue (int element);
		int dequeue ();
		string roam ();

	public:
		Queue () {first = NULL; last = NULL; queueSize = 0;}
		~Queue();
		void empty ();
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
				int anterior;
				InformacoesDeAresta data;
				Node* next;
				Node* prev;
			public:
				Node (InformacoesDeAresta& data, Node* prev, Node* next);
		};
		Node* first;
		Node* last;
		int listSize;

		void insertFirst (InformacoesDeAresta element);
		string roam ();

	public:
		List () {first = NULL; last = NULL; listSize = 0;}
		List (const List& obj);
		~List();
		void empty ();
		int size ();
		bool isEmpty ();
		void insertL (InformacoesDeAresta element);
		void insertR (InformacoesDeAresta element);
		void insertAtPosition (InformacoesDeAresta element, int position);
		void remove (int position);
		bool exists (int dataValue);
		InformacoesDeAresta search (int dataValue);
		InformacoesDeAresta pull (int position);
		InformacoesDeAresta get (int position);
		List& operator >> (string& rhs);
		List& operator = (const List& rhs);

};

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

#endif
