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

DataStructureSizingException::DataStructureSizingException (const char* message) {
	this -> message = message;
}

const char* DataStructureSizingException::what () {
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

void MatrizDeAdjacencia::expandMatrix (int amount) {
	if (amount <= 0) {
		throw DataStructureSizingException ("Insira um número maior que zero para ampliar sua matiz!");
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
		throw VertexNotFoundException (("Vértice inválido: " + toString(vertice)).c_str());
	}
	List listaDeVizinhos;
	for (int i = 0; i < quantVertices; i++) {
		if (matriz[vertice][i] > 0) {
			InformacoesDeAresta info (i, matriz[vertice][i]);
			listaDeVizinhos.insertR(info);
		}
	}
	return listaDeVizinhos;
}

bool MatrizDeAdjacencia::isVizinho (int vertice1, int vertice2) {
	if (vertice1 < 0 or vertice1 >= quantVertices) {
		throw VertexNotFoundException (("Vértice inválido: " + toString(vertice1)).c_str());
	}
	if (vertice2 < 0 or vertice2 >= quantVertices) {
		throw VertexNotFoundException (("Vértice inválido: " + toString(vertice1)).c_str());
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
		expandMatrix(quantidade);
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
	if (!orientado) {
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
//////////////////////  Implementação da Lista de Adjacência   //////////////////////

ListaDeAdjacencia::ListaDeAdjacencia (bool orientado) : Grafo (orientado) {
	listas = NULL;
}

ListaDeAdjacencia::~ListaDeAdjacencia () {
	reiniciar();
}

void ListaDeAdjacencia::clearList () {
	for (int i = 0; i < quantVertices; i++) {
		listas[i] -> empty();
		delete listas[i];
	}
	delete[] listas;
	listas = NULL;
}

void ListaDeAdjacencia::reiniciar () {
	clearList();
	quantVertices = 0;
	quantArestas = 0;
}

void ListaDeAdjacencia::expandList (int amount) {
	if (amount <= 0) {
		throw DataStructureSizingException ("Insira um número maior que zero para ampliar sua lista!");
	}
	int newSize = quantVertices + amount;
	List** newList = new List*[newSize];
	for (int i = 0; i < newSize; i++) {
		if (i < quantVertices) {
			newList[i] = new List (*(listas[i]));
			string test;
			*newList[i] >> test;
		} else {
			newList[i] = new List;
		}
	}
	clearList();
	listas = newList;
}

List ListaDeAdjacencia::getVizinhos (int vertice) {
	if (vertice < 0 or vertice >= quantVertices) {
		throw VertexNotFoundException (("Vértice inválido: " + toString(vertice)).c_str());
	}
	return *listas[vertice];
}

bool ListaDeAdjacencia::isVizinho (int vertice1, int vertice2) {
	if (vertice1 < 0 or vertice1 >= quantVertices) {
		throw VertexNotFoundException (("Vértice inválido: " + toString(vertice1)).c_str());
	}
	if (vertice2 < 0 or vertice2 >= quantVertices) {
		throw VertexNotFoundException (("Vértice inválido: " + toString(vertice2)).c_str());
	}
	return listas[vertice1] -> exists(vertice2);
}

void ListaDeAdjacencia::adicionarVertices (int quantidade) {
	if (listas == NULL) {
		listas = new List*[quantidade];
		for (int i = 0; i < quantidade; i++) {
			listas[i] = new List;
		}
	} else {
		expandList(quantidade);
	}
	quantVertices += quantidade;
}

void ListaDeAdjacencia::adicionarAresta (int vertice1, int vertice2, int peso) {
	if (listas == NULL) {
		throw EdgeInsertionException ("Grafo não inicializado!");
	}
	if (vertice1 >= quantVertices or vertice2 >= quantVertices) {
		throw EdgeInsertionException (("Vértice não existente na matriz: " 
			+ toString((vertice1 >= quantVertices) ? (vertice1) : (vertice2))).c_str());
	}
	InformacoesDeAresta result = listas[vertice1] -> search(vertice2);
	if (result.getVerticeAlvo() != -1) {
		throw EdgeInsertionException (("Essa aresta já existe, e tem peso " 
			+ toString(result.getPeso())).c_str());
	}
	InformacoesDeAresta insertionA (vertice2, peso);
	listas[vertice1] -> insertR(insertionA);
	if (!orientado) {
		InformacoesDeAresta insertionB (vertice1, peso);
		listas[vertice2] -> insertR(insertionB);
	}
	quantArestas++;
}

string ListaDeAdjacencia::getRepresentacao () {
	string result = "";
	if (listas != NULL) {
		result = "Representação da Lista de Adjacência:\n\t";

		for (int i = 0; i < quantVertices; i++) {
			string neighborhood;
			*(listas[i]) >> neighborhood;
			result += toString(i) + " | \t" + neighborhood + "\n\t";
		}
		result += "Número de vértices: " + toString(quantVertices) + "\n\t";
		result += "Número de arestas:  " + toString(quantArestas);
	} else {
		result = "Grafo vazio!";
	}
	return result;
}

/////////////////////////////////////////////////////////////////////////////////////
////////////////////  Implementação da Matriz de Incidência  ////////////////////////

MatrizDeIncidencia::MatrizDeIncidencia (bool orientado) : Grafo (orientado) {
	matriz = NULL;
}

MatrizDeIncidencia::~MatrizDeIncidencia () {
	reiniciar();
}

void MatrizDeIncidencia::clearMatrix () {
	for (int i = 0; i < quantArestas; i++) {
		delete[] matriz[i];
	}
	delete[] matriz;
	matriz = NULL;
}

void MatrizDeIncidencia::reiniciar () {
	clearMatrix();
	quantVertices = 0;
	quantArestas = 0;
}

void MatrizDeIncidencia::expandMatrix (int amountL, int amountC) {

	if (amountL < 0) {
		throw DataStructureSizingException ("Insira um número de linhas maior que zero para ampliar sua matiz!");
	}
	if (amountC < 0) {
		throw DataStructureSizingException ("Insira um número de colunas maior que zero para ampliar sua matiz!");
	}
	if (amountL == 0 and amountC == 0) {
		throw DataStructureSizingException ("A matriz deve ser ampliada em ao menos uma dimensão!");
	}
	int newSizeL = quantArestas + amountL;
	int newSizeC = quantVertices + amountC;
	CelulaDeIncidencia** newMatrix = new CelulaDeIncidencia*[newSizeL];
	for (int i = 0; i < newSizeL; i++) {
		newMatrix[i] = new CelulaDeIncidencia[newSizeC];
		for (int j = 0; j < newSizeC; j++) {
			if (i < quantArestas and j < quantVertices) {
				newMatrix[i][j] = matriz[i][j];
			}
		}
	}
	clearMatrix();
	matriz = newMatrix;
}

List MatrizDeIncidencia::getVizinhos (int vertice) {
	if (vertice < 0 or vertice >= quantVertices) {
		throw VertexNotFoundException (("Vértice inválido: " + toString(vertice)).c_str());
	}
	List listaDeVizinhos;

	int i = 0;

	while (i < quantArestas) {
		if ((orientado and matriz[i][vertice].getPeso() < 0) or 
			(!orientado and matriz[i][vertice].getPeso() > 0)) {
			int j = 0;
			bool found = false;
			while (j < quantVertices and !found) {
				if (j != vertice and matriz[i][j].getPeso() > 0) {
					InformacoesDeAresta info (j,
						matriz[i][j].getPeso() * (matriz[i][vertice].temPesoPositivo()) ? 
						(1) : (-1));
					listaDeVizinhos.insertR(info);
				}
				j++;
			} 
		}
		i++;
	}

	return listaDeVizinhos;
}

bool MatrizDeIncidencia::isVizinho (int vertice1, int vertice2) {
	if (vertice1 < 0 or vertice1 >= quantVertices) {
		throw VertexNotFoundException (("Vértice inválido: " + toString(vertice1)).c_str());
	}
	if (vertice2 < 0 or vertice2 >= quantVertices) {
		throw VertexNotFoundException (("Vértice inválido: " + toString(vertice1)).c_str());
	}

	int i = 0;
	bool found = false;

	while (i < quantArestas and !found) {
		if ((orientado and matriz[i][vertice1].getPeso() < 0) or 
			(!orientado and matriz[i][vertice1].getPeso() > 0)) {
			if (matriz[i][vertice2].getPeso() > 0) {
				found = true;
			}
		}
		i++;
	}
	return found;
}

void MatrizDeIncidencia::adicionarVertices (int quantidade) {
	if (matriz != NULL) {
		expandMatrix(0, quantidade);
	}
	quantVertices += quantidade;
}

void MatrizDeIncidencia::adicionarAresta (int vertice1, int vertice2, int peso) {
	if (vertice1 >= quantVertices or vertice2 >= quantVertices) {
		throw EdgeInsertionException (("Vértice não existente na matriz: " 
			+ toString((vertice1 >= quantVertices) ? (vertice1) : (vertice2))).c_str());
	}
	if (vertice1 == vertice2) return;
	if (isVizinho(vertice1, vertice2)) {
		int i = 0;
		int pesoEncontrado;
		bool found = false;

		while (i < quantArestas and !found) {
			if ((orientado and matriz[i][vertice1].getPeso() < 0) or 
				(!orientado and matriz[i][vertice1].getPeso() > 0)) {
				if (matriz[i][vertice2].getPeso() != 0) {
					found = true;
					pesoEncontrado = matriz[i][vertice2].getPeso() * 
					((matriz[i][vertice2].temPesoPositivo()) ? (1) : (-1));
				}
			}
			i++;
		}
		throw EdgeInsertionException (("Essa aresta já existe, e tem peso " 
			+ toString(pesoEncontrado)).c_str());
	}

	if (matriz == NULL) {
		matriz = new CelulaDeIncidencia*[1];
		matriz[0] = new CelulaDeIncidencia[quantVertices];
	} else {
		expandMatrix (1, 0);
	}

	CelulaDeIncidencia c1 ((peso >= 0) ? (true) : (false), modulo(peso) 
		* ((orientado) ? (-1) : (1)));
	CelulaDeIncidencia c2 ((peso >= 0) ? (true) : (false), modulo(peso));
	matriz[quantArestas][vertice1] = c1;
	matriz[quantArestas][vertice2] = c2;
	quantArestas++;
}

string MatrizDeIncidencia::getRepresentacao () {
	string result = "";
	if (matriz != NULL) {
		result = "Representação da Matriz de Incidência:\n\t\t\t";

		for (int i = 0; i < quantVertices; i++) {
			result += toString(i) + "\t";
		}
		result += "\n\t";
		for (int i = 0; i < quantVertices + 1; i++) {
			result += "--------";
		}
		result += "--\n\t";
		if (quantArestas > 0) {
			for (int i = 0; i < quantArestas; i++) {
				result += "Aresta " + toString(i) + " | \t";
				for (int j = 0; j < quantVertices; j++) {
					result += toString(matriz[i][j].getPeso()) + "\t";
				}
				result += "\n\t";
			}
		} else {
			result += "### SEM ARESTAS ###\n\t";
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