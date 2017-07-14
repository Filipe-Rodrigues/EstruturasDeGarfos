#include <iostream>
#include <fstream>
#include "grafos.cpp"
#include "objetos.cpp"

using namespace std;

void findBridges(Grafo* grafo, int v, int tam, int &cnt, int &bcnt, DFSdata *vertices) {
    int i;

    vertices[v].visitado = cnt++; // marca como visitado
    vertices[v].low = vertices[v].visitado;
    //low2[v] = num[v] = cnt2++;
    for(i = 0; i < tam; i++){  // percorre as arestas do vertice
        if (grafo->isVizinho(v, i)){
			if (vertices[i].visitado == -1){
				vertices[i].anterior = v;
				findBridges(grafo, i, tam, cnt, bcnt, vertices); // visita o vértice
				if (vertices[v].low > vertices[i].low) vertices[v].low = vertices[i].low;
				if (vertices[i].low == vertices[i].visitado){
					bcnt++;
					cout << "ponte " << v << " - " << i << "\n";
				}
				/*if(low2[i]>=num[v]){
					cout << "Ponto de articulacao - " << v << "\n";
				}
				low2[v]=(low2[v]<low2[i])?low2[v]:low2[i];*/
			}
			else if (i!=vertices[v].anterior){
				//low2[v] = (low2[v]<num[i])?low2[v]:num[i];
				if(vertices[v].low > vertices[i].visitado){
					vertices[v].low = vertices[i].visitado;
				}
			}
		}
    }
}

void cutVertices(Grafo* grafo, int v, int tam, int cnt, DFSdata *vertices) {
    int i;

    vertices[v].visitado = cnt; // marca como visitado
    vertices[v].low = vertices[v].num = cnt++;
    //low2[v] = num[v] = cnt2++;
    for(i = 0; i < tam; i++){  // percorre as arestas do vertice
        if (grafo->isVizinho(v, i)){
			if (vertices[i].visitado == -1){
				vertices[i].anterior = v;
				cutVertices(grafo, i, tam, cnt, vertices); // visita o vértice
				if (vertices[v].low > vertices[i].low) vertices[v].low = vertices[i].low;
				/*if (vertices[i].low == vertices[i].visitado){
					bcnt++;
					cout << "ponte " << v << " - " << i << "\n";
				}*/
				if(vertices[i].low > vertices[v].num){
					//cout << "Ponto de articulacao - " << v << "\n";
					vertices[i].marcado = true;
				}
				vertices[v].low = (vertices[v].low < vertices[i].low) ? vertices[v].low : vertices[i].low;
			}
			else if (i!=vertices[v].anterior){
				vertices[v].low = (vertices[v].low < vertices[i].num) ? vertices[v].low : vertices[i].num;
				/*if(vertices[v].low > vertices[i].visitado){
					vertices[v].low = vertices[i].visitado;
				}*/
			}
		}
    }

}

int verificaPonte(Grafo* grafo, int tam){
	DFSdata *vertices  = new DFSdata[tam];
	int cnt = 0, bcnt = 0;
	
	for(int i=0; i<tam; i++){
		if(vertices[i].visitado == -1){
			findBridges(grafo, i, tam, cnt, bcnt, vertices);
		}
	}
	delete []vertices;
	return bcnt;
}

void verificaPontoDeArticulacao(Grafo* grafo, int tam) {
	DFSdata *vertices = new DFSdata[tam];
	int cnt = 0;
	for(int i=0; i<tam; i++){
		if(vertices[i].visitado == -1){
			cutVertices(grafo, i, tam, cnt, vertices);
		}
		for (int j = 0; j < tam; j++) {
			vertices[j].visitado = -1;
			vertices[j].num = -1;
			vertices[j].low = -1;
			vertices[j].anterior = -1;
		}
	}
	for (int j = 0; j < tam; j++) {
		if (vertices[j].marcado) {
			cout << "Ponto de articulacao - " << j << "\n";
		}
	}
	delete[] vertices;
	
}

int main() {
	int numOp;
	cout << "Seu grafo é orientado? (0 - Não, 1 - sim): ";
	cin >> numOp;
	bool orientado = (numOp == 1)? (true) : (false);
	
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
	verificaPontoDeArticulacao(grafo, tam);
	//cout << "Numero de pontes " << verificaPonte(grafo, tam) << "\n";
	return 0;
}

	

















