#ifndef GRAFOS_HPP
#define GRAFOS_HPP 1

#include "estruturas.cpp"

/////////////////////////////////////////////////////////////////////////////////////
////////////////////////      Definição das Classes      ////////////////////////////

class VertexNotFoundException : public std::exception {
	
	private:
		const char* message;

	public:
		VertexNotFoundException(const char* message);
		virtual const char* what ();

};

class MatrixSizeException : public std::exception {
	
	private:
		const char* message;

	public:
		MatrixSizeException(const char* message);
		virtual const char* what ();

};

class EdgeInsertionException : public std::exception {
	
	private:
		const char* message;

	public:
		EdgeInsertionException(const char* message);
		virtual const char* what ();

};

class Grafo {

	protected:
		bool orientado;
		int quantVertices;
		int quantArestas;

	public:
		Grafo (bool orientado);
		~Grafo() {}
		virtual void reiniciar () = 0;
		int getQuantVertices () {return quantVertices;}
		int getQuantArestas () {return quantArestas;}
		virtual List getVizinhos (int vertice) = 0;
		virtual bool isVizinho (int vertice1, int vertice2) = 0;
		virtual void adicionarVertices (int quantidade) = 0;
		virtual void adicionarAresta (int vertice1, int vertice2, int peso) = 0;
		virtual string getRepresentacao () = 0;

};

class MatrizDeAdjacencia : public Grafo{

	private:
		int** matriz;
		void expandMatix (int amount);
		void clearMatrix ();
	public:
		MatrizDeAdjacencia (bool orientado);
		~MatrizDeAdjacencia();
		void reiniciar ();
		List getVizinhos (int vertice);
		bool isVizinho (int vertice1, int vertice2);
		void adicionarVertices (int quantidade);
		void adicionarAresta (int vertice1, int vertice2, int peso);
		string getRepresentacao ();

};

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

#endif