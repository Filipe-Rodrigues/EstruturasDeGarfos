#include <iostream>
#include <fstream>
#include "grafos.cpp"
#include "objetos.cpp"

using namespace std;

void findBridges(Grafo* grafo, int v, int tam, int &cnt, int &bcnt, DFSdata *vertices) {

    vertices[v].visitado = true; // marca como visitado
    vertices[v].low = vertices[v].num = cnt++;
    
    List vizinhos = grafo -> getVizinhos(v);
	for(int j = 0; j < vizinhos.size(); j++){  
		int i = vizinhos.get(j).getVerticeAlvo();
		if (!vertices[i].visitado){
			vertices[i].anterior = v;
			findBridges(grafo, i, tam, cnt, bcnt, vertices); // visita o vértice
			if (vertices[v].low > vertices[i].low) vertices[v].low = vertices[i].low;
			if (vertices[i].low == vertices[i].num){
				bcnt++;
				//cout << "ponte " << v << " - " << i << "\n";
			}
		}
		else if (i!=vertices[v].anterior and vertices[v].low > vertices[i].num){
			vertices[v].low = vertices[i].num;
			
		}
	}
}


void cutVertices(Grafo* grafo, int u, int tam, DFSdata *vertices) {
	
	static int cnt = 0;
	int filhos = 0;
	
    vertices[u].visitado = true; // marca como visitado
    vertices[u].low = vertices[u].num = ++cnt;
    List vizinhos = grafo -> getVizinhos(u);

    for(int i = 0; i < vizinhos.size(); i++){  // percorre as arestas do vertice
		int v = vizinhos.get(i).getVerticeAlvo();
		if (!vertices[v].visitado){
			filhos++;
			vertices[v].anterior = u;
			cutVertices(grafo, v, tam, vertices); // visita o vértice
			vertices[u].low = min(vertices[u].low, vertices[v].low);
			
			if((vertices[u].anterior == -1) && (filhos > 1)){
				vertices[u].marcado = true;
			}
			if((vertices[u].anterior != -1) && (vertices[v].low >= vertices[u].num)){
				//cout << "Ponto de articulacao - " << v << "\n";
				vertices[u].marcado = true;
			}
		}
		else if (v!=vertices[u].anterior){
			vertices[u].low = min(vertices[u].low, vertices[v].num);
			
		}
    }

}

int verificaPonte(Grafo* grafo, int tam){
	DFSdata *vertices  = new DFSdata[tam];
	int cnt = 0, bcnt = 0;
	
	for(int i=0; i<tam; i++){
		if(vertices[i].visitado == false){
			findBridges(grafo, i, tam, cnt, bcnt, vertices);
		}
	}
	delete []vertices;
	return bcnt;
}

int verificaPontoDeArticulacao(Grafo* grafo, int tam) {
	DFSdata *vertices = new DFSdata[tam];
	int numArticulacoes = 0;
	
	for(int i=0; i < tam; i++){
		if(vertices[i].visitado == false){
			cutVertices(grafo, i, tam, vertices);
		}
	}
	
	for (int j = 0; j < tam; j++) {
		if (vertices[j].marcado) {
			//cout << "Ponto de articulacao - " << j << "\n";
			numArticulacoes++;
		}
	}
	delete[] vertices;
	return numArticulacoes;
}

int buscarVertices(Grafo* grafo, int u, DFSdata* vertices, int &cnt){
	
    vertices[u].visitado = true; // marca como visitado
    vertices[u].low = vertices[u].num = ++cnt;
    List vizinhos = grafo -> getVizinhos(u);

    for(int i = 0; i < vizinhos.size(); i++){  // percorre as arestas do vertice
		int v = vizinhos.get(i).getVerticeAlvo();
		if (!vertices[v].visitado){
			vertices[v].anterior = u;
			buscarVertices(grafo, v, vertices, cnt); // visita o vértice
		}
    }
    
	return cnt;
}

int verticesAlcancaveis (Grafo* grafo, int v, int tam) {
	int cnt = -1;
	DFSdata *vertices = new DFSdata[tam];
	int alcancaveis = buscarVertices(grafo, v, vertices, cnt);
	return alcancaveis;
	delete []vertices;
}

int calcularDiametro(Grafo* grafo, int tam){
	MinimumData* vertices;
	Queue fila;
	int v, u, distancia = 0, maiorDistancia = 0;
	
	for(int i=0; i<tam; i++){
		vertices  = new MinimumData[tam];
		vertices[i].d = 0;
		vertices[i].cor = 'C';
		fila << i;
		
		while(fila . size() != 0){
			//distancia++;
			fila >> v;	
			List vizinhos = grafo -> getVizinhos(v);
			for(int j = 0; j < vizinhos.size(); j++) { 
				u = vizinhos.get(j).getVerticeAlvo();
				if (vertices[u].cor != 'C'){
					vertices[u].d = vertices[v].d + 1;
					vertices[u].cor = 'C';
					vertices[u].anterior = v;
					fila << u;
				} 
				if(vertices[u].d > distancia) distancia = vertices[u].d;
			}
		}
		
		if (distancia > maiorDistancia) maiorDistancia = distancia;
		
		delete []vertices;
	}
	return	maiorDistancia;
} 

int main() {
	int orient, numOp;
	cout << "Seu grafo é orientado? (0 - Não, 1 - sim): ";
	cin >> orient;
	bool orientado = (orient == 1)? (true) : (false);
	
	cout << "Como deseja representar seu grafo: \n";
	cout << "1 - Matriz de Adjacencia \n";
	cout << "2 - Lista de Adjacencia \n";
	cout << "3 - Matriz de Incidencia \n Opcao: ";
	cin >> numOp;
	
	Grafo* grafo;
	if(numOp == 1){
		grafo = new MatrizDeAdjacencia(orientado);
	}
	else if(numOp == 2){
		grafo = new ListaDeAdjacencia(orientado);
	}
	else if(numOp == 3){
		grafo = new MatrizDeIncidencia(orientado);
	}
	else cout << "Comando Invalido\n";
	
	cout << "Digite o nome do arquivo que consta os dados: ";
	string arquivo;
	cin >> arquivo;
	
	ifstream arq(arquivo.c_str());
	int tam, i, j;
	arq >> tam;
	grafo -> adicionarVertices(tam);
	
	do{
		arq >> i;
		arq >> j;
		try{
			grafo -> adicionarAresta(i, j, 1);
		} catch (EdgeInsertionException e) {
			cerr << e.what() << endl;
		}
	}while(arq.good());
	
	arq.close();
	if(orient == 0){
		cout << "Numero de Articulações : " << verificaPontoDeArticulacao(grafo, tam) << "\n";
		cout << "Numero de pontes : " << verificaPonte(grafo, tam) << "\n";
	}
	cout << "Vertices Alcanceveis do 0 : " << verticesAlcancaveis(grafo, 0, tam) << "\n";
	cout << "Vertices Alcanceveis do 1 : " << verticesAlcancaveis(grafo, 1, tam) << "\n";
	cout << "Diametro : " << calcularDiametro(grafo, tam) << "\n";
	return 0;
}
