#include <iostream>
#include <fstream>
#include <cstdlib>
#include "grafos.cpp"
#include "objetos.cpp"

#define FORTEMENTE_CONEXO 3
#define SEMIFORTEMENTE_CONEXO 2
#define FRACAMENTE_CONEXO 1
#define DESCONEXO 0
#define INF 1000000

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
    cnt++;
    List vizinhos = grafo -> getVizinhos(u);

    for(int i = 0; i < vizinhos.size(); i++){  // percorre as arestas do vertice
		int v = vizinhos.get(i).getVerticeAlvo();
		if (!vertices[v].visitado){
			buscarVertices(grafo, v, vertices, cnt); // visita o vértice
		}
    }
    
	return cnt;
}

int verticesAlcancaveis (Grafo* grafo, int v, int tam) {
	int cnt = -1;
	DFSdata *vertices = new DFSdata[tam];
	int alcancaveis = buscarVertices(grafo, v, vertices, cnt);
	delete []vertices;
	return alcancaveis;
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

void checarConectividade (Grafo* grafo, int u, int* label, DFSdata* vertices, Stack* pilha) {
	static int cnt = 0;
	*pilha << u;
	vertices[u].num = vertices[u].low = cnt++;
	vertices[u].visitado = true;
	List vizinhos = grafo -> getVizinhos(u);

    for(int i = 0; i < vizinhos.size(); i++){  // percorre as arestas do vertice
		int v = vizinhos.get(i).getVerticeAlvo();
		if (!vertices[v].visitado){
			vertices[v].anterior = u;
			checarConectividade(grafo, v, label, vertices, pilha); // visita o vértice
			vertices[u].low = min(vertices[u].low, vertices[v].low);
		} else if (!vertices[v].marcado) {
			vertices[u].low = min(vertices[u].low, vertices[v].num);
		} else continue;
    }
    if (vertices[u].low == vertices[u].num) {
    	int v;
    	do {
    		*pilha >> v;
    		vertices[v].label = (vertices[v].label == -1) ? (*label) : (vertices[v].label);
    	} while (v != u);
    	(*label)++;
    }
}

void componentesFortementeConexas (Grafo* grafo, int& numVerticesConexos, int& numArestasConexas){
	DFSdata *vertices  = new DFSdata[grafo -> getQuantVertices()];
	Stack* pilha = new Stack;
	int* label = new int;
	(*label) = 0;
	for (int i = 0; i < grafo -> getQuantVertices(); i++) {
		if (!vertices[i].visitado) {
			checarConectividade (grafo, i, label, vertices, pilha);
		}
		for (int j = 0; j < grafo -> getQuantVertices(); j++) {
			if (vertices[j].visitado) {
				vertices[j].marcado = true;
			}
		}
	}
	numVerticesConexos = (*label);
	numArestasConexas = 0;
	for (int i = 0; i < grafo -> getQuantVertices(); i++) {
		List vizinhos = grafo -> getVizinhos(i);
		for (int j = 0; j < vizinhos.size(); j++) {
			int v = vizinhos.get(j).getVerticeAlvo();
			if (vertices[i].label != vertices[v].label) {
				numArestasConexas++;
			}
		}
	}
	delete[] vertices;
	delete pilha;
}

void fracamente(Grafo* grafo, int v, int& cnt, DFSdata* vertices){
	vertices[v].visitado = true; // marca como visitado
    vertices[v].num = cnt++;
	
	List vizinhos = grafo -> getVizinhos(v);
	for(int j = 0; j < vizinhos.size(); j++){  
		int i = vizinhos.get(j).getVerticeAlvo();
		if(vertices[i].visitado == false){
			fracamente(grafo, i, cnt, vertices);
		}
		
	}
}

bool desconexo (Grafo* grafo, int v, int& cnt,DFSdata* vertices,int raiz){
	vertices[v].visitado = true; // marca como visitado
    vertices[v].num = cnt++;
	
	List vizinhos = grafo -> getVizinhos(v);
	for(int j = 0; j < vizinhos.size(); j++){  
		int i = vizinhos.get(j).getVerticeAlvo();
		if(vertices[i].visitado == false){
			desconexo(grafo, i, cnt, vertices, raiz);
		}
		else if (vertices[raiz].num > vertices[i].num){
			return false;
		}
	}
	return true;
}

bool confirmarFracamente(Grafo* grafo){
	int tam = grafo -> getQuantVertices();
	DFSdata *vertices  = new DFSdata[tam];
	int cnt = 0;
	int aux = 0;
	int raiz = -1;
	
	for(int i=0; i<tam; i++){
		if(vertices[i].visitado == false and aux==0){
			
			fracamente(grafo, i, cnt, vertices);
			aux ++;
		}
		else if(!vertices[i].visitado){
			raiz = i;
			if(desconexo(grafo, i, cnt, vertices, raiz))
				return false;
		}
	}
	delete []vertices;
	return true;
}

int** floydWarshall (Grafo* grafo) {
	int** distancias = new int*[grafo -> getQuantVertices()];
	for (int i = 0; i < grafo -> getQuantVertices(); i++) {
		distancias[i] = new int[grafo -> getQuantVertices()];
	}
	for (int i = 0; i < grafo -> getQuantVertices(); i++) {
		for (int j = 0; j < grafo -> getQuantVertices(); j++) {
			if (i == j) {
				distancias[i][j] = 0;
			} else if (grafo -> isVizinho(i, j)) {
				distancias[i][j] = 1;
			} else {
				distancias[i][j] = INF;
			}
		}
	}
	for (int k = 0; k < grafo -> getQuantVertices(); k++) {
		for (int i = 0; i < grafo -> getQuantVertices(); i++) {
			for (int j = 0; j < grafo -> getQuantVertices(); j++) {
				distancias[i][j] = min(distancias[i][j], distancias[i][k] + distancias[k][j]);
			}
		}
	}
	return distancias;
}

int classificarConexidade (Grafo* grafo) {
	int** distancias = floydWarshall(grafo);
	int nivelConexao = FORTEMENTE_CONEXO;
	int i = 0, j = 0;
	bool linhaConexa;
	while (i < grafo -> getQuantVertices() and nivelConexao != DESCONEXO) {
		linhaConexa = false;
		j = 0;
		while (j < grafo -> getQuantVertices()) {
			if (distancias[i][j] >= INF) {
				if (distancias[j][i] == 1 and nivelConexao != FRACAMENTE_CONEXO) {
					nivelConexao = SEMIFORTEMENTE_CONEXO;
					linhaConexa = true;
				} else if (distancias[j][i] < INF) {
					nivelConexao = FRACAMENTE_CONEXO;
					linhaConexa = true;
				} else {
					nivelConexao = FRACAMENTE_CONEXO;
				}
			} else {
				linhaConexa = true;
			}
			j++;
		}
		if (!linhaConexa) {
			nivelConexao = DESCONEXO;
		}
		i++;
	}
	for (int i = 0; i < grafo -> getQuantVertices(); i++) {
		delete[] distancias[i];
	}
	delete[] distancias;
	return nivelConexao;
}


void imprimeAjuda () {
	cout << "Uso: ./TP1.bin nomeDoArquivo [parâmetros]" << endl << endl;
	cout << "Parâmetros aceitos:" << endl;
	cout << "-m TIPO_DE_GRAFO\t" << "Tipo de estrutura para o grafo." << endl;
	cout << "\t\t\t\t1 para Matriz de Adjacência" << endl;
	cout << "\t\t\t\t2 para Lista de Adjacência" << endl;
	cout << "\t\t\t\t3 para Matriz de Incidência" << endl << endl;
	cout << "-p1\t\t\t" << "Exibir resposta para o Problema 1" << endl;
	cout << "-p2\t\t\t" << "Exibir resposta para o Problema 2" << endl;
	cout << "-p3\t\t\t" << "Exibir resposta para o Problema 3." << endl;
	cout << "\t\t\t\t OBS: Será solicitado depois números inteiros representando vértices determinados." << endl;
	cout << "\t\t\t\t      Não os insira como parâmetros." << endl;
	cout << "-p4\t\t\t" << "Exibir resposta para o Problema 4" << endl;
	cout << "-p5\t\t\t" << "Exibir resposta para o Problema 5" << endl;
	cout << "-p6\t\t\t" << "Exibir resposta para o Problema 6" << endl;
}



int main(int argc, char** argv) {
	//Grafo* grafo;
	
	if (argc == 1) {
		imprimeAjuda();
	} else {
		int tipo = 1;
		bool p1, p2, p3, p4, p5, p6, solicitou;
		p1 = p2 = p3 = p4 = p5 = p6 = solicitou = false;
		string nomeArq (argv[1]);
		nomeArq += ".txt";
		for (int i = 2; i < argc; i++) {
			string param (argv[i]);
			if (param == "-m") {
				if ((i + 1) < argc) {
					int value = atoi(argv[i + 1]);
					if (value >= 1 and value <= 3) {
						tipo = value;
					}
				}
			} else if (param == "-p1") {
				p1 = solicitou = true;
			} else if (param == "-p2") {
				p2 = solicitou = true;
			} else if (param == "-p3") {
				p3 = solicitou = true;
			} else if (param == "-p4") {
				p4 = solicitou = true;
			} else if (param == "-p5") {
				p5 = solicitou = true;
			} else if (param == "-p6") {
				p6 = solicitou = true;
			}
		}
		if (solicitou) {
			ifstream arq (nomeArq.c_str());
			Grafo* grafo;
			if (arq.good()) {
				string opcao;
				bool orientado;
				arq >> opcao;
				if (opcao != "VERTEX_EDGES_FILE") {
					cout << "Arquivo não apropriado! Não foi encontrado o cabeçalho contendo \"VERTEX_EDGES_FILE\"" << endl;
					return -1;
				}
				arq >> opcao;
				if (opcao == "UNDIRECTED") {
					orientado = false;
				} else {
					orientado = true;
				}
				if(tipo == 1){
					grafo = new MatrizDeAdjacencia(orientado);
				} else if(tipo == 2){
					grafo = new ListaDeAdjacencia(orientado);
				} else if(tipo == 3){
					grafo = new MatrizDeIncidencia(orientado);
				}
				
				arq >> opcao;
				int tam, u, v;
				arq >> tam;
				grafo -> adicionarVertices(tam);
				do{
					arq >> u;
					arq >> v;
					try{
						grafo -> adicionarAresta(u, v, 1);
					} catch (EdgeInsertionException e) {
						
					}
				}while(arq.good());
				arq.close();

				int* verticesPraTestar = NULL;
				int quantos;

				if (p3) {
					cout << "Quantos vértices deseja testar para o P3? ";
					cin >> quantos;
					cout << "Quais? " << endl;
					verticesPraTestar = new int[quantos];
					for (int i = 0; i < quantos; ++i) {
						cin >> verticesPraTestar[i];
					}
				}

				if (p1) {
					cout << "P1: " << verificaPonte(grafo, tam) << endl;
				}
				if (p2) {
					cout << "P2: " << verificaPontoDeArticulacao(grafo, tam) << endl;
				}
				if (p3) {
					cout << "P3: ";
					for (int i = 0; i < quantos; ++i) {
						cout << verticesAlcancaveis(grafo, verticesPraTestar[i], tam) << " ";
					}
					cout << endl;
				}
				if (p4) {
					cout << "P4: " << calcularDiametro(grafo, tam) << endl;
				}
				
				if (p5) {
					int conexidade = classificarConexidade(grafo);
					if (conexidade == FORTEMENTE_CONEXO) {
						cout << "FORTEMENTE CONEXO";
					} else if (conexidade == SEMIFORTEMENTE_CONEXO) {
						cout << "SEMIFORTEMENTE CONEXO";
					} else if (conexidade == FRACAMENTE_CONEXO) {
						if(confirmarFracamente(grafo))
							cout << "FRACAMENTE CONEXO";
						else cout << "DESCONEXO";
						
					} else {
						cout << "DESCONEXO";
					}
					cout << endl;
				}
				if (p6) {
						int numVerticesConexos, numArestasConexas;
						componentesFortementeConexas(grafo, numVerticesConexos, numArestasConexas);
						cout << "Quantidade de vértices no grafo simplificado: " << numVerticesConexos << endl;
						cout << "Quantidade de arestas no grafo simplificado: " << numArestasConexas << endl;
				}
				delete grafo;
				delete[] verticesPraTestar;
			} else {
				cout << "Arquivo não encontrado! Certifique-se de que o nome esteja correto e NÃO adicione extensão .txt, apenas o nome basta!" << endl;
			}
			
		}
	}
	return 0;
}
