#include "ros/ros.h"
using namespace std;

// Funciones
void reset(int *array);
void show(int *array);
int check(int *array);
void ClearScreen();

// Variables globales
int estado = 0;

int main(int argc, char **argv) {
	
	//int malla[9];
	int malla[9] = {0,-1,-1,1,1,1,0,1,0};
	bool out = 0;
	
	while(!out)
	{
		// Maquina de estados
		switch(estado)
		{
			case 0:		// reset
				//reset(malla);
				show(malla);
				estado = 1;
				break;
			case 1:		// start
				cout << "Empieza el juego" << endl;
				
				cout << check(malla) << endl;
				estado = -1;
				break;
			case 2:		// win
				cout << "Gano x" << endl;
				break;
			default:	// exit
				out = 1;
		}
	}
}

// Funciones
void reset(int *array)
{
	for(int i=0; i<9; i++)
		array[i] = -1;
}

void show(int *array)
{
	char array_show[9];
	for(int i=0; i<9; i++)
	{
		switch(array[i])
		{
			case 0:
				array_show[i] = 'o';
				break;
			case 1:
				array_show[i] = 'x';
				break;
			default:
				array_show[i] = ' ';
		}
	}
	
	// Raw array
	cout << endl;
	for(int i=0; i<3; i++)
	{
		cout << "\t" << array[i*3] << " | " << array[i*3+1] << " | " << array[i*3+2] << endl;
		if(i!=2)
			cout << "\t" << "---------" << endl;
	}
	cout << endl;
	
	// Arranged array
	cout << endl;
	for(int i=0; i<3; i++)
	{
		cout << "\t" << array_show[i*3] << " | " << array_show[i*3+1] << " | " << array_show[i*3+2] << endl;
		if(i!=2)
			cout << "\t" << "---------" << endl;
	}
	cout << endl;
}

int check(int *array)
{
	int winner;		// Indica la ficha ganadora
	bool win = 1;	// Indica si hay victoria
	
	// Comprobacion filas horizontales
	for(int i=0; i<3; i++)
	{
		if(array[i*3]!=-1)
		{
			winner = array[i*3];
			win = 1;
			for(int j=1; j<3;j++)	// Compruebo por toda la fila si alguna celda no corresponde con la primera
				if(array[i*3+j] != winner)
					win = 0;
		}
		if(win)
			break;
	}
	
	if(win)
		return winner;
	return -1;
}

void ClearScreen()
{
	cout << string( 100, '\n' );
}
