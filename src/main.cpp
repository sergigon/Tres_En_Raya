#include "ros/ros.h"
using namespace std;

// Variables globales
const int size = 3;
int estado = 0;

// Funciones
void ClearScreen();

// Clases
class Tablero {
	private:
		int malla[size][size];
		int winner;
	public:
		Tablero();
		Tablero(int array[size][size]);
		~Tablero();
		void initialize(int array[size][size]);
		void reset();
		void show();
		void write(bool player);
		int check();
};

class NeuralNet {
	private:
		int nLayers;
		int sizeLayer;
		int sizeInput;
		vector< vector<float> > weights;
		vector<float> bias;
		vector<float> input;
		vector<float> output;
	public:
		NeuralNet(int sizeL, int sizeI);
		NeuralNet(vector< vector<int> > w, vector<int> bias);
		~NeuralNet();
		void random();
		void show();
		void start(vector<int> in);
		void start(int array[size][size]);
};

int main(int argc, char **argv)
{
	bool out = 0;
	bool player = 0;
	int winner = -1;
	
	int malla[size][size] = {
		{0,-1,1},
		{1,1,0},
		{0,1,1}
	};
	
	Tablero tablero;
	NeuralNet network(2, 9);
	
	vector<int> vec;
	vec.push_back(0);
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);
	vec.push_back(5);
	vec.push_back(6);
	vec.push_back(7);
	vec.push_back(8);
	
	network.start(malla);
	network.show();
	
	while(!out)
	{
		// Maquina de estados
		switch(estado)
		{
			case 0:		// reset
				//ClearScreen();
				tablero.reset();
				//tablero.initialize(malla);
				player = 0;
				winner = -1;
				tablero.show();
				estado = 1;
				break;
				
			case 1:		// start
				cout << "Empieza el juego" << endl;
				while(estado == 1)
				{
					cout << "-- Turno de ";
					if(player)
						cout << "x:";
					else
						cout << "o:";
					cout << " --" << endl;
					tablero.write(player);
					player = !player;	// Cambio de jugador
					tablero.show();
					winner = tablero.check();
					if(winner!=-1)
						estado = 2;
				}
				break;
				
			case 2:		// win
				switch(winner)
				{
					case 0:
						cout << "#########################" << endl;
						cout << "#\t";
						cout << "Gano o";
						cout << "\t\t#" << endl;
						cout << "#########################" << endl;
						break;
					case 1:
						cout << "#########################" << endl;
						cout << "#\t";
						cout << "Gano x";
						cout << "\t\t#" << endl;
						cout << "#########################" << endl;
						break;
					default:
						cout << "#########################" << endl;
						cout << "#   ";
						cout << "Partida terminada";
						cout << "   #" << endl;
						cout << "#########################" << endl;
						break;
				}
				
				cout << endl;
				estado = 3;
				break;
				
			default:	// exit
				int answer = 0;
				cout << "Se acabo el juego" << endl;
				cout << "¿Quieres jugar otra partida? (1->Si, 0->No)" << endl;
				cin >> answer;
				if(answer)
					estado = 0;
				else
					out = 1;
		}
	}
}

// Funciones
Tablero::Tablero()
{
	reset();
	winner = -1;
}

Tablero::Tablero(int array[size][size])
{
	initialize(array);
}

Tablero::~Tablero(){}

void Tablero::initialize(int array[size][size])
{
	for(int i=0; i<size; i++)
		for(int j=0; j<size; j++)
			malla[i][j] = array[i][j];
}

void Tablero::reset()
{
	for(int i=0; i<size; i++)
		for(int j=0; j<size; j++)
			malla[i][j] = -1;
}

void Tablero::show()
{
	char array_show[size][size];
	for(int i=0; i<size; i++)
		for(int j=0; j<size; j++)
			switch(malla[i][j])
			{
				case 0:
					array_show[i][j] = 'o';
					break;
				case 1:
					array_show[i][j] = 'x';
					break;
				default:
					array_show[i][j] = ' ';
			}

	// Arranged array
	cout << endl;
	for(int i=0; i<size; i++)
		cout << "\t" << array_show[i][0] << " | " << array_show[i][1] << " | " << array_show[i][2] << endl;
	cout << endl;
}

void Tablero::write(bool player)
{
	int row = -1;
	int col = -1;
	bool again = 1;
	while(again == 1)
	{
		row = -1;
		col = -1;
		while(row<1 or row>3)
		{
			cout << "Elige fila: ";
			cin >> row;
		}
		while(col<1 or col>3)
		{
			cout << "Elige columna: ";
			cin >> col;
		}
		if(malla[row-1][col-1]==-1)
			again = 0;
		else
			cout << "Ya hay una ficha, prueba otra vez" << endl;
	}
	malla[row-1][col-1] = player;
}

int Tablero::check()
{
	int winner_check;	// Winner: Indica la ficha ganadora
						// -1 -> No hay ganador
						//  0 -> Ganador o
						//  1 -> Ganador x
						//  2 -> Tablero completo
	bool win = 0;	// Indica si hay victoria
	
	// Comprobacion filas horizontales
	for(int i=0; i<size; i++)
	{
		if(malla[i][0]!=-1)
		{
			winner_check = malla[i][0];
			win = 1;
			for(int j=1; j<size;j++)	// Compruebo por toda la fila si alguna celda no corresponde con la primera
				if(malla[i][j] != winner_check)
					win = 0;
		}
		if(win)
		{
			winner = winner_check;
			return winner;
		}
	}
	
	// Comprobacion filas verticales
	for(int j=0; j<size; j++)
	{
		if(malla[0][j]!=-1)
		{
			winner_check = malla[0][j];
			win = 1;
			for(int i=1; i<size;i++)	// Compruebo por toda la fila si alguna celda no corresponde con la primera
				if(malla[i][j] != winner_check)
					win = 0;
		}
		if(win)
		{
			winner = winner_check;
			return winner;
		}
	}
	
	// Comprobacion filas diagonales
	if(malla[0][0]!=-1)
	{
		win = 1;
		winner_check = malla[0][0];
		for(int i=1; i<size;i++)
			if(malla[i][i] != winner_check)
				win = 0;
	}
	if(win)
	{
		winner = winner_check;
		return winner;
	}
	if(malla[0][size-1]!=-1)
	{
		win = 1;
		winner_check = malla[0][size-1];
		for(int i=1; i<size;i++)
			if(malla[i][size-1-i] != winner_check)
				win = 0;
	}
	if(win)
	{
		winner = winner_check;
		return winner;
	}
	
	// Comprobacion tablero completo
	bool full = 1;
	for(int i=0; i<size; i++)
		for(int j=0; j<size; j++)
			if(malla[i][j]==-1)
				full = 0;
	if(full==1)
	{
		winner = 2;
		return winner;
	}
	
	winner = -1;
	return winner;
}

NeuralNet::NeuralNet(int sizeL, int sizeI)
{
	nLayers = 1;
	sizeLayer = sizeL;
	sizeInput = sizeI;
	random();
}

//NeuralNet::NeuralNet(vector< vector<int> > w, vector<int> bias);

NeuralNet::~NeuralNet(){}

void NeuralNet::random()
{
	srand(time(NULL)); /* seed random number generator */
	
	// Borro el vector
	weights.erase(weights.begin(),weights.end());
	
	// Inicializo el vector
	vector<float> weights_aux;
	for(int i=0; i<sizeLayer; i++)
	{
		weights_aux.erase(weights_aux.begin(),weights_aux.end());
		for(int j=0; j<sizeInput; j++)
			weights_aux.push_back(float(rand() % 11)/10);
		weights.push_back(weights_aux);
	}
}

void NeuralNet::show()
{
	// Show weights
	for(int i=0; i<sizeLayer; i++)
	{
		for(int j=0; j<sizeInput; j++)
			cout << weights[i][j] << "\t";
		cout << endl;
	}
	cout << endl;
	
	// Show input
	for(int i=0; i<input.size(); i++)
		cout << input[i] << endl;
	cout << endl;
	
	// Show output
	for(int i=0; i<output.size(); i++)
		cout << output[i] << endl;
	cout << endl;
	
}

void NeuralNet::start(vector<int> in)
{
	if(in.size()!=sizeInput)
	{
		cout << "El tamaño del vector input no coincide con el de la red neuronal" << endl;
		cout << "Por favor, introduce un un vector de tamaño " << sizeInput << endl;
		cout << endl;
		return;
	}
	
	// out = f(w*in + b)
	
	// Borro el vector input y output
	output.erase(output.begin(),output.end());
	input.erase(input.begin(),input.end());
	
	// Completo vector input
	for(int i=0; i<sizeInput; i++)
		input.push_back(in[i]);
	
	for(int i=0; i<sizeLayer; i++)
	{
		float aux = 0;
		for(int j=0; j<sizeInput; j++)
			aux = weights[i][j]*in[j] + aux;
		output.push_back(aux);
	}
}

void NeuralNet::start(int array[size][size])
{
	vector<int> auxVec;
	for(int i=0; i<size; i++)
		for(int j=0; j<size; j++)
			auxVec.push_back(array[i][j]);
	start(auxVec);
}

void ClearScreen()
{
	cout << string( 100, '\n' );
}
