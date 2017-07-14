#include <iostream>

using namespace std;

class DFSdata{
public:
	int visitado;
	int low;
	int num;
	int anterior;
	bool marcado;
	
	DFSdata(){
		visitado = -1;
		anterior = -1;
		marcado = false;
	}
};

