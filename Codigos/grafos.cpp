#include "grafos.hpp"
#include <iostream>
using namespace std;

/////////////////////////////////////////////////////////////////////////////////////
////////////////////////    Implementação da Excessão    ////////////////////////////

VertexNotFoundException::VertexNotFoundException (const char* message) {
	this -> message = message;
}

const char* VertexNotFoundException::what () {
	return message;
}

MatrixSizeException::MatrixSizeException (const char* message) {
	this -> message = message;
}

const char* MatrixSizeException::what () {
	return message;
}

EdgeInsertionException::EdgeInsertionException (const char* message) {
	this -> message = message;
}

const char* EdgeInsertionException::what () {
	return message;
}

/////////////////////////////////////////////////////////////////////////////////////
////////////////////////  Implementação da SUPERCLASSE   ////////////////////////////

Grafo::Grafo (bool orientado) {
	this -> orientado = orientado;
	quantVertices = 0;
	quantArestas = 0;
}

/////////////////////////////////////////////////////////////////////////////////////
////////////////////  Implementação da Matriz de Adjacência  ////////////////////////

MatrizDeAdjacencia::MatrizDeAdjacencia (bool orientado) : Grafo (orientado) {
	matriz = NULL;
}

MatrizDeAdjacencia::~MatrizDeAdjacencia () {
	reiniciar();
}

void MatrizDeAdjacencia::clearMatrix () {
	for (int i = 0; i < quantVertices; i++) {
		delete[] matriz[i];
	}
	delete[] matriz;
	matriz = NULL;
}

void MatrizDeAdjacencia::reiniciar () {
	clearMatrix();
	quantVertices = 0;
	quantArestas = 0;
}

void MatrizDeAdjacencia::expandMatix (int amount) {
	if (amount <= 0) {
		throw MatrixSizeException ("Insira um número maior que zero para ampliar sua matiz!");
	}
	int newSize = quantVertices + amount;
	int** newMatrix = new int*[newSize];
	for (int i = 0; i < newSize; i++) {
		newMatrix[i] = new int[newSize];
		for (int j = 0; j < newSize; j++) {
			if (i < quantVertices and j < quantVertices) {
				newMatrix[i][j] = matriz[i][j];
			} else {
				newMatrix[i][j] = 0;
			}
		}
	}
	clearMatrix();
	matriz = newMatrix;
}

List MatrizDeAdjacencia::getVizinhos (int vertice) {
	if (vertice < 0 or vertice >= quantVertices) {
		throw VertexNotFoundException ("Vértice inválido!");
	}
	List listaDeVizinhos;
	for (int i = 0; i < quantVertices; i++) {
		if (matriz[vertice][i] > 0) {
			listaDeVizinhos.insertR(i);
		}
	}
	return listaDeVizinhos;
}

bool MatrizDeAdjacencia::isVizinho (int vertice1, int vertice2) {
	if (vertice1 < 0 or vertice1 >= quantVertices) {
		throw VertexNotFoundException ("Vértice inválido!");
	}
	if (vertice2 < 0 or vertice2 >= quantVertices) {
		throw VertexNotFoundException ("Vértice inválido!");
	}
	return (matriz[vertice1][vertice2] > 0);
}

void MatrizDeAdjacencia::adicionarVertices (int quantidade) {
	if (matriz == NULL) {
		matriz = new int*[quantidade];
		for (int i = 0; i < quantidade; i++) {
			matriz[i] = new int[quantidade];
			for (int j = 0; j < quantidade; j++) {
				matriz[i][j] = 0;
			}
		}
	} else {
		expandMatix(quantidade);
	}
	quantVertices += quantidade;
}

void MatrizDeAdjacencia::adicionarAresta (int vertice1, int vertice2, int peso) {
	if (matriz == NULL) {
		throw EdgeInsertionException ("Grafo não inicializado!");
	}
	if (vertice1 >= quantVertices or vertice2 >= quantVertices) {
		throw EdgeInsertionException (("Vértice não existente na matriz: " 
			+ toString((vertice1 >= quantVertices) ? (vertice1) : (vertice2))).c_str());
	}
	if (matriz[vertice1][vertice2] != 0) {
		throw EdgeInsertionException (("Essa aresta já existe, e tem peso " 
			+ toString(matriz[vertice1][vertice2])).c_str());
	}
	matriz[vertice1][vertice2] = peso;
	if (orientado) {
		matriz[vertice2][vertice1] = peso;
	}
	quantArestas++;
}

string MatrizDeAdjacencia::getRepresentacao () {
	string result = "";
	if (matriz != NULL) {
		result = "Representação da Matriz de Adjacência:\n\t\t";

		for (int i = 0; i < quantVertices; i++) {
			result += toString(i) + "\t";
		}
		result += "\n\t";
		for (int i = 0; i < quantVertices; i++) {
			result += "--------";
		}
		result += "--\n\t";
		for (int i = 0; i < quantVertices; i++) {
			result += toString(i) + " | \t";
			for (int j = 0; j < quantVertices; j++) {
				result += toString(matriz[i][j]) + "\t";
			}
			result += "\n\t";
		}
		result += "Número de vértices: " + toString(quantVertices) + "\n\t";
		result += "Número de arestas:  " + toString(quantArestas);
	} else {
		result = "Grafo vazio!";
	}
	return result;
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////