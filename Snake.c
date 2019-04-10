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
	printf("________________________________________\n");
	for (i = 0; i < tv; i++) //for anidado para crear el tablero
	{
		printf("|");
		for (j = 0; j < th; j++)
		{
			tablero[i][j] = ' ';
		}
		printf("|\n");
	}
	printf("________________________________________");
	srand(time(NULL));
	i = (rand() % tv); //posición aleatoria para la manzana
	j = (rand() % th);
	a = i; //a y b son las coordenadas de la manzana
	b = j;
	system("color A4"); //cambio de color a fondo verde y elementos rojos
	tablero[i][j] = 254;
	i = (rand() % tv); //posición aleatoria para la serpiente
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
			tablero[v + 1][w] = ' ';
			if (tablero[v + 1][w] == tablero[a][b])
			{
				i = (rand() % tv); //posición aleatoria para la manzana
				j = (rand() % th);
				a = i; //a y b son las coordenadas de la manzana
				b = j;
				tablero[i][j] = 254;
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
			break;

		case 80:
			system("cls");
			v = v + 1;
			tablero[v][w] = 178;
			tablero[v - 1][w] = ' ';
			if (tablero[v - 1][w] == tablero[a][b])
			{
				i = (rand() % tv); //posición aleatoria para la manzana
				j = (rand() % th);
				a = i; //a y b son las coordenadas de la manzana
				b = j;
				tablero[i][j] = 254;
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
			break;

		case 75:
			system("cls");
			w = w - 1;
			tablero[v][w] = 178;
			tablero[v][w + 1] = ' ';
			if (tablero[v][w + 1] == tablero[a][b])
			{
				i = (rand() % tv); //posición aleatoria para la manzana
				j = (rand() % th);
				a = i; //a y b son las coordenadas de la manzana
				b = j;
				tablero[i][j] = 254;
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
			break;

		case 77:
			system("cls");
			w = w + 1;
			tablero[v][w] = 178;
			tablero[v][w - 1] = ' ';
			if (tablero[v][w + 1] == tablero[a][b])
			{
				i = (rand() % tv); //posición aleatoria para la manzana
				j = (rand() % th);
				a = i; //a y b son las coordenadas de la manzana
				b = j;
				tablero[i][j] = 254;
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
			break;
		}
	}
	return 0;
}