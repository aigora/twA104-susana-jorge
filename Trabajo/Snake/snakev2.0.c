#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include <malloc.h>
#define D 25
void Titulo();
void Inicializar(int *B, char *mov, int *vidas, int *puntuacion, char pt[D][D], char manzana, int lng, int Y[1], int X[1], char serpiente, int *a, int *b);
int Menu();
void main()
{
	FILE *phs, *pbckup;

	char pt[D][D]; //El tablero (pt) es una matriz regular  DxD
	char manzana = 254; //Caracter de la manzana
	int lng = 3, i=0, m = 10, j, A = 1, x, y, a, b, *X, *Y, vidas = 3, puntuacion = 0, times = 100, flag = 0, highscore, B = 0;
	char T[27][53], serpiente = 219;
	char mando;
	size_t size;
	X = (int *)malloc(sizeof(int) * lng);
	Y = (int *)malloc(sizeof(int) * lng);


// pt[][] representa el tablero
// X[] guarda la coordenada x de la serpiente
// Y[] guarda la coordenada y de la serpiente
// a representa el valor aleatorio que toma la coordenada x de la manzana
// b representa el valor aleatorio que toma la coordenada y de la manzana
// times marca el tiempo del Sleep
// el flag marca cuando se pierde una vida
// B marca la opción elegida en el menú de pausa


	system("pause"); //Para maximizar la pantalla antes de que salga el dibujo
	Titulo();
	Sleep(1000);// Deja la pantalla durante un segundo para que no se borre de golpe
	system("cls");

	printf("\t\t\t\t _________________________________ \n\t\t\t\t|\t\t\t\t  |\n\t\t\t\t|\tbienvenido al SNAKE\t  |\n");
	printf("\t\t\t\t|\t\t\t\t  |\n\t\t\t\t|_________________________________|\n");
	Sleep(1000);
	printf("\t\t\t\t _______________________________________ \n\t\t\t\t|\t\t\t\t\t|\n");
	printf("\t\t\t\t| flecha >: moverse a la derecha\t|\n\t\t\t\t| flecha <: moverse a la izquierda\t|\n");
	printf("\t\t\t\t| flecha ^: moverse arriba\t\t|\n\t\t\t\t| flecha v: moverse abajo\t\t|\n");
	printf("\t\t\t\t| esc DOS VECES: pausar el juego\t|\n");
	printf("\t\t\t\t|_______________________________________|\n");
	system("pause");
	
	system("cls");
	Inicializar(&B, &mando, &vidas, &puntuacion, pt, manzana, lng, Y, X, serpiente, &a, &b);
	do {
		if (B == 2)
			B = 0;
		pt[a][b] = manzana;
		if (_kbhit() == 1) // Recoge teclas especiales (flechas, etc)
		{
			_getch();
			mando = _getch();
		}
		pt[X[lng - 1]][Y[lng - 1]] = ' ';
		if (pt[X[0]][Y[0]] == pt[a][b])
		{
			pt[a][b] = ' ';
			i = (rand() % 24)+1; //posición aleatoria para la manzana
			j = (rand() % 24) + 1;
			a = i; //a y b son las coordenadas de la manzana
			b = j;
			pt[a][b] = manzana;
			lng += 1;
			size = _msize(X);
			X = (int*)realloc(X, size + 1 * sizeof(int));
			Y = (int*)realloc(Y, size + 1 * sizeof(int));
			if (vidas == 3) // La puntuación aumenta más lentamente al disminuir el número de vidas restantes
				puntuacion += 10;
			else if (vidas == 2)
				puntuacion += 5;
			else if (vidas == 1)
				puntuacion += 2;
			if(times > 0) // La velocidad a la que se mueve aumenta cada vez que te comes una manzana
			times -= 5;
		}

		if (mando != 27) // Si el mando es 27 es la pausa, de esta manera evitamos perder vidas mientras se abre el menú de pausa
		{
			for (i = lng - 1; i > 0; i--)
			{
				X[i] = X[i - 1];
				Y[i] = Y[i - 1];
			}
		}

		if (X[0] == 0 && m == 0) //Cuando choca contra una pared, aparece en el lado opuesto
		{
			X[0] = 24;
		}
		else if (X[0] == 24 && m == 1)
		{
			X[0] = 0;
		}
		if (Y[0] == 0 && m == 2)
		{
			Y[0] = 24;
		}
		else if (Y[0] == 24 && m == 3)
		{
			Y[0] = 0;
		}
		if (m == 0 && mando == 80) //Si intenta ir marcha atrás, no lo permite y además pierde una vida porque se come a sí misma
		{
			mando = 72;
			flag = 1;
		}
		else if (m == 1 && mando == 72)
		{
			mando = 80;
			flag = 1;
		}
		if (m == 2 && mando == 77)
		{
			mando = 75;
			flag = 1;
		}
		else if (m == 3 && mando == 75)
		{
			mando = 77;
			flag = 1;
		}


		switch (mando) //Ejecuta la orden
		{
		case 72: //Flecha izquierda
			if (X[0] > 0)
				X[0] -= 1;
			m = 0;
			break;

		case 80: //Flecha derecha
			if (X[0] < 24)
				X[0] += 1;
			m = 1;
			break;

		case 75: //Flecha arriba
			if (Y[0] > 0)
				Y[0] -= 1;
			m = 2;
			break;

		case 77: //Flecha abajo
			if (Y[0] < 24)
				Y[0] += 1;
			m = 3;
			break;
		case 27:
			B = Menu();
			if (B == 2)
				flag = 0;
			if (m != 0)
				mando = 80;
			else if (m == 0)
				mando = 77;
			break;
		default:
			mando = 27;
			break;
		}


		if (B == 1) //Si en la pausa se elige la opción de terminar la partida B=1 y se sale del do-while
			break;


		for (i = 1; i < lng; i++)
		{
			if (X[0] == X[i] && Y[0] == Y[i] && B==0) //Si la serpiente se come a sí misma, pierde una vida
			{
				flag = 1;
			}
		}


		if (flag == 1) //El flag se activa cuando se come a sí misma
		{
			vidas--;
			printf("\a"); //Sonará una alarma cada vez que disminuya su número de vidas
			Sleep(1000);
			if (vidas == 0)
			{
				Sleep(1000);
				system("CLS");
				printf("GAME OVER");
				break;
			}

			flag = 0;
		}

		for (i = 0; i < lng; i++)
		{
			x = X[i]; y = Y[i];
			pt[x][y] = serpiente;
		}

		Sleep(times); //Determina la velocidad de la serpiente, cuanto mayor sea el valor de times, más despacio se desplazará
		system("cls");
		printf("\t\tPUNTUACION ACTUAL: %d\n", puntuacion);
		printf(" _________________________________________________\n");
		A = 1;
		for (i = 0; i < D; i++)
		{
			T[i][0] = T[i][51] = '|';
			T[i][52] = 10;
			for (j = 0; j < D; j++)
			{
				T[i][A] = pt[i][j];
				T[i][A + 1] = pt[i][j];
				A += 2;
			}
			A = 1;
		}
		printf("%s%c _________________________________________________                                                                                              ", T, 13);
		printf("\n\n\t\tTE QUEDAN %d VIDAS", vidas);
	} while (vidas >= 0 && (B==0 || B==2));



	printf("\n\nTu puntuacion final es %d.\n", puntuacion);

	//Te dice tu puntuación final y comprueba si has superado el record. En ese caso lo guarda en el archivo backup, donde se guardan todos los recors

	phs = fopen("highscore.txt", "r");
	pbckup = fopen("backup.txt", "a");
	fscanf(phs, "%d", &highscore);
	if (puntuacion > highscore)
	{
		printf("ENHORABUENA, HAS BATIDO EL RECORD DE PUNTUACION");
		printf("\nEl record anterior era: %d", highscore);
		phs = fopen("highscore.txt", "w");
		fprintf(phs, "%d\n", puntuacion);
		fprintf(pbckup, "%d", puntuacion);
	}
	else
		{
		printf("El record actual es: %d puntos.\n", highscore);
	}
	fclose(phs);
	fclose(pbckup);

	printf("\n\nHasta la proxima.\n\n");
	free(X); free(Y);
	system("pause");
}
void Titulo()
{
	FILE *ifpt;
	int ai = 0, i = 0, k;
	size_t size;
	char *T;
		ifpt = fopen("snake1.txt", "r");
	
	T = (char*)malloc(1 * sizeof(char));

	while (feof(ifpt) == 0)
	{
		fscanf(ifpt, "%d", &ai);
		T[i] = ai;
		size = _msize(T);
		T = (char*)realloc(T, size + 1 * sizeof(char));
		i++;
	}
	i = 0;


	while (i < 101)
	{
		system("cls");
		printf("\n%s%c                                                         \n", T, 13);
		k = i;
		printf("         _________________________________________________________________________________________ \n\t|\n\t|");
		while (k > 0)
		{
			printf("%c", 219);
			k--;
		}
		printf("\n\t|_________________________________________________________________________________________ \n");
		printf("\t\t\t\t\t\t CARGANDO... %d%c\n", i, 37);
		i += 5;
	}
	fclose(ifpt);
	free(T);
}
void Inicializar(int *B, char *mando, int *vidas, int *puntuacion, char pt[D][D], char manzana, int lng, int Y[1], int X[1], char serpiente, int *a, int *b)
{
	int i, j;
	*mando = 80;
	*B = 0;
		*vidas = 3;
		*puntuacion = 0;
		for (i = 0; i < D; i++)
		{
			for (j = 0; j < D; j++)
			{
				pt[i][j] = 32;
			}
		}
		srand(time(NULL));
		i = (rand() % 24) + 1; //posición aleatoria para la manzana
		j = (rand() % 24) + 1;
		*a = i;
		*b = j;
		pt[*a][*b] = manzana; //Define las coordenadas a, b como manzana
		i = (rand() % 24) + 1; //posición aleatoria para la serpiente
		j = (rand() % 24) + 1;
		X[0] = i;
		Y[0] = j;
		for (i = 0; i < lng; i++)
		{
			X[i] = X[0] + i;
			Y[i] = Y[0] + i;
			pt[X[i]][Y[i]] = serpiente;//Asigna las coordenadas x, y a la serpiente
		}
}
int Menu()
{
	FILE *fpt, *ofpt;
	int i, j, z = 0;
	char si[9][24], a = 'a', no[9][24];
	if ((fpt = fopen("sino.txt", "r")) == NULL)
		printf("Error : File could not be opened\n");
	if ((ofpt = fopen("nosi.txt", "r")) == NULL)
		printf("Error : File could not be opened\n");
	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 24; j++)
		{
			fscanf(fpt, "%c", &si[i][j]);
			if (si[i][j] == '.')
				si[i][j] = 219;
		}
	}
	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 24; j++)
		{
			fscanf(ofpt, "%c", &no[i][j]);
			if (no[i][j] == '.')
				no[i][j] = 219;
		}
	}
	while (a != 'i')
	{
		system("cls");
		printf("\t\t\tPAUSA, QUIERES CONTINUAR EL JUEGO?\n");
		for (i = 0; i < 9; i++)
		{
			printf("\t\t");
			for (j = 0; j < 24; j++)
			{
				if (a == 'a')
				{
					printf("%c", si[i][j]);
					if (si[i][j] == ' ')
						printf("%c", ' ');
					else
						printf("%c", 219);
				}
				if (a == 'd')
				{
					printf("%c", no[i][j]);
					if (no[i][j] == ' ')
						printf("%c", ' ');
					else
						printf("%c", 219);
				}
			}
			printf("\n");
		}
		_getch();
		a = _getch();
		switch (a)
		{
		case 77:
			a = 'd';
			z = 1;
			break;
		case 75:
			a = 'a';
			z = 2;
			break;
		case 13:
			a = 'i';
			break;
		}
	}
	return z;
	fclose(fpt); fclose(ofpt);
}