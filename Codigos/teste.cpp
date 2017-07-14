#include <iostream>
#include "grafos.cpp"

using namespace std;

void testStack () {
	Stack s1;
	int n;
	string res;
	s1 >> res;
	cout << res << endl;
	cin >> n;
	do {
		s1 << n;
		cin >> n;
	} while (n != 0);
	s1 >> res;
	cout << res << endl;
	int x;
	cout << "Type '0' to exit" << endl;
	cin >> x;
	while (x != 0) {
		try {
			s1 >> n;
			s1 >> res;
			cout << n << " was destacked!" << endl << res << endl;
			cin >> x;
		} catch (DataStructureException e) {
			cerr << e.what() << endl;
			x = 0;
		}
	}
}

void testQueue () {
	Queue q1;
	int n;
	string res;
	q1 >> res;
	cout << res << endl;
	cin >> n;
	do {
		q1 << n;
		cin >> n;
	} while (n != 0);
	q1 >> res;
	cout << res << endl;
	int x;
	cout << "Type '0' to exit" << endl;
	cin >> x;
	while (x != 0) {
		try {
			q1 >> n;
			q1 >> res;
			cout << n << " was destacked!" << endl << res << endl;
			cin >> x;
		} catch (DataStructureException e) {
			cerr << e.what() << endl;
			x = 0;
		}
	}
}


/*void testList () {
	List l1;
	InformacoesDeAresta n;
	string res;
	l1 >> res;
	cout << res << endl;
	cin >> n;
	while (n != 0) {
		l1.insertR(n);
		cin >> n;
	}
	l1 >> res;
	cout << res << endl;
	int x;
	cout << "Type '-1' to exit" << endl;
	cin >> x;
	while (x != -1) {
		try {
			n = l1.pull(x);
			l1 >> res;
			cout << n << " was destacked!" << endl << res << endl;
		} catch (IndexOutOfBoundsException e) {
			cerr << e.what() << endl;
		}
		cin >> x;
	}
}
*/

void testGarfos () {
	int numOp;
	cout << "Orientado ou não? (0 - Nope, 1- Yep) ";
	cin >> numOp;
	bool orientado = (numOp == 0) ? (false) : (true);
	Grafo* g1;
	cout << "1 - Matriz de Adjacencia" << endl;
	cout << "2 - Lista de Adjacencia" << endl;
	cout << "3 - Matriz de Incidencia" << endl;
	cout << "" << endl << "Qual vai ser? ";
	cin >> numOp;
	switch (numOp) {
		case 2:
			g1 = new ListaDeAdjacencia (orientado);
			break;
		case 3:
			g1 = new MatrizDeIncidencia (orientado);
			break;
		default:
			g1 = new MatrizDeAdjacencia (orientado);
			break;
	}
	cout << (g1 -> getRepresentacao()) << endl;
	int q, n;
	cout << "Quantos vértices? ";
	cin >> n;
	g1 -> adicionarVertices(n);
	do {
		int v1, v2;
		cout << "ORIGEM DESTINO:" << endl;
		cin >> v1 >> v2;
		try {
			g1 -> adicionarAresta(v1, v2, 1);
		} catch (EdgeInsertionException e) {
			cerr << e.what() << endl;
		}
		cout << "Mais? (0 pra sair, 1 pra continuar) ";
		cin >> q; 
	} while (q != 0);
	cout << (g1 -> getRepresentacao()) << endl;
	g1 -> adicionarVertices(2);
	g1 -> adicionarVertices(2);
	cout << (g1 -> getRepresentacao()) << endl;
	cout << "Quer a lista de vizinhos de quem? ";
	cin >> n;
	List vizinhos = g1 -> getVizinhos(n);
	string vizinhanca;
	vizinhos >> vizinhanca;
	cout << vizinhanca << endl;
}

int main () {
	//testStack();
	//testQueue();
	//testList();
	testGarfos();
	return 0;
}
