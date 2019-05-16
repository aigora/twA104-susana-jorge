#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>

void titulo();

void cartas(int v, int car, char pal);


void main()
{
	FILE *ofpt;
	int numero = 20, i, j, a = 2, r = 1, c, y = 0;
	float dinero[20], apuesta[20];
	int card[8][20], valor[20];
	char palo[4] = { '+','-','/','^' }, decis = 'y', suit[8][20];
	//numero numero de jugadores
	// i,j variables de los for
	// a coger una carta aleatoria
	// dinero dinero de cada jugador
	// apuesta la apuesta de cada jugador en la ronda
	// r  ronda
	// card las cartas de cada jugador
	// suit el palo de las cartas de cada jugador
	// palo[4] los cuatro palos posibles
	// valor suma del valor de las cartas de cada jugador
	// decis decision de si jugar otra ronda 
	// c lineas de impresion de las cartas
	// y flag si alguien se queda sin dinero
	
	system("pause");

	titulo();
	srand(time(NULL));

	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 20; j++)
		{
			card[i][j] = 0;
		}
	}

	if ((ofpt = fopen("saved.txt", "r")) == NULL)//leer
		printf("Error : No Se Pudo Abrir El Archivo\n");//se abren los archivos
	  //inicio___________________________________________________________________________________________________________________
	else
	{
		printf("  __________________________________ \n");
		printf(" |\t\t\t\t    |\n");
		printf("    Cuantos Jugadores Vais A Ser? ");
		scanf("%d", &numero);
		while (numero <= 0||numero>20)
		{           //cor n jugadores
			printf("    Cantidad Incorrecta\n");
			printf("    Cuantos Jugadores? ");
			scanf("%d", &numero);
		}
		printf(" |__________________________________|\n");
		printf("  ______________________________________________________ \n");
		printf(" |\t\t\t\t\t\t\t|\n");
		printf("    Le Gustaria Jugar Un Juego Previo?(y/n) ");
		scanf(" %c", &decis);
		while (decis != 'y'&&decis != 'n')
		{       //corr decis
			printf("\t\t\tVuelve A Intentar(y/n) ");
			scanf(" %c", &decis);
		}
		if (decis == 'y')
		{
			for (j = 0; j < numero; j++)
			{
				fscanf(ofpt, "%f", &dinero[j]);
				while (dinero[j] <= 0)
					{
						printf("   Jugador %d Cuanto Dinero? $", j + 1);
						scanf("%f", &dinero[j]);
					} 
				printf("   Jugador %d Tiene = $%.f\n", j + 1, dinero[j]);
			}
		}
		printf(" |______________________________________________________|\n");
		Sleep(3000);
		if (decis == 'n')
		{
			printf("  ______________________________________ \n");
			printf(" |\t\t\t\t\t|\n");
			for (j = 0; j < numero; j++)
			{
				do
				{
					printf("   Jugador %d , Cuanto Dinero Tiene? $", j + 1);
					scanf("%f", &dinero[j]);
				}while (dinero[j] <= 0);
			}
			printf(" |______________________________________|\n");
		}
		decis = 'y'; //para no añadir mas variables la reusamos
	//rondas___________________________________________________________________________________________________________________________
		while (decis == 'y')
		{
			system("cls");
			printf("\n  Ronda %d\n", r);
			printf("  _______________________________________________ \n");
			printf(" |\t\t\t\t\t\t |\n");
			for (j = 0; j < numero; j++)
			{
				printf("    Jugador %d Cuanto Quiere Apostar? $", j + 1);
				scanf("%f", &apuesta[j]);
				while (apuesta[j] > dinero[j] || apuesta[j] <= 0)
				{
					printf("    No Puede Apostar Mas De Lo Que Tiene o <0\n\n");
					printf("    Jugador %d Cuanto Quiere Apostar? $", j + 1);
					scanf("%f", &apuesta[j]);
				}
			}
			printf(" |_______________________________________________|\n");
			//jugadores________________________________________________________________________________________________________________________
			system("cls");
			for (j = 0; j < numero; j++)
			{
				valor[j] = 0;//el valor es porque sino se estaria sumando las cartas con las de las rondas anteriores
				printf("  __________________________________________________ \n");
				printf(" |\t\t\t\t\t\t    |\n");
				printf("    El Jugador %d Tiene Las Cartas\n", j + 1);
				for (i = 0; i <= 1; i++)
				{
					a = (rand() % 13) + 1;
					card[i][j] = a;
					a = rand() % 4;
					suit[i][j] = palo[a];
				}
				for (c = 1; c < 7; c++)
				{
					for (a = 0; a < i; a++)
					{
						cartas(c, card[a][j], suit[a][j]);
					}
					printf("\n");
				}
				printf("\n |__________________________________________________|\n");
				printf("  ______________________________________________________________________________ \n");
				printf(" |\t\t\t\t\t\t\t\t\t\t|\n");
				printf("    Jugador %d Quiere Una Tercera Carta(y/n)? ", j + 1);
				scanf(" %c", &decis);
				while (decis != 'y'&&decis != 'n')
				{
					printf("\t\t\t  Intenta Otra Vez (y/n)  ");
					scanf(" %c", &decis);
				}
				while (decis == 'y'&&i <= 7)
				{
					system("cls");
					a = (rand() % 13) + 1;
					card[i][j] = a;
					a = rand() % 4;
					suit[i][j] = palo[a];
					for (c = 1; c < 7; c++)
					{
						for (a = 0; a <= i; a++)
						{
							cartas(c, card[a][j], suit[a][j]);
						}
						printf("\n");
					}
					a = 0;
					printf("\n\t     Quiere Otra Carta(y/n)? ");
					scanf(" %c", &decis);
					while (decis != 'y'&&decis != 'n')
					{
						printf("\t\t\t   Intenta Otra Vez(y/n)  ");
						scanf(" %c", &decis);
					}
					i++;
				}
				a = 0;
				for (i = 0; i <= 7; i++)
				{
					if (card[i][j] >= 10)
						card[i][j] = 10;
					if (card[i][j] == 1)
					{
						a = 2;
						printf("\n\n\t     Elige Valor Para 1 o 11 = ");
						scanf("%d", &card[i][j]);
						while (card[i][j] != 1 && card[i][j] != 11)
						{
							printf("\t     Vuelve A Elegir (1 o 11) = ");
							scanf("%d", &card[i][j]);
						}
					}
					valor[j] += card[i][j];
				}
				//printf("\t\t\t\t\t\t\t= %.f\n",valor[j]);
				printf(" |______________________________________________________________________________|\n");
				system("cls");
				for (i = 0; i <= 7; i++)
				{
					card[i][j] = 0;//para borrar todas las cartas anteriores
				}
			}//casa__________________________________________________________________________________________________________________________
			i = 0;
			valor[numero] = 0;
			while (valor[numero] < 17)
			{
				a = (rand() % 13) + 1;
				card[i][numero] = a;
				a = rand() % 4;
				suit[i][numero] = palo[a];
				if (card[i][numero] >= 10)
					card[i][numero] = 10;
				valor[numero] += card[i][numero];
				if (valor[numero] == 11)
				{
					a = i;
					for (a = 0; a <= i; a++)
					{
						if (card[a][numero] == 1)
							valor[numero] = 21;
					}
				}
				i++;
			}
			printf("  ______________________________________________________________________________\n");
			printf(" |\t\t\t\t\t\t\t\t\t\t|\n");
			printf("    La Casa Tiene Las Cartas :\n");
			for (c = 1; c < 7; c++)
			{
				for (a = 0; a < i; a++)
				{
					cartas(c, card[a][numero], suit[a][numero]);
				}
				printf("\n");
			}
			printf("\t\t\t\t\t\t\t= %.d\n", valor[numero]);
			printf(" |______________________________________________________________________________|\n");
			printf("  ______________________________________________________ \n");
			printf(" |\t\t\t\t\t\t\t|\n");
			//resultado_________________________________________________________________________________________________________________________________
			for (j = 0; j < numero; j++)
			{
				if (valor[j] == 21)
				{
					printf("   Jugador %d Con BLACK JACK,          ", j + 1);
				}
				else
				{
					printf("   Jugador %d Con Una Puntuacion Final De  %d, ", j + 1, valor[j]);
				}
				if (valor[numero] > 21)
				{
					if (valor[j] > 21)
					{
						printf("\tPerdiste \n");
						dinero[j] -= apuesta[j];
					}
					if (valor[j] <= 21)
					{
						printf("\tGanaste\n");
						dinero[j] += apuesta[j];
					}
				}
				if (valor[numero] <= 21)
				{
					if (valor[j] > 21)
					{
						printf("\tPerdiste\n");
						dinero[j] -= apuesta[j];
					}
					if (valor[j] <= 21)
					{
						if (valor[j] < valor[numero])
						{
							printf("\tPerdiste\n");
							dinero[j] -= apuesta[j];
						}
						else if (valor[j] > valor[numero])
						{
							printf("\tGanaste\n");
							dinero[j] += apuesta[j];
						}
						else
						{
							printf("\tEmpate\n");
						}
					}
				}
			}
			printf("\n");
			for (j = 0; j < numero; j++)
			{
				printf("   El Dinero Restante Del Jugador %d is $%.f\n", j + 1, dinero[j]);
			}
			printf(" |______________________________________________________|\n");
			for (j = 0; j < numero; j++)
			{
				if (dinero[j] <= 0)
				{
					y = 1;//si alguien se queda sin dinero se acaba la partida
				}
			}
			printf("\n    Quiere Jugar Otra Ronda?(y/n) ");
			scanf(" %c", &decis);
			while (decis != 'y'&&decis != 'n')
			{
				printf("\t\t\t   intenta otra vez(y/n) ");
				scanf(" %c", &decis);
			}
			r++;
			if (y == 1)
				break;
		}//fin___________________________________________________________________________________________________________________________
		ofpt = fopen("saved.txt", "w");
		for (j = 0; j < numero; j++)
		{
			if (dinero[j] > 0)
				fprintf(ofpt, "%.f\n", dinero[j]);
		}
		fclose(ofpt);
		system("pause");
	}
}   //función____________________________________________________________________________________________________________________________________-


void titulo()
{
	FILE *fpt, *ifpt;
	int i, j, ai;
	system("color 27");
	if ((fpt = fopen("imagenes.txt", "r")) == NULL)
	{
		printf("Error : File could not be opened\n");
	}
	if ((ifpt = fopen("blackjack.txt", "r")) == NULL)
	{
		printf("Error : File could not be opened\n");
	}
	printf("\n\n");
	for (i = 0; i < 7; i++)
	{
		printf("\t\t");
		for (j = 0; j < 46; j++)
		{
			fscanf(ifpt, "%d", &ai);
			switch (ai)
			{
			case 0:
				printf("%c%c", 219, 219);
				break;
			case 1:
				printf("  ");
				break;
			case 2:
				printf("%c%c", 178, 178);
				break;
			case 3:
				printf("%c%c", 177, 177);
			}

		}
		printf("\n");
	}
	printf("\n\n");
	for (i = 0; i < 19; i++)
	{

		for (j = 0; j < 66; j++)
		{
			fscanf(fpt, "%d", &ai);
			switch (ai)
			{
			case 0:
				printf("%c%c", 219, 219);
				break;
			case 1:
				printf("  ");
				break;
			case 2:
				printf("%c%c", 178, 178);
				break;
			case 3:
				printf("%c%c", 177, 177);
			}

		}
		printf("\n");
	}
	system("pause");
	system("cls");
}

void cartas(int v, int car, char pal)
{
	if (v == 1)
	{
		printf("   _______  ");
	}
	if (v == 2)
	{
		if (car < 10)
			printf("  |%d      | ", car);
		if (car > 9)
			printf("  |%d     | ", car);
	}
	if (v == 3)
	{
		if (pal == '+')
			printf("  |   |   | ");
		if (pal == '-')
			printf("  |       | ");
		if (pal == '^')
			printf("  |  / \\  | ");
		if (pal == '/')
			printf("  |    /  | ");
	}
	if (v == 4)
	{
		if (pal == '+')
			printf("  | --|-- | ");
		if (pal == '-')
			printf("  | ----- | ");
		if (pal == '^')
			printf("  | /   \\ | ");
		if (pal == '/')
			printf("  |   /   | ");
	}
	if (v == 5)
	{
		if (pal == '+')
			printf("  |   |   | ");
		if (pal == '-')
			printf("  |       | ");
		if (pal == '^')
			printf("  |/     \\| ");
		if (pal == '/')
			printf("  |  /    | ");
	}
	if (v == 6)
	{
		if (car < 10)
			printf("  |______%d| ", car);
		if (car > 9)
			printf("  |_____%d| ", car);
	}
}