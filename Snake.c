#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include <malloc.h>
#define tv 20
#define th 40
int main()
{
	int i, j, v, w, a, b;
	char mando;
	char tablero[tv][th];
	printf("Bienvenido al juego de snake.\nUtiliza las flechas para mover a tu serpiente y presiona esc para abandonar la partida.\nCualquier otra tecla que no sirva para mover la serpiente no funcionara.\n");
	system("pause");
	system("cls");
	for (i = 0; i < tv; i++)
	{
		for (j = 0; j < th; j++)
		{
			tablero[i][j] = ' ';
		}
	}
	srand(time(NULL));
	i = (rand() % tv); //posici�n aleatoria para la manzana
	j = (rand() % th);
	a = i; //a y b son las coordenadas de la manzana
	b = j;
	system("color A4"); //cambio de color a fondo verde y elementos rojos
	tablero[i][j] = 254;
	i = (rand() % tv); //posici�n aleatoria para la serpiente
	j = (rand() % th);
	v = i; //v y w son las coordenadas de la serpiente
	w = j;
	tablero[i][j] = 178;
	printf("________________________________________\n");
	for (i = 0; i < tv; i++) //for para colocar la manzana y la serpiente
	{
		printf("|");
		for (j = 0; j < th; j++)
		{
			printf("%c", tablero[i][j]);
		}
		printf("|\n");
	}
	printf("________________________________________");
	mando = getch();
	while (mando != 27)
	{
		mando = getch();
		switch (mando) //Ejecuta la orden
		{
		case 72:
			system("cls");
			v = v - 1;
			tablero[v][w] = 178;
			if (tablero[v + 1][w] == tablero[a][b])
			{
				i = (rand() % tv); //posici�n aleatoria para la manzana
				j = (rand() % th);
				a = i; //a y b son las coordenadas de la manzana
				b = j;
				tablero[i][j] = 254;
				tablero[v + 1][w] = 178; //Hace que la serpiente aparezca un cuadrado m�s larga
			}
			else
				tablero[v + 1][w] = ' '; //Si no toca la manzana, se elimina la serpiente en la coordenada anterior y �nicamente aparece como un cuadrado
			break;

		case 80:
			system("cls");
			v = v + 1;
			tablero[v][w] = 178;
			if (tablero[v - 1][w] == tablero[a][b])
			{
				i = (rand() % tv); //posici�n aleatoria para la manzana
				j = (rand() % th);
				a = i; //a y b son las coordenadas de la manzana
				b = j;
				tablero[i][j] = 254;
				tablero[v - 1][w] = 178; //Hace que la serpiente aparezca un cuadrado m�s larga
			}
			else
				tablero[v - 1][w] = ' '; //Si no toca la manzana, se elimina la serpiente en la coordenada anterior y �nicamente aparece como un cuadrado
			break;

		case 75:
			system("cls");
			w = w - 1;
			tablero[v][w] = 178;
			if (tablero[v][w + 1] == tablero[a][b])
			{
				i = (rand() % tv); //posici�n aleatoria para la manzana
				j = (rand() % th);
				a = i; //a y b son las coordenadas de la manzana
				b = j;
				tablero[i][j] = 254;
				tablero[v][w + 1] = 178; //Hace que la serpiente aparezca un cuadrado m�s larga
			}
			else
				tablero[v][w + 1] = ' '; //Si no toca la manzana, se elimina la serpiente en la coordenada anterior y �nicamente aparece como un cuadrado
			break;

		case 77:
			system("cls");
			w = w + 1;
			tablero[v][w] = 178;
			if (tablero[v][w - 1] == tablero[a][b])
			{
				i = (rand() % tv); //posici�n aleatoria para la manzana
				j = (rand() % th);
				a = i; //a y b son las coordenadas de la manzana
				b = j;
				tablero[i][j] = 254;
				tablero[v][w - 1] = 178; //Hace que la serpiente aparezca un cuadrado m�s larga
			}
			else
				tablero[v][w - 1] = ' '; //Si no toca la manzana, se elimina la serpiente en la coordenada anterior y �nicamente aparece como un cuadrado
			
			break;
		}
		printf("________________________________________\n");
		for (i = 0; i < tv; i++)
		{
			printf("|");
			for (j = 0; j < th; j++)
			{
				printf("%c", tablero[i][j]);
			}
			printf("|\n");
		}
		printf("________________________________________");
	}
	return 0;
}
/*Problema:
No se mueve el segundo cuadrado de la serpiente.
�Asignaci�n din�mica de memoria?*/