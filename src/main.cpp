#include "ros/ros.h"
using namespace std;

// Variables globales
const int size = 3;
int estado = 0;

// Funciones
void reset(int array[][size]);
void show(int array[][size]);
void write(bool player, int array[][size]);
int check(int array[][size]);
void ClearScreen();

int main(int argc, char **argv)
{
	bool out = 0;
	bool player = 0;
	int winner = -1;
	int answer = 0;
	int malla[size][size] = {
		{0,-1,0},
		{1,0,0},
		{0,1,1}
	};
	
	while(!out)
	{
		// Maquina de estados
		switch(estado)
		{
			case 0:		// reset
				ClearScreen();
				reset(malla);
				show(malla);
				estado = 1;
				break;
				
			case 1:		// start
				cout << "Empieza el juego" << endl;
				while(estado == 1)
				{
					player = !player;
					write(player, malla);
					show(malla);
					winner = check(malla);
					if(winner!=-1)
						estado = 2;
				}
				break;
				
			case 2:		// win
				switch(winner)
				{
					case 0:
						cout << "Gano o" << endl;
						break;
					case 1:
						cout << "Gano x" << endl;
						break;
					default:
						cout << "Partida terminada" << endl;
						break;
				}
				estado = 3;
				break;
				
			default:	// exit
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
void reset(int array[][size])
{
	for(int i=0; i<size; i++)
		for(int j=0; j<size; j++)
			array[i][j] = -1;
}

void show(int array[][size])
{
	char array_show[size][size];
	for(int i=0; i<size; i++)
		for(int j=0; j<size; j++)
			switch(array[i][j])
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
	/*
	// Raw array
	cout << endl;
	for(int i=0; i<size; i++)
		cout << "\t" << array[i][0] << " | " << array[i][1] << " | " << array[i][2] << endl;
	cout << endl;
	*/
	// Arranged array
	cout << endl;
	for(int i=0; i<size; i++)
		cout << "\t" << array_show[i][0] << " | " << array_show[i][1] << " | " << array_show[i][2] << endl;
	cout << endl;
}

void write(bool player, int array[][size])
{
	int row = -1;
	int col = -1;
	bool again = 1;
	while(again==1)
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
		if(array[row-1][col-1]==-1)
			again = 0;
		else
			cout << "Ya hay una ficha, prueba otra vez" << endl;
	}
	array[row-1][col-1] = player;
}

int check(int array[][size])
{
	int winner;		// Indica la ficha ganadora
					// -1 -> No hay ganador
					// 0  -> Ganador o
					// 1  -> Ganador x
					// 2  -> Tablero completo
	bool win = 0;	// Indica si hay victoria
	
	// Comprobacion filas horizontales
	for(int i=0; i<size; i++)
	{
		if(array[i][0]!=-1)
		{
			winner = array[i][0];
			win = 1;
			for(int j=1; j<size;j++)	// Compruebo por toda la fila si alguna celda no corresponde con la primera
				if(array[i][j] != winner)
					win = 0;
		}
		if(win)
			return winner;
	}
	
	// Comprobacion filas verticales
	for(int j=0; j<size; j++)
	{
		if(array[0][j]!=-1)
		{
			winner = array[0][j];
			win = 1;
			for(int i=1; i<size;i++)	// Compruebo por toda la fila si alguna celda no corresponde con la primera
				if(array[i][j] != winner)
					win = 0;
		}
		if(win)
			return winner;
	}
	
	// Comprobacion filas diagonales
	if(array[0][0]!=-1)
	{
		win = 1;
		winner = array[0][0];
		for(int i=1; i<size;i++)
			if(array[i][i] != winner)
				win = 0;
	}
	if(win)
		return winner;
	if(array[0][size-1]!=-1)
	{
		win = 1;
		winner = array[0][size-1];
		for(int i=1; i<size;i++)
			if(array[i][size-1-i] != winner)
				win = 0;
	}
	if(win)
		return winner;
	
	// Comprobacion tablero completo
	bool full = 1;
	for(int i=0; i<size; i++)
		for(int j=0; j<size; j++)
			if(array[i][j]==-1)
				full = 0;
	if(full==1)
		return 2;
	
	return -1;
}

void ClearScreen()
{
	cout << string( 100, '\n' );
}
