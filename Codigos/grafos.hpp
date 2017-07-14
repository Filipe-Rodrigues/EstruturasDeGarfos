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

class DataStructureSizingException : public std::exception {
	
	private:
		const char* message;

	public:
		DataStructureSizingException(const char* message);
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
		int getQuantVertices () {return quantVertices;}
		int getQuantArestas () {return quantArestas;}
		virtual void reiniciar () = 0;
		virtual List getVizinhos (int vertice) = 0;
		virtual bool isVizinho (int vertice1, int vertice2) = 0;
		virtual void adicionarVertices (int quantidade) = 0;
		virtual void adicionarAresta (int vertice1, int vertice2, int peso) = 0;
		virtual string getRepresentacao () = 0;

};

class MatrizDeAdjacencia : public Grafo{

	private:
		int** matriz;
		void expandMatrix (int amount);
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

class ListaDeAdjacencia : public Grafo{

	private:
		List** listas;
		void expandList (int amount);
		void clearList ();
	public:
		ListaDeAdjacencia (bool orientado);
		~ListaDeAdjacencia();
		void reiniciar ();
		List getVizinhos (int vertice);
		bool isVizinho (int vertice1, int vertice2);
		void adicionarVertices (int quantidade);
		void adicionarAresta (int vertice1, int vertice2, int peso);
		string getRepresentacao ();

};

class MatrizDeIncidencia : public Grafo{

	private:
		CelulaDeIncidencia** matriz;
		void expandMatrix (int amountL, int amountC);
		void clearMatrix ();
	public:
		MatrizDeIncidencia (bool orientado);
		~MatrizDeIncidencia();
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
