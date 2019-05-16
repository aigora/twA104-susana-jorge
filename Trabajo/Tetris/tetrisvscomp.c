#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>// matriz[columna][serie]
#include<conio.h>
#include<windows.h>


void titulo();
void inicializar(char[][30]);

int figuras(char, int, int *, int, int, int, char[][30], int*);

void picture(char mat[][30]);
char mov(char, int*, int*);
int menu();


int main()
{
	FILE *fpt, *ofpt;
	int I, J, L, K, ROT, R, puntos = 0, b = 0, flag = 0, highscore, ai, sleep = 100;
	char matriz[12][30], a = 'p';
	// I,J los uso para los for
	// L guarda la posicion y de la figura
	// K guarda la posicion x de la figura y un uso extra
	// ROT guarda la orientacion de la figura
	// R guarda que pieza se esta usando y un uso extra
	// flag marca cuando la figura ha llegado a un obstaculo
	// highscore es el valor mas alto guardado de otras partidas
	// a guarda la tecla que introduces en el getch
	srand(time(NULL));

	system("pause");

	titulo();
	inicializar(matriz);
	while (b == 0)
	{
		K = 0;
		ROT = 1;
		//borro de linea y suma de puntos
		for (I = 0; I < 20; I++)
		{
			for (J = 1; J < 11; J++)
			{
				if (matriz[J][I] != ' ')
					K++;
			}
			if (K == 10)
			{
				for (R = I; R > 0; R--)
				{
					for (J = 1; J < 11; J++)
					{
						matriz[J][R] = matriz[J][R - 1];
					}
				}
				puntos++;
				if (sleep>0)
				sleep -= 10;
			}
			K = 0;
		}

		L = ((rand() % 4) + 4);//aleatoriamente sale una pieza de la columna 4->7
		R = (rand() % 7);// elegir aleatoriamente la pieza
		if (puntos ==20)
		{
		R = 7;
		puntos++;
		}
			
		for (K = 0; K < 20; K++)//imp
		{
			a = 'p';

			a = mov(a, &b, &K);
			if (b != 1)
			{
				L = figuras(a, puntos, &ROT, L, K, R, matriz, &flag);
				Sleep(sleep);
			}
			if (flag == 1)
			{
				flag = 0;
				break;
			}
		}
		for (J = 1; J < 11; J++)
		{
			if (matriz[J][0] != ' ')
				b = 1;
		}
	}

	fpt = fopen("highscore.txt", "r");
	printf("\nGAME OVER\nSu puntuacion es %d\n", puntos);
	fscanf(fpt, "%d", &highscore);
	if (puntos > highscore)
	{
		highscore = puntos;
		printf("\nNUEVO HIGHSCORE\n");
	}
	fpt = fopen("highscore.txt", "w");
	fprintf(fpt, "%d", highscore);
	system("pause");
}


void titulo()
{
	int ai,i=0;
	FILE *ifpt;
	char *t;
	size_t size;
	system("color 17");
	ifpt = fopen("tetris.txt", "r");
	t = (char*)calloc(1, sizeof(char));
	while (feof(ifpt) == 0)
	{
		fscanf(ifpt, "%d", &ai);
		t[i] = ai;
		size = _msize(t);
		t = (char*)realloc(t, size + 1 * sizeof(char));
		i++;
	}
	printf("%s%c             ", t, 13);
	system("pause");
	
	fclose(ifpt);
}
void inicializar(char matriz[][30])
{
	int i, j, ai;
	system("cls");
	system("color 71");
	printf("\t\t ___________________________________________________\n");
	printf("\t\t|\t\tReglas:\t\t\t\t    |\n\t\t|\t\t\t\t\t\t    |\n");
	printf("\t\t|  flecha >: moverse a la derecha\t\t    |\n\t\t|  flecha <: moverse a la izquierda\t\t    |\n");
	printf("\t\t|  flecha v: rotar sentido horario\t\t    |\n\t\t|  flecha ^: rotar sentido antihorario\t\t    |\n\t\t|  tecla esc 2 veces: menu pausa\t\t    |\n");
	printf("\t\t|___________________________________________________|\n");
	system("pause");
	for (i = 0; i < 30; i++)
	{
		for (j = 0; j < 12; j++)
		{
			matriz[j][i] = ' ';
			matriz[0][i] = matriz[11][i] = 219;
		}
	}
}

int figuras(char a, int puntos, int *ROT, int L, int K, int R, char matriz[][30], int *flag)
{
	switch (R)
	{
		//_________________________________________________________________________________________________
	case 0:
		if (a == 'r')
			(*ROT) += 1;
		if (a == 'w')
			(*ROT) -= 1;
		if (*ROT == 5)
			*ROT = 1;
		if (*ROT == 0)
			*ROT = 4;

		if (*ROT == 3 || *ROT == 1)
		{
			if (L == 10)
				L--;
			else if (L == 1)
				L++;
		}
		system("color 75");
		switch (*ROT)
		{
		case 1:
			if (a == 'd'&&L != 9 && matriz[L + 2][K] == ' '&&matriz[L + 1][K - 1] == ' ')
				L++;
			if (a == 'a'&&L != 2 && matriz[L - 2][K] == ' '&&matriz[L - 1][K - 1] == ' ')
				L--;
			if (matriz[L][K] == ' '&&matriz[L - 1][K] == ' '&&matriz[L + 1][K] == ' ')
			{
				matriz[L][K - 1] = matriz[L][K] = matriz[L + 1][K] = matriz[L - 1][K] = 219;
				system("cls"); printf("puntuacion: %d", puntos); picture(matriz);
				if (K < 19)
					matriz[L][K - 1] = matriz[L][K] = matriz[L + 1][K] = matriz[L - 1][K] = ' ';
			}
			else
			{
				matriz[L][K - 2] = matriz[L][K - 1] = matriz[L + 1][K - 1] = matriz[L - 1][K - 1] = 219;
				*flag = 1;
			}
			break;
		case 2:
			if (a == 'd'&&L != 10 && matriz[L + 1][K] == ' '&&matriz[L + 1][K - 1] == ' '&&matriz[L + 1][K + 1] == ' '&&K < 19)
				L++;
			if (a == 'a'&&L != 2 && matriz[L - 2][K] == ' '&&matriz[L - 1][K - 1] == ' '&&matriz[L - 1][K + 1] == ' '&&K < 19)
				L--;
			if (matriz[L - 1][K] == ' '&&matriz[L][K + 1] == ' '&&K < 19)
			{
				matriz[L][K] = matriz[L][K - 1] = matriz[L][K + 1] = matriz[L - 1][K] = 219;
				system("cls"); printf("puntuacion: %d", puntos); picture(matriz);
				matriz[L][K] = matriz[L][K - 1] = matriz[L][K + 1] = matriz[L - 1][K] = ' ';
			}
			else
			{
				matriz[L][K - 1] = matriz[L][K - 2] = matriz[L][K] = matriz[L - 1][K - 1] = 219;
				*flag = 1;
			}
			break;
		case 3:
			if (a == 'd'&&L != 9 && matriz[L + 2][K] == ' '&&matriz[L + 1][K + 1] == ' '&&K < 19)
				L++;
			if (a == 'a'&&L != 2 && matriz[L - 2][K] == ' '&&matriz[L - 1][K + 1] == ' '&&K < 19)
				L--;
			if (matriz[L][K + 1] == ' '&&matriz[L - 1][K] == ' '&&matriz[L + 1][K] == ' '&&K < 19)
			{
				matriz[L][K + 1] = matriz[L - 1][K] = matriz[L + 1][K] = matriz[L][K] = 219;
				system("cls"); printf("puntuacion: %d", puntos); picture(matriz);
				matriz[L][K + 1] = matriz[L - 1][K] = matriz[L + 1][K] = matriz[L][K] = ' ';
			}
			else
			{
				matriz[L][K] = matriz[L - 1][K - 1] = matriz[L + 1][K - 1] = matriz[L][K - 1] = 219;
				*flag = 1;
			}
			break;
		case 4:
			if (a == 'd'&&L != 9 && matriz[L + 2][K] == ' '&&matriz[L + 1][K - 1] == ' '&&matriz[L + 1][K + 1] == ' '&&K < 19)
				L++;
			if (a == 'a'&&L != 1 && matriz[L - 1][K] == ' '&&matriz[L - 1][K - 1] == ' '&&matriz[L - 1][K + 1] == ' '&&K < 19)
				L--;
			if (matriz[L + 1][K] == ' '&&matriz[L][K + 1] == ' '&&K < 19)
			{
				matriz[L][K] = matriz[L][K - 1] = matriz[L + 1][K] = matriz[L][K + 1] = 219;
				system("cls"); printf("puntuacion: %d", puntos); picture(matriz);
				matriz[L][K] = matriz[L][K - 1] = matriz[L + 1][K] = matriz[L][K + 1] = ' ';
			}
			else
			{
				matriz[L][K - 1] = matriz[L][K - 2] = matriz[L + 1][K - 1] = matriz[L][K] = 219;
				*flag = 1;
			}
			break;
		}
		break;
	case 1://_____________________________________________________________________________________________________________________-

		if (a == 'r' || a == 'w')
			(*ROT) += 1;
		if (*ROT == 3)
			*ROT = 1;

		if (*ROT == 1)
		{
			if (a == 'r' || a == 'w')
			{
				if (L == 1)L++;
				else if (L >= 9)L = 8;
			}
		}
		system("color 73");
		switch (*ROT)
		{
		case 1:
			if (a == 'd'&&L != 8 && matriz[L + 3][K] == ' ')
				L++;
			if (a == 'a'&&L != 2 && matriz[L - 2][K] == ' ')
				L--;
			if (matriz[L - 1][K] == ' '&&matriz[L][K] == ' '&&matriz[L + 1][K] == ' '&&matriz[L + 2][K] == ' ')
			{
				matriz[L - 1][K] = matriz[L][K] = matriz[L + 1][K] = matriz[L + 2][K] = 219;
				system("cls"); printf("puntuacion: %d", puntos); picture(matriz);
				if (K < 19)
					matriz[L - 1][K] = matriz[L][K] = matriz[L + 1][K] = matriz[L + 2][K] = ' ';
			}
			else
			{
				matriz[L - 1][K - 1] = matriz[L][K - 1] = matriz[L + 1][K - 1] = matriz[L + 2][K - 1] = 219;
				*flag = 1;
			}
			break;
		case 2:
			if (a == 'd'&&L != 10 && matriz[L + 1][K] == ' '&&matriz[L + 1][K - 1] == ' '&&matriz[L + 1][K - 2] == ' '&&matriz[L + 1][K + 1] == ' '&&K < 19)
				L++;
			if (a == 'a'&&L != 1 && matriz[L - 1][K] == ' '&&matriz[L - 1][K - 1] == ' '&&matriz[L - 1][K - 2] == ' '&&matriz[L - 1][K + 1] == ' '&&K < 19)
				L--;
			if (matriz[L][K + 1] == ' '&&K < 19)
			{
				matriz[L][K] = matriz[L][K - 1] = matriz[L][K - 2] = matriz[L][K + 1] = 219;
				system("cls"); printf("puntuacion: %d", puntos); picture(matriz);
				matriz[L][K] = matriz[L][K - 1] = matriz[L][K - 2] = matriz[L][K + 1] = ' ';
			}
			else
			{
				matriz[L][K - 1] = matriz[L][K - 2] = matriz[L][K - 3] = matriz[L][K] = 219;
				*flag = 1;
			}
			break;
		}
		break;
	case 2://_______________________________________________________________________________________


		if (a == 'r' || a == 'w')
			(*ROT) += 1;
		if (*ROT == 3)
			*ROT = 1;
		if (*ROT == 1)
		{
			if (a == 'r' || a == 'w')
			{
				if (L == 1)L++;
			}
		}

		system("color 74");
		switch (*ROT)
		{
		case 1:
			if (a == 'd'&&L != 9 && matriz[L + 1][K - 1] == ' '&&matriz[L + 2][K] == ' ')
				L++;
			if (a == 'a'&&L != 2 && matriz[L - 2][K - 1] == ' '&&matriz[L - 1][K] == ' ')
				L--;
			if (matriz[L][K] == ' ' && matriz[L - 1][K - 1] == ' ' && matriz[L + 1][K] == ' ')
			{
				matriz[L][K - 1] = matriz[L - 1][K - 1] = matriz[L][K] = matriz[L + 1][K] = 219;
				system("cls"); printf("puntuacion: %d", puntos); picture(matriz);
				if (K < 19)
					matriz[L][K - 1] = matriz[L - 1][K - 1] = matriz[L][K] = matriz[L + 1][K] = ' ';
			}
			else
			{
				matriz[L][K - 2] = matriz[L - 1][K - 2] = matriz[L][K - 1] = matriz[L + 1][K - 1] = 219;
				*flag = 1;
			}
			break;
		case 2:
			if (a == 'd'&&L != 9 && matriz[L + 2][K] == ' '&&matriz[L + 2][K - 1] == ' '&&matriz[L + 1][K + 1] == ' '&&K < 19)//decide si puede irse a la izq  der
				L++;
			if (a == 'a'&&L != 1 && matriz[L - 1][K] == ' '&&matriz[L - 1][K + 1] == ' '&&matriz[L][K - 1] == ' '&&K < 19)
				L--;
			if (matriz[L][K + 1] == ' '&&matriz[L + 1][K] == ' '&&K < 19) //decide si puede bajar
			{
				matriz[L][K + 1] = matriz[L + 1][K] = matriz[L][K] = matriz[L + 1][K - 1] = 219;
				system("cls"); printf("puntuacion: %d", puntos); picture(matriz);
				matriz[L][K + 1] = matriz[L + 1][K] = matriz[L][K] = matriz[L + 1][K - 1] = ' ';
			}
			else
			{
				matriz[L][K] = matriz[L + 1][K - 1] = matriz[L][K - 1] = matriz[L + 1][K - 2] = 219;
				*flag = 1;
			}
			break;
		}
		break;

	case 3://_______________________________________________________________________________________
		if (a == 'r' || a == 'w')
			(*ROT) += 1;
		if (*ROT == 3)
			*ROT = 1;
		if (*ROT == 1)
		{
			if (a == 'r' || a == 'w')
			{
				if (L == 10)L--;
			}
		}
		system("color 72");
		switch (*ROT)
		{
		case 1:
			if (a == 'd'&&L < 9 && matriz[L + 1][K] == ' '&&matriz[L + 2][K - 1] == ' ')
				L++;
			if (a == 'a'&&L > 2 && matriz[L - 2][K] == ' '&&matriz[L - 1][K - 1] == ' ')
				L--;
			if (matriz[L][K] == ' ' && matriz[L + 1][K - 1] == ' ' && matriz[L - 1][K] == ' ')
			{
				matriz[L][K - 1] = matriz[L + 1][K - 1] = matriz[L][K] = matriz[L - 1][K] = 219;
				system("cls"); printf("puntuacion: %d", puntos); picture(matriz);
				if (K < 19)
					matriz[L][K - 1] = matriz[L + 1][K - 1] = matriz[L][K] = matriz[L - 1][K] = ' ';
			}
			else
			{
				matriz[L][K - 2] = matriz[L + 1][K - 2] = matriz[L][K - 1] = matriz[L - 1][K - 1] = 219;
				*flag = 1;
			}
			break;
		case 2:
			if (a == 'd'&&L < 10 && matriz[L + 1][K + 1] == ' '&&matriz[L + 1][K] == ' '&&matriz[L][K - 1] == ' '&&K < 19)
				L++;
			if (a == 'a'&&L > 2 && matriz[L - 1][K + 1] == ' '&&matriz[L - 2][K] == ' '&&matriz[L - 2][K - 1] == ' '&&K < 19)
				L--;
			if (matriz[L][K + 1] == ' '&&matriz[L - 1][K] == ' '&&K < 19)
			{
				matriz[L][K] = matriz[L - 1][K] = matriz[L][K + 1] = matriz[L - 1][K - 1] = 219;
				system("cls"); printf("puntuacion: %d", puntos); picture(matriz);
				matriz[L][K] = matriz[L - 1][K] = matriz[L][K + 1] = matriz[L - 1][K - 1] = ' ';
			}
			else
			{
				matriz[L][K - 1] = matriz[L - 1][K - 1] = matriz[L][K] = matriz[L - 1][K - 2] = 219;
				*flag = 1;
			}
			break;
		}
		break;

	case 4://_____________________________________________________________________________________________________________________
		if (a == 'r')
			(*ROT) += 1;
		if (a == 'w')
			(*ROT) -= 1;
		if (*ROT == 5)
			*ROT = 1;
		if (*ROT == 0)
			*ROT = 4;

		if (*ROT == 2 || *ROT == 4)
		{
			if (L == 1)L++;
			if (L == 10)L--;
		}
		system("color 78");
		switch (*ROT)
		{
		case 1:
			if (a == 'd'&&L < 10 && matriz[L + 1][K] == ' '&&matriz[L + 1][K - 1] == ' '&&matriz[L + 1][K + 1] == ' '&&K < 19)
				L++;
			if (a == 'a'&&L > 2 && matriz[L - 1][K] == ' '&&matriz[L - 1][K + 1] == ' '&&matriz[L - 2][K - 1] == ' '&&K < 19)
				L--;
			if (matriz[L][K + 1] == ' '&&matriz[L - 1][K - 1] == ' '&&K < 19)
			{
				matriz[L][K] = matriz[L][K + 1] = matriz[L][K - 1] = matriz[L - 1][K - 1] = 219;
				system("cls"); printf("puntuacion: %d", puntos); picture(matriz);
				matriz[L][K] = matriz[L][K + 1] = matriz[L][K - 1] = matriz[L - 1][K - 1] = ' ';
			}
			else
			{
				matriz[L][K - 1] = matriz[L][K] = matriz[L][K - 2] = matriz[L - 1][K - 2] = 219;
				*flag = 1;
			}
			break;
		case 2:
			if (a == 'd'&&L < 9 && matriz[L + 2][K] == ' '&&matriz[L][K + 1] == ' '&&K < 19)
				L++;
			if (a == 'a'&&L > 2 && matriz[L - 2][K] == ' '&&matriz[L - 2][K + 1] == ' '&&K < 19)
				L--;
			if (matriz[L][K] == ' '&&matriz[L - 1][K + 1] == ' '&&matriz[L + 1][K] == ' '&&K < 19)
			{
				matriz[L][K] = matriz[L - 1][K + 1] = matriz[L - 1][K] = matriz[L + 1][K] = 219;
				system("cls"); printf("puntuacion: %d", puntos); picture(matriz);
				matriz[L][K] = matriz[L - 1][K + 1] = matriz[L - 1][K] = matriz[L + 1][K] = ' ';
			}
			else
			{
				matriz[L][K - 1] = matriz[L - 1][K] = matriz[L - 1][K - 1] = matriz[L + 1][K - 1] = 219;
				*flag = 1;
			}
			break;
		case 3:
			if (a == 'd'&&L < 9 && matriz[L + 2][K + 1] == ' '&&matriz[L + 1][K] == ' '&&matriz[L + 1][K - 1] == ' '&&K < 19)
				L++;
			if (a == 'a'&&L > 1 && matriz[L - 1][K + 1] == ' '&&matriz[L - 1][K] == ' '&&matriz[L - 1][K - 1] == ' '&&K < 19)
				L--;
			if (matriz[L][K + 1] == ' '&&matriz[L + 1][K + 1] == ' '&&K < 19)
			{
				matriz[L][K] = matriz[L][K - 1] = matriz[L + 1][K + 1] = matriz[L][K + 1] = 219;
				system("cls"); printf("puntuacion: %d", puntos); picture(matriz);
				matriz[L][K] = matriz[L][K - 1] = matriz[L + 1][K + 1] = matriz[L][K + 1] = ' ';
			}
			else
			{
				matriz[L][K - 1] = matriz[L][K - 2] = matriz[L + 1][K] = matriz[L][K] = 219;
				*flag = 1;
			}
			break;
		case 4:
			if (a == 'd'&&L < 9 && matriz[L + 2][K] == ' '&&matriz[L + 2][K - 1] == ' ')
				L++;
			if (a == 'a'&&L > 2 && matriz[L - 2][K] == ' '&&matriz[L][K - 1] == ' ')
				L--;
			if (matriz[L][K] == ' '&&matriz[L - 1][K] == ' '&&matriz[L + 1][K] == ' ')
			{
				matriz[L][K] = matriz[L - 1][K] = matriz[L + 1][K] = matriz[L + 1][K - 1] = 219;
				system("cls"); printf("puntuacion: %d", puntos); picture(matriz);
				if (K < 19)
					matriz[L][K] = matriz[L - 1][K] = matriz[L + 1][K] = matriz[L + 1][K - 1] = ' ';
			}
			else
			{
				matriz[L][K - 1] = matriz[L - 1][K - 1] = matriz[L + 1][K - 1] = matriz[L + 1][K - 2] = 219;
				*flag = 1;
			}
			break;
		}
		break;
	case 5://_____________________________________________________________________________________________________________________
		if (*ROT == 5)
			*ROT = 1;
		if (a == 'r')
			(*ROT) -= 1;
		if (a == 'w')
			(*ROT) += 1;
		if (*ROT == 5)
			*ROT = 1;
		if (*ROT == 0)
			*ROT = 4;

		if (*ROT == 2 || *ROT == 4)
		{
			if (L == 1)L++;
			if (L == 10)L--;
		}
		system("color 71");

		switch (*ROT)
		{
		case 1:
			if (a == 'd'&&L < 9 && matriz[L + 1][K] == ' '&&matriz[L + 2][K - 1] == ' '&&matriz[L + 1][K + 1] == ' '&&K < 19)
				L++;
			if (a == 'a'&&L > 1 && matriz[L - 1][K] == ' '&&matriz[L - 1][K + 1] == ' '&&matriz[L - 1][K - 1] == ' '&&K < 19)
				L--;
			if (matriz[L][K + 1] == ' '&&matriz[L + 1][K - 1] == ' '&&K < 19)
			{
				matriz[L][K] = matriz[L][K + 1] = matriz[L][K - 1] = matriz[L + 1][K - 1] = 219;
				system("cls"); printf("puntuacion: %d", puntos); picture(matriz);
				matriz[L][K] = matriz[L][K + 1] = matriz[L][K - 1] = matriz[L + 1][K - 1] = ' ';
			}
			else
			{
				matriz[L][K - 1] = matriz[L][K] = matriz[L][K - 2] = matriz[L + 1][K - 2] = 219;
				*flag = 1;
			}
			break;
		case 2:
			if (a == 'd'&&L < 9 && matriz[L + 2][K] == ' '&&matriz[L + 2][K + 1] == ' '&&K < 19)
				L++;
			if (a == 'a'&&L > 2 && matriz[L - 2][K] == ' '&&matriz[L][K + 1] == ' '&&K < 19)
				L--;
			if (matriz[L][K] == ' '&&matriz[L - 1][K] == ' '&&matriz[L + 1][K + 1] == ' '&&K < 19)
			{
				matriz[L][K] = matriz[L - 1][K] = matriz[L + 1][K] = matriz[L + 1][K + 1] = 219;
				system("cls"); printf("puntuacion: %d", puntos); picture(matriz);
				matriz[L][K] = matriz[L - 1][K] = matriz[L + 1][K] = matriz[L + 1][K + 1] = ' ';
			}
			else
			{
				matriz[L][K - 1] = matriz[L - 1][K - 1] = matriz[L + 1][K - 1] = matriz[L + 1][K] = 219;
				*flag = 1;
			}
			break;
		case 3:
			if (a == 'd'&&L < 10 && matriz[L + 1][K + 1] == ' '&&matriz[L + 1][K] == ' '&&matriz[L + 1][K - 1] == ' '&&K < 19)
				L++;
			if (a == 'a'&&L > 2 && matriz[L - 2][K + 1] == ' '&&matriz[L - 1][K] == ' '&&matriz[L - 1][K - 1] == ' '&&K < 19)
				L--;
			if (matriz[L][K + 1] == ' '&&matriz[L - 1][K + 1] == ' '&&K < 19)
			{
				matriz[L][K] = matriz[L][K - 1] = matriz[L - 1][K + 1] = matriz[L][K + 1] = 219;
				system("cls"); printf("puntuacion: %d", puntos); picture(matriz);
				matriz[L][K] = matriz[L][K - 1] = matriz[L - 1][K + 1] = matriz[L][K + 1] = ' ';
			}
			else
			{
				matriz[L][K - 1] = matriz[L][K - 2] = matriz[L - 1][K] = matriz[L][K] = 219;
				*flag = 1;
			}
			break;
		case 4:
			if (a == 'd'&&L < 9 && matriz[L][K - 1] == ' '&&matriz[L + 2][K] == ' ')
				L++;
			if (a == 'a'&&L > 2 && matriz[L - 2][K] == ' '&&matriz[L - 2][K - 1] == ' ')
				L--;
			if (matriz[L][K] == ' '&&matriz[L - 1][K] == ' '&&matriz[L + 1][K] == ' ')
			{
				matriz[L][K] = matriz[L - 1][K] = matriz[L + 1][K] = matriz[L - 1][K - 1] = 219;
				system("cls"); printf("puntuacion: %d", puntos); picture(matriz);
				if (K < 19)
					matriz[L][K] = matriz[L - 1][K] = matriz[L + 1][K] = matriz[L - 1][K - 1] = ' ';
			}
			else
			{
				matriz[L][K - 1] = matriz[L - 1][K - 1] = matriz[L + 1][K - 1] = matriz[L - 1][K - 2] = 219;
				*flag = 1;
			}
			break;
		}
		break;
	case 6://______________________________________________________________________________________________________________________
		system("color 76");
		if (a == 'd'&&L != 9 && matriz[L + 2][K] == ' '&&matriz[L + 2][K - 1] == ' ')//cambiar tambien en el resto porque da lugar a erroresimp imp imp imp imp
			L++;
		if (a == 'a'&&L != 1 && matriz[L - 1][K] == ' '&&matriz[L - 1][K - 1] == ' ')
			L--;
		if (matriz[L][K] == ' '&&matriz[L + 1][K] == ' ')
		{
			matriz[L][K - 1] = matriz[L][K] = matriz[L + 1][K] = matriz[L + 1][K - 1] = 219;
			system("cls"); printf("puntuacion: %d", puntos); picture(matriz);
			if (K < 19)
				matriz[L][K - 1] = matriz[L][K] = matriz[L + 1][K] = matriz[L + 1][K - 1] = ' ';
		}
		else
		{
			matriz[L][K - 2] = matriz[L][K - 1] = matriz[L + 1][K - 1] = matriz[L + 1][K - 2] = 219;
			*flag = 1;
		}
		break;
	case 7://__________________________________________________________________________________________________________
		if (a == 'd'&&L < 7)
			L++;
		if (a == 'a'&&L > 4)
			L--;
		if (K == 19)
		{
			K = 22;
			*flag = 1;
		}

		matriz[L][K] = matriz[L + 1][K] = matriz[L - 1][K] = matriz[L + 2][K + 1] = matriz[L - 2][K + 1] = matriz[L + 3][K + 2] = matriz[L - 3][K + 2] = matriz[L + 3][K + 3] = matriz[L - 3][K + 3] = 219;
		matriz[L + 3][K + 4] = matriz[L - 3][K + 4] = matriz[L + 2][K + 5] = matriz[L - 2][K + 5] = matriz[L][K + 6] = matriz[L + 1][K + 6] = matriz[L - 1][K + 6] = 219;
		system("cls"); printf("puntuacion: %d", puntos); picture(matriz);
		matriz[L][K] = matriz[L + 1][K] = matriz[L - 1][K] = matriz[L + 2][K + 1] = matriz[L - 2][K + 1] = matriz[L + 3][K + 2] = matriz[L - 3][K + 2] = matriz[L + 3][K + 3] = matriz[L - 3][K + 3] = ' ';
		matriz[L + 3][K + 4] = matriz[L - 3][K + 4] = matriz[L + 2][K + 5] = matriz[L - 2][K + 5] = matriz[L][K + 6] = matriz[L + 1][K + 6] = matriz[L - 1][K + 6] = ' ';
	}
	return L;
}

void picture(char mat[][30])
{
	int i, j, a=0;
	char *T;
	printf("\n");
	size_t size;
	T = (char*)calloc(2, sizeof(char));
	for (i = 0; i < 20; i++)
	{
		for (j = 0; j < 12; j++)
		{
			T[a] = mat[j][i];
			size = _msize(T);
			T[a + 1]=mat[j][i];
			if(j==11)
				T = (char*)realloc(T, size + 3 * sizeof(char));
			else 
			T = (char*)realloc(T, size + 2 * sizeof(char));
			a += 2;
		}
		T[a] = 10;
		a++;
	}
	printf("%s%c                                                                                                                                                     ", T,13);
}
char mov(char a, int *b, int *K)
{
	if (_kbhit() == 1)
	{
		_getch();
		a = _getch();
		switch (a)
		{
		case 77:
			a = 'd';
			break;
		case 75:
			a = 'a';
			break;
		case 72:
			a = 'r';
			break;
		case 80:
			a = 'w';
			break;
		case 27:
			*b = menu();
			if (*b == 1)
				K = 20;
			//a = 's';
			break;
		}
	}
	return a;
}
int menu()
{
	FILE *fpt, *ofpt;
	int i, j,z=0;
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
	while (a!='i')
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
			z = 0;
			break;
		case 13:
			a = 'i';
			break;
		}
	}
	return z;

}
