#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<conio.h>

void titulo();
int inicializar(char[][10], char[][10]);

void ceros(char[][10], char[][10], int, int);

void picture(char[][10],int,int);
int mov(char*, int*,int*);
int menu();


int main()
{
	int i, j, a=4, b=4, z = 0, x = 0, k,B;
	char move = 'a', bomba[10][10], vacio[10][10], f=244; 
	// i, j los uso como variables en los for
	// a, b marcan la posicion x, y en la que apuntas
	// z, x se usa para confirmar que solo las bombas tienen bandera
	// move guarda el movimiento qeu deseas hacer
	// bomba es el tablero completo con los numeros y bombas
	// vacio es el tablero que puede ver el usuario
	// k numero de bombas
	// f es el simbolo de la bandera
	srand(time(NULL));

	system("pause");

	titulo();
	k=inicializar(vacio, bomba,&a,&b);
	while (vacio[a][b] != 'x')
	{
		move = 'a';
		while (move != 'r'&&move != 't')
		{
			picture(vacio, a, b);
			B=mov(&move, &a,&b);
		}
		if (B == 1)
			break;
		if (move == 't')
		{
			vacio[a][b] = 244;
		}
		else
		{
			vacio[a][b] = bomba[a][b];
			ceros(vacio, bomba, a, b);
		}
		z = x = 0;//inicializar z y x
		for (i = 0; i < 10; i++)
		{
			for (j = 0; j < 10; j++)
			{
				if (bomba[i][j] == 'x')
				{
					if (vacio[i][j] == f)//contar que todas las bombas tienen bandera
						z++;
				}
				if (vacio[i][j] == f)//contar que solo hay 10 banderas
					x++;
			}
		}
		if (z == k && x == k)
			break;
	}
	picture(bomba,a,b);
	if (z == k)
		printf("you win\n");
	else
		printf("GAME OVER\n");
	system("pause");
}


void titulo()
{
	FILE *ifpt;
	int i = 0, ai;
	char *t;
	size_t size;
	// i,j para los for
	// a,b marcan posicion x,y
	// ai variable para imprimir titulo

	ifpt = fopen("texto.txt", "r");
	t = (char*)calloc(1, sizeof(char));
	while (feof(ifpt) == 0)
	{
		fscanf(ifpt, "%d", &ai);
		t[i] = ai;
		size = _msize(t);
		t = (char*)realloc(t, size + 1 * sizeof(char));
		i++;
	}
	printf("%s%c              \n", t, 13);
	system("pause");
	fclose(ifpt);
}
int inicializar(char vacio[][10],char bomba[][10])
{
	int i=0, j, b, k, a=0;
	
	system("cls");
	system("color 70");
	printf("\t\t\t\t _______________________________________ \n\t\t\t\t|\t\t\t\t\t|\n\t\t\t\t|\tbienvenido al buscaminas\t|\n");
	printf("\t\t\t\t|\t\t\t\t\t|\n\t\t\t\t|_______________________________________|\n");
	Sleep(1000);
	printf("\t\t\t\t _______________________________________ \n\t\t\t\t|\t\t\t\t\t|\n");
	printf("\t\t\t\t| flecha >: moverse a la derecha\t|\n\t\t\t\t| flecha <: moverse a la izquierda\t|\n");
	printf("\t\t\t\t| flecha ^: moverse arriba\t\t|\n\t\t\t\t| flecha v: moverse abajo\t\t|\n");
	printf("\t\t\t\t| intro DOS VECES: para poner una bomba\t|\n");
	printf("\t\t\t\t| tab DOS VECES: para poner una bandera\t|\n");
	printf("\t\t\t\t|_______________________________________|\n\n");
	do
	{
		printf("\t\t\t\t\tcuantas bombas desea que haya ");
		scanf("%d", &k);
	} while (k <= 0 || k>100);
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			vacio[i][j] = '-';
			bomba[i][j] = '0';
		}

	}
	srand(time(NULL));
	for (i = 0; i <k; i++)
	{
		do
		{
			a = (rand() % 10);
			b = (rand() % 10);
		} while (bomba[a][b] == 'x');
		bomba[a][b] = 'x';
	}

	for (a = 0; a < 10; a++)
	{
		for (b = 0; b < 10; b++)
		{
			if (bomba[a][b] != 'x')
			{
				for (i = -1; i <= 1; i++)
				{
					for (j = -1; j <= 1; j++)
					{
						if (bomba[a + i][b + j] == 'x')
						{
							if(a+i>=0&&a+i<10&&b+j>=0&&b+j<10)
							bomba[a][b]++;
						}
					}
				}
			}
		}
	}
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			printf("%c", bomba[j][i]);
		}
		printf("\n");
	}
	system("pause");
	return k;
}

void ceros(char vacio[][10], char bomba[][10], int a, int b)
{
	int w, v, h, k, l, m, n, o, p, q, i, j, c, d, e, f, r, s, t, u;

	// son todas variables de bucle en bucle en bucle de fors
	if (vacio[a][b] == '0')
	{
		for (v = -1; v <= 1; v++)
		{
			for (w = -1; w <= 1; w++)
			{
				if (a + v >= 0 && b + w >= 0 && a + v <= 9 && b + w <= 9)
					vacio[a + v][b + w] = bomba[a + v][b + w];//ronda 1
				if (vacio[a + v][b + w] == '0')
				{
					for (h = -1; h <= 1; h++)
					{
						for (k = -1; k <= 1; k++)
						{
							if (a + v + h >= 0 && b + w + k >= 0 && a + v + h <= 9 && b + w + k <= 9)
								vacio[a + v + h][b + w + k] = bomba[a + v + h][b + w + k];//ronda 2
							if (vacio[a + v + h][b + w + k] == '0')
							{
								for (l = -1; l <= 1; l++)
								{
									for (m = -1; m <= 1; m++)
									{
										if (a + v + h + l >= 0 && b + w + k + m >= 0 && a + v + h + l <= 9 && b + w + k + m <= 9)
											vacio[a + v + l + h][b + w + m + k] = bomba[a + v + l + h][b + w + m + k];//ronda 3
										if (vacio[a + v + l + h][b + w + m + k] == '0')
										{
											for (n = -1; n <= 1; n++)
											{
												for (o = -1; o <= 1; o++)
												{
													if (a + v + h + l + n >= 0 && b + w + k + m + o >= 0 && a + v + h + l + n <= 9 && b + w + k + m + o <= 9)
														vacio[a + v + l + h + n][b + w + m + k + o] = bomba[a + v + l + h + n][b + w + m + k + o];//ronda 4
													if (vacio[a + v + l + h + n][b + w + m + k + o] == '0')
													{
														for (i = -1; i <= 1; i++)
														{
															for (j = -1; j <= 1; j++)
															{
																if (a + v + h + l + n + i >= 0 && b + w + k + m + o + j >= 0 && a + v + h + l + n + i <= 9 && b + w + k + m + o + j <= 9)
																	vacio[a + v + l + h + n + i][b + w + m + k + o + j] = bomba[a + v + l + h + n + i][b + w + m + k + o + j];//ronda 5
																if (vacio[a + v + l + h + n + i][b + w + m + k + o + j] == '0')
																{
																	for (p = -1; p <= 1; p++)
																	{
																		for (q = -1; q <= 1; q++)
																		{
																			if (a + v + h + l + n + i + p >= 0 && b + w + k + m + o + j + q >= 0 && a + v + h + l + n + i + p <= 9 && b + w + k + m + o + j + q <= 9)
																				vacio[a + v + l + h + n + i + p][b + w + m + k + o + j + q] = bomba[a + v + l + h + n + i + p][b + w + m + k + o + j + q];//ronda 6
																			if (vacio[a + v + l + h + n + i + p][b + w + m + k + o + j + q] == '0')
																			{
																				for (c = -1; c <= 1; c++)
																				{
																					for (d = -1; d <= 1; d++)
																					{
																						if (a + v + l + h + n + i + p + c >= 0 && b + w + m + k + o + j + q + d >= 0 && a + v + l + h + n + i + p + c <= 9 && b + w + m + k + o + j + q + d <= 9)
																							vacio[a + v + l + h + n + i + p + c][b + w + m + k + o + j + q + d] = bomba[a + v + l + h + n + i + p + c][b + w + m + k + o + j + q + d];//ronda 7
																						if (vacio[a + v + l + h + n + i + p + c][b + w + m + k + o + j + q + d] == '0')
																						{
																							for (e = -1; e <= 1; e++)
																							{
																								for (f = -1; f <= 1; f++)
																								{
																									if (a + v + l + h + n + i + p + c + e >= 0 && b + w + m + k + o + j + q + d + f >= 0 && a + v + l + h + n + i + p + c + e <= 9 && b + w + m + k + o + j + q + d + f <= 9)
																										vacio[a + v + l + h + n + i + p + c + e][b + w + m + k + o + j + q + d + f] = bomba[a + v + l + h + n + i + p + c + e][b + w + m + k + o + j + q + d + f];//ronda 8
																									if (vacio[a + v + l + h + n + i + p + c + e][b + w + m + k + o + j + q + d + f] == '0')
																									{
																										for (r = -1; r <= 1; r++)
																										{
																											for (s = -1; s <= 1; s++)
																											{
																												if (a + v + l + h + n + i + p + c + e + r >= 0 && b + w + m + k + o + j + q + d + f + s >= 0 && a + v + l + h + n + i + p + c + e + r <= 9 && b + w + m + k + o + j + q + d + f + s <= 9)
																													vacio[a + v + l + h + n + i + p + c + e + r][b + w + m + k + o + j + q + d + f + s] = bomba[a + v + l + h + n + i + p + c + e + r][b + w + m + k + o + j + q + d + f + s];//ronda 9
																												if (vacio[a + v + l + h + n + i + p + c + e + r][b + w + m + k + o + j + q + d + f + s] == '0')
																												{
																													for (t = -1; t <= 1; t++)
																													{
																														for (u = -1; u <= 1; u++)
																														{
																															if (a + v + l + h + n + i + p + c + e + r + t >= 0 && b + w + m + k + o + j + q + d + f + s + u >= 0 && a + v + l + h + n + i + p + c + e + r + t <= 9 && b + w + m + k + o + j + q + d + f + s + u <= 9)
																																vacio[a + v + l + h + n + i + p + c + e + r + t][b + w + m + k + o + j + q + d + f + s + u] = bomba[a + v + l + h + n + i + p + c + e + r + t][b + w + m + k + o + j + q + d + f + s + u];//ronda 9

																														}
																													}
																												}
																											}
																										}
																									}
																								}
																							}
																						}
																					}
																				}
																			}
																		}
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

void picture(char vacio[][10],int a,int b)
{
	int x, i, j;

		//i,j variable para for
		// x marca que parte de cada serie hay que imprimir
		system("cls");
		printf(" __________________________________________________ \n");
		for (j = 0; j < 10; j++)
		{
			for (x = 0; x < 3; x++)
			{
				printf("|");
				for (i = 0; i < 10; i++)
				{
					if (x == 0)
					{
						if (i == a && j == b)
							printf("%c%c%c%c%c", 218, 196, 196, 196, 191);
						else
							printf("     ");
					}
					if (x == 1)
					{
						if (vacio[i][j] == '0')
							vacio[i][j] = ' ';
						if (i == a && j == b)
						{
							if (vacio[i][j] == 'x')
								printf("| - |");
							else 
							printf("| %c |", vacio[i][j]);
						}
						else
						{
							if (vacio[i][j] == 'x')
								printf("  -  ");
							else
							printf("  %c  ", vacio[i][j]);
						}
							
					}
					if (x == 2)
					{
						if (i == a && j == b)
							printf("%c%c%c%c%C", 192, 196, 196, 196, 217);
						else//(i!=a)
							printf("     ");
					}
				}
					printf("|\n");
			}
		}
		printf("|__________________________________________________|\n");
	
}
int mov(char *move, int *a,int *b)
{
	int B=0;
	_getch();
	*move = _getch();
	switch (*move)
	{
	case 75://a
		*move = 'a';
		break;
	case 77://d
		*move = 'd';
		break;
	case 72://w
		*move = 'w';
		break;
	case 80://s
		*move = 's';
		break;
	case 13:
		*move = 'r';
		break;
	case 9:
		*move = 't';
		break;
	case 27:
		B = menu();
		if (B == 1)
			*move = 't';
		break;
	}
	if (*move == 'a'&&*a > 0)
		*a-=1;
	if (*move == 'd'&&*a < 9)
		*a+=1;
	if (*move == 's'&&*b < 9)
		*b+=1;
	if (*move == 'w'&&*b > 0)
		*b-=1;
	return B;
}
int menu()
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
			z = 0;
			break;
		case 13:
			a = 'i';
			break;
		}
	}
	return z;

}