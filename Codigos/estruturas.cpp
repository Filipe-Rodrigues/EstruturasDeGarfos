#include "estruturas.hpp"

/////////////////////////////////////////////////////////////////////////////////////
////////////////////////       Funções Auxiliares        ////////////////////////////

string toString (int value) {
	ostringstream ss;
	ss << value;
	return ss.str();
}

string toString (double value) {
	ostringstream ss;
	ss << value;
	return ss.str();
}

int modulo (int value) {
	return ((value >= 0) ? (value) : (-value));
}

string obterTempo (double tempo) {
	int d, h, m, s, ms, us;
	d = h = m = s = ms = 0;
	us = tempo;
	if (us > 1000) {
		ms = us/1000;
		us %= 1000;
		if (ms > 1000) {
			s = ms/1000;
			ms %= 1000;
			if (s > 60) {
				m = s/60;
				s %= 60;
				if (m > 60) {
					h = m/60;
					m %= 60;
					if (h > 24) {
						d = h/24;
						h %= 24;
					}
				}
			}
		}
	}
	string tempoFormatado = toString(d) + "d " + toString(h) + "h " +
		toString(m) + "m " + toString(s) + "s " + toString(ms) + "ms " + 
		toString(us) + "μs";
	return tempoFormatado;
}

/////////////////////////////////////////////////////////////////////////////////////
////////////////////////    Implementação da Excessão    ////////////////////////////

DataStructureException::DataStructureException (const char* message) {
	this -> message = message;
}

const char* DataStructureException::what () {
	return message;
}

IndexOutOfBoundsException::IndexOutOfBoundsException (const char* message) {
	this -> message = message;
}

const char* IndexOutOfBoundsException::what () {
	return message;
}

/////////////////////////////////////////////////////////////////////////////////////
////////////////////////    Implementações auxiliares    ////////////////////////////

InformacoesDeAresta::InformacoesDeAresta (int verticeAlvo, int peso) {
	this -> verticeAlvo = verticeAlvo;
	this -> peso = peso;
}

InformacoesDeAresta::InformacoesDeAresta (const InformacoesDeAresta& obj) {
	verticeAlvo = obj.verticeAlvo;
	peso = obj.peso;
}

void InformacoesDeAresta::setVerticeAlvo (int verticeAlvo) {
	this -> verticeAlvo = verticeAlvo;
}

void InformacoesDeAresta::setPeso (int peso) {
	this -> peso = peso;
}

int InformacoesDeAresta::getVerticeAlvo () {
	return verticeAlvo;
}

int InformacoesDeAresta::getPeso () {
	return peso;
}

InformacoesDeAresta& InformacoesDeAresta::operator = (const InformacoesDeAresta& rhs) {
	if (this != &rhs) {
		verticeAlvo = rhs.verticeAlvo;
		peso = rhs.peso;
	}
	return *this;
}

CelulaDeIncidencia::CelulaDeIncidencia (bool pesoPositivo, int peso) {
	this -> pesoPositivo = pesoPositivo;
	this -> peso = peso;
}

CelulaDeIncidencia::CelulaDeIncidencia (const CelulaDeIncidencia& obj) {
	pesoPositivo = obj.pesoPositivo;
	peso = obj.peso;
}

void CelulaDeIncidencia::setPesoPositivo (bool pesoPositivo) {
	this -> pesoPositivo = pesoPositivo;
}

void CelulaDeIncidencia::setPeso (int peso) {
	this -> peso = peso;
}

bool CelulaDeIncidencia::temPesoPositivo () {
	return pesoPositivo;
}

int CelulaDeIncidencia::getPeso () {
	return peso;
}

CelulaDeIncidencia& CelulaDeIncidencia::operator = (const CelulaDeIncidencia& rhs) {
	if (this != &rhs) {
		pesoPositivo = rhs.pesoPositivo;
		peso = rhs.peso;
	}
	return *this;
}

/////////////////////////////////////////////////////////////////////////////////////
////////////////////////      Implementação da Pilha     ////////////////////////////

Stack::Node::Node (int data, Node* next) {
	this -> data = data;
	this -> next = next;
}

Stack::~Stack () {
	empty();
}

void Stack::empty () {
	while (top != NULL) {
		Node* aux = top;
		top = top -> next;
		delete aux;
	}
	top = NULL;
	stackSize = 0;
}

bool Stack::isEmpty () {
	return stackSize == 0;
}

void Stack::push (int element) {
	if (top == NULL) {
		top = new Stack::Node (element, NULL);
	} else {
		Node* aux = top;
		top = new Stack::Node (element, aux);
	}
	stackSize++;
}

int Stack::pop () {
	if (top == NULL) {
		throw DataStructureException ("A pilha está VAZIA! Não insista!");
	}
	int element = top -> data;
	Node* aux = top;
	top = top -> next;
	delete aux;
	stackSize--;
	return element;
}

string Stack::roam () {
	string result;
	if (stackSize == 0) {
		result = "Pilha vazia!";
	} else {
		Node* aux = top;
		result = "TOPO";
		while (aux != NULL) {
			result += " |> " + toString(aux -> data);
			aux = aux -> next;
		}
		result += " |> BASE";
	}
	return result;
}

Stack& Stack::operator << (const int& rhs) {
	push(rhs);
	return *this;
}

Stack& Stack::operator >> (int& rhs) {
	rhs = pop();
	return *this;
}

Stack& Stack::operator >> (string& rhs) {
	rhs = roam();
	return *this;
}

/////////////////////////////////////////////////////////////////////////////////////
////////////////////////      Implementação da Fila      ////////////////////////////

Queue::~Queue () {
	empty();
}

void Queue::empty () {
	while (first != NULL) {
		Node* aux = first;
		first = first -> next;
		delete aux;
	}
	first = NULL;
	last = NULL;
	queueSize = 0;
}

bool Queue::isEmpty () {
	return queueSize == 0;
}

int Queue::peek () {
	return first -> data;
}

int Queue::size(){
	return queueSize;
}

void Queue::enqueue (int element) {
	if (first == NULL) {
		first = new Node (element);
		last = first;
	} else {
		Node* aux = new Node (element);
		last -> next = aux;
		last = last -> next; 
	}
	queueSize++;
}

int Queue::dequeue () {
	if (first == NULL) {
		throw DataStructureException ("A fila está VAZIA! Não insista!");
	}
	int element = first -> data;
	Node* aux = first;
	first = first -> next;
	delete aux;
	queueSize--;
	return element;
}

string Queue::roam () {
	string result;
	if (queueSize == 0) {
		result = "Fila vazia!";
	} else {
		Node* aux = first;
		result = "PRIMEIRO";
		while (aux != NULL) {
			result += " <| " + toString(aux -> data);
			aux = aux -> next;
		}
		result += " <| BASE";
	}
	return result;
}

Queue& Queue::operator << (const int& rhs) {
	enqueue(rhs);
	return *this;
}

Queue& Queue::operator >> (int& rhs) {
	rhs = dequeue();
	return *this;
}

Queue& Queue::operator >> (string& rhs) {
	rhs = roam();
	return *this;
}

/////////////////////////////////////////////////////////////////////////////////////
////////////////////////      Implementação da Lista     ////////////////////////////

List::Node::Node (InformacoesDeAresta& data, Node* prev, Node* next) {
	this -> data = data;
	this -> prev = prev;
	this -> next = next;
}

List::List (const List& obj) {
	listSize = obj.listSize;
	if (listSize > 0) {
		Node* auxOBJ = obj.first;
		first = new Node(auxOBJ -> data, NULL, NULL);
		Node* auxTHIS = first;
		while (auxOBJ -> next != NULL) {
			auxOBJ = auxOBJ -> next;
			auxTHIS -> next = new Node (auxOBJ -> data, auxTHIS, NULL);
			auxTHIS = auxTHIS -> next;
		}
		last = auxTHIS;
	} else {
		first = NULL;
		last = NULL;
	}
}

List::~List () {
	empty();
}

void List::empty () {
	while (first != NULL) {
		Node* aux = first;
		first = first -> next;
		delete aux;
	}
	listSize = 0;
}

bool List::isEmpty () {
	return listSize == 0;
}

string List::roam () {
	string result;
	if (listSize == 0) {
		result = "Lista vazia!";
	} else {
		Node* aux = first;
		result = "INÍCIO:: ";
		while (aux -> next != NULL) {
			result += "Dest. " + toString(aux -> data.getVerticeAlvo()) 
			+ ", Peso " + toString(aux -> data.getPeso()) + " <-> ";
			aux = aux -> next;
		}
		result += "Dest. " + toString(aux -> data.getVerticeAlvo()) 
		+ ", Peso " + toString(aux -> data.getPeso()) + " ::FIM";
	}
	return result;
}

void List::insertFirst (InformacoesDeAresta element) {
	first = new Node(element, NULL, NULL);
	last = first;
}

int List::size () {
	return listSize;
}

void List::insertL (InformacoesDeAresta element) {
	if (isEmpty()) {
		insertFirst(element);
	} else {
		Node* aux = new Node(element, NULL, first);
		first = aux;
		first -> next -> prev = first;
	}
	listSize++;
}

void List::insertR (InformacoesDeAresta element) {
	if (isEmpty()) {
		insertFirst(element);
	} else {
		Node* aux = new Node(element, last, NULL);
		last = aux;
		last -> prev -> next = last;
	}
	listSize++;
}

void List::insertAtPosition (InformacoesDeAresta element, int position) {
	if (position == 0) {
		insertL(element);
	} else if (position == listSize) {
		insertR(element);
	} else if (position > 0 and position < listSize) {
		Node* aux = first;
		for (int i = 0; i < position - 1; i++) {
			aux = aux -> next;
		}
		Node* newNode = new Node(element, aux, aux -> next);
		aux -> next = newNode;
		newNode -> next -> prev = newNode;
		listSize++;
	} else {
		throw IndexOutOfBoundsException("Posição de inserção inválida!");
	}
}

void List::remove (int position) {
	pull(position);
}

bool List::exists (int dataValue) {
	Node* aux = first;
	while (aux != NULL and aux -> data.getVerticeAlvo() != dataValue) {
		aux = aux -> next;
	}
	if (aux != NULL) {
		return true;
	} else {
		return false;
	}
}

InformacoesDeAresta List::search (int dataValue) {
	Node* aux = first;
	while (aux != NULL and aux -> data.getVerticeAlvo() != dataValue) {
		aux = aux -> next;
	}
	if (aux != NULL) {
		return aux -> data;
	} else {
		InformacoesDeAresta notFound;
		return notFound;
	}
}

InformacoesDeAresta List::pull (int position) {
	if (position == 0 and listSize > 0) {
		Node* aux = first;
		first = first -> next;
		InformacoesDeAresta value = aux -> data;
		delete aux;
		if (listSize == 1) {
			last = NULL;
		} else {
			first -> prev = NULL;
		}
		listSize--;
		return value;
	} else if (position == listSize - 1 and listSize > 0) {
		Node* aux = last;
		last = last -> prev;
		last -> next = NULL;
		InformacoesDeAresta value = aux -> data;
		delete aux;
		listSize--;
		return value;
	} else if (position > 0 and position < listSize) {
		Node* aux = first;
		for (int i = 0; i < position; i++) {
			aux = aux -> next;
		}
		aux -> prev -> next = aux -> next;
		aux -> next -> prev = aux -> prev;
		InformacoesDeAresta value = aux -> data;
		delete aux;
		listSize--;
		return value;
	} else {
		throw IndexOutOfBoundsException("Posição de remoção inválida!");
	}
}

InformacoesDeAresta List::get (int position) {
	if (position < 0 or position >= listSize) {
		throw IndexOutOfBoundsException("Posição de acesso inválida!");
	}
	Node* aux = first;
	for (int i = 0; i < position; i++) {
		aux = aux -> next;
	}
	return aux -> data;
}

List& List::operator >> (string& rhs) {
	rhs = roam();
	return *this;
}

List& List::operator = (const List& rhs) {
	if (this != &rhs) {
		listSize = rhs.listSize;
		if (listSize > 0) {
			Node* auxOBJ = rhs.first;
			first = new Node(auxOBJ -> data, NULL, NULL);
			Node* auxTHIS = first;
			while (auxOBJ -> next != NULL) {
				auxOBJ = auxOBJ -> next;
				auxTHIS -> next = new Node (auxOBJ -> data, auxTHIS, NULL);
				auxTHIS = auxTHIS -> next;
			}
			last = auxTHIS;
		} else {
			first = NULL;
			last = NULL;
		}
	}
	return *this;
}

/////////////////////////////////////////////////////////////////////////////////////
