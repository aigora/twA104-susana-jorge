#define _CRT_SECURE_NO_DEPRECATE
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<conio.h>
#include<Windows.h>
#include<malloc.h>

#define U 16//valores de las posiciones iniciales
#define V 9
#define W 8
#define X 10



void Titulo();
void Inicializar(char [][19], char [], int [], int [], int *, int *, char *);

void Fantasmas(char[][19], int[], int[], int[], int *, char, char[], int);

void Mover(int *, char [][19], int  *, int  *, int *, char *);
void Picture(char[][19]);
int Menu();


int main()
{
	FILE *ofpt;
	int i = U, j = V, A[4] = { 2,2,2,2 }, P[4] = { 1,2,3,4 }, C[4], D[4], flag = 1, l, n, k = 0, d, I, J, B = 0, sleep=100;
	int puntos = 0,highscore,ronda;
	char t[22][19], pacman = 'O', colafant[4], m = 1, fant = 178, s = 196;
	
	// i,j son las coordenadas del pacman
	//A[] guarda hacia donde iba cada fantasma
	//P[] muestras las cuatro opciones de moverse de cada fantasmas y permite que se muevan aleatoriamente
	//C[] guarda la posicion y de cada fantasma 
	//D[] guarda la posicion x de cada fantasma
	//flag  que diferencia el tiempo en que se puede comer fantasmas y el que no
	// l,n las uso para los for
	//k cuenta cuantos puntos quedan en el tablero y si es cero termina y ganas
	//I marca la posicion y de los fantasmas 
	//J marca la posicion x de los fantasmas
	//B si vale 1 termina el programa, si lo eliges en el menu de pausa
	//sleep muestra el tiempo de delay en cada nivel
	//m guarda la tecla que introduces en el getch/ el ultimo movimiento que has hecho
	//t[][] es la matriz que representa el tablero
	//pacman simbolo del pacman
	//fant simbolo de los fantasmas
	//s simbolo de las paredes de arriba que atrapan a los fantasmas que estan en casa
	//colafant[] guarda el simbolo que hay en el tablero antes de que se lo coma un fantasma para ponerlo despues de vuelta
	//ai se usa en la funcion picture para imprimir el dibujo
	//d muestra en el for de la funcion fant, de que fantasma estamos hablando

	system("pause");

	Titulo();//imprime el titulo del comienzo, sacando el dibujo de un archivo/bloc de notas
	//COMIENZO___________________________________________________________________________________________________________________________
	for (ronda = 0; ronda < 3; ronda++)
	{
		system("cls");
		printf("ronda %d\n", ronda + 1);

		Inicializar(t, colafant, C, D, &i, &j, &m);//inicializa todos loas valores antes de empezar

		clock_t start = 0; //INCIAMOS START QUE CUENTA EL TIEMPO EN QUE LOS FANTASMAS PODRAN SER COMIDOS
		clock_t comienzo = clock();//EMPIEZA EL A CONTAR EL TIEMPO PARA LA SALIDA DE LOS OTROS DOS FANTASMAS

		Picture(t);//IMPRIMIMOS TABLERO
		system("pause");

		while (t[i][j] != 178 && B == 0)
		{
			if (((clock() - comienzo) / CLOCKS_PER_SEC) > 15.0)//CAMBIAMOS LA VALLA QUE ATRAPA A LOS FANTASMAS A LOS 15S PARA QUE SALGAN
				t[9][9] = t[9][8] = t[9][10] = 196;
			t[i][j] = ' ';

			Mover(&puntos, t, &i, &j, &B, &m);//se encarga de llevar a cabo bien el movimiento de pacman

			if (B == 0)
			{
				if (i == 10 && j == 0)//SI LLEGAS AL LADO SIN PARED TE MANDA AL OTRO LADO
					j = 17;
				if (i == 10 && j == 18)
					j = 1;

				if (t[i][j] == '+')
				{
					fant = 177;
					flag = 0;
					start = clock();//COMIENZA EL TIEMPO EN EL QUE PUEDES COMERTE LOS FANTASMAS AL HABER TOMADO LA FRUTA
				}
				if (flag == 0 && ((clock() - start) / CLOCKS_PER_SEC) > 10.0)
				{
					fant = 178;
					flag = 1;
				}

				t[i][j] = pacman;
				t[10][8] = t[10][9] = t[10][10] = ' ';


				Fantasmas(t, &A, &C, &D, &puntos, fant, &colafant, flag); // se encarga del movimiento aleatorio y correcto de los fantasmas

				if (flag == 1 && t[i][j] == fant)//178)// si te comes un fantasma cuando no debes se termina la ronda
					break;
				k = 0;
				for (l = 0; l < 22; l++)
				{
					for (n = 0; n < 19; n++)
					{
						if (t[l][n] == '.')
							k++;
					}
				}
				if (k == 0)//si no queda ningun punto entonces termina la ronda y ganas 5000 puntos
				{
					puntos += 5000; break;
				}
				system("cls");
				printf("puntuacion: %d\n", puntos);
				Picture(t);//imprimimos de nuevo el tablero con los cambios que haya habido
				Sleep(sleep);//dependiendo de la ronda habra mayor o menor delay
			}
			if (B == 1)//si en el menu has decidido acabar, terminara el juego
			{
				break;
				ronda = 3;
			}
		}
		sleep -= 50;
	}
		system("cls");
		Picture(t);// imprime una ultima vez el tablero
		
		ofpt = fopen("puntos.txt", "r");//abre el archivo con el ultimo highscore para leerlo
		fscanf(ofpt, "%d", &highscore);
		fclose(ofpt);

		if (k != 0)printf("\nGAME OVER\n");
		else if (k == 0) 
		{
			printf("VICTORIA\n");
		}
		else if (B == 1)printf("se finalizó la partida\n");
		else printf("error");
		printf("puntuacion final: %d\n", puntos);
		if (puntos > highscore)
		{
			ofpt = fopen("puntos.txt", "w");//abre el mismo archivo pero para escribir si la puntuacion es mayor que el highscore
			printf("nuevo highscore\n");
			fprintf(ofpt, "%d", puntos);
			fclose(ofpt);
		}
	
		system("pause");
}


void Titulo()
{
	FILE *ifpt;
	int l, n, ai,N=0, i=0,k;
	char *t;
	size_t size;
	ifpt = fopen("fant.txt", "r");
	system("color 07");
	t = (char*)calloc(1, sizeof(char));
	while (feof(ifpt) == 0)
	{
		fscanf(ifpt,"%d", &ai);
		t[i] = ai;
		size = _msize(t);
		t = (char*)realloc(t,size+1*sizeof(char));
		i++;
	}
	i = 0;
	while (i < 101)
	{
		system("cls");
		printf("\n%s%c                           ",t, 13);
		k = i;
		printf("\n         ____________________________________________________________________________________________________ \n\t|\n\t|");
		while (k > 0)
		{
			printf("%c", 219);
			k--;
		}
		printf("\n\t|____________________________________________________________________________________________________ \n");
		printf("\t\t\t\t\t\t CARGANDO... %d%c\n", i, 37);
		i += 5;
	}
	system("cls");

	system("color 1E");
	printf("\t\t\t\t _________________________________ \n\t\t\t\t|\t\t\t\t  |\n\t\t\t\t|\tbienvenido al PACMAN\t  |\n");
	printf("\t\t\t\t|\t\t\t\t  |\n\t\t\t\t|_________________________________|\n");
	Sleep(1000);
	printf("\t\t\t\t _______________________________________ \n\t\t\t\t|\t\t\t\t\t|\n");
	printf("\t\t\t\t| flecha >: moverse a la derecha\t|\n\t\t\t\t| flecha <: moverse a la izquierda\t|\n");
	printf("\t\t\t\t| flecha ^: moverse arriba\t\t|\n\t\t\t\t| flecha v: moverse abajo\t\t|\n");
	printf("\t\t\t\t| esc DOS VECES: pausar el juego\t|\n");
	printf("\t\t\t\t|_______________________________________|\n");
	system("pause");
	fclose(ifpt);

}
void Inicializar(char t[][19], char colafant[], int C[], int D[], int *i, int *j, char *m)
{
	FILE *fpt;
	int l, n, ai;


	fpt = fopen("tablero.txt", "r"); //se abre el archivo donde esta dibujado el tablero


	for (l = 0; l < 22; l++)//se guarda el tablero en la matriz 
	{
		for (n = 0; n < 19; n++)
		{
			fscanf(fpt, "%c", &t[l][n]);
		}
	}
	t[0][9] = t[5][9] = t[17][9] = t[13][9] = 194;// estos son valores que no lee el block de notas
	t[17][0] = t[7][5] = 195;
	t[17][18] = t[7][13] = 180;
	t[19][5] = t[19][13] = 193;
	t[0][0] = t[2][2] = t[2][5] = t[2][11] = t[2][15] = t[13][0] = t[9][7] = t[11][15] = t[7][15] = t[15][15] = 218;//izq ar
	t[21][0] = t[3][2] = t[3][5] = t[3][11] = t[3][15] = t[9][15] = t[13][15] = t[11][7] = t[7][0] = 192;//azq ab
	t[0][18] = t[2][3] = t[2][7] = t[2][13] = t[2][16] = t[7][3] = t[11][3] = t[9][11] = t[13][18] = t[15][3] = 191;//der ar
	t[21][18] = t[3][3] = t[3][7] = t[3][13] = t[3][16] = t[9][3] = t[13][3] = t[7][18] = t[11][11] = 217;

	C[0] = W; C[1] = X; C[2] = X; D[0] = X; D[1] = W; D[2] = X; C[3] = W; D[3] = W;//SITUAMOS CADA FANTASMA
	colafant[0] = colafant[1] = colafant[2] = colafant[3] = '.';//INICIAMOS EL VALOR DEL TABLERO QUE SE COMERAN LOS FANTASMAS

	*i = U; *j = V;//SITUAMOS A PACMAN
	*m = 1;//inicializamos el movimient
	fclose(fpt);
}

void Fantasmas(char t[][19], int A[], int C[], int D[], int *puntos, char fant, char colafant[], int y)
{
	int d, I, J, k;
	char s = 196, P[4] = { 1,2,3,4 };
	//fantasmaS__________________________________________________________________________________________________
	for (d = 0; d < 4; d++)
	{
		I = C[d]; J = D[d];
		if (A[d] == 0)//no puede volver hacia atras
			P[1] = 0;
		if (A[d] == 1)
			P[0] = 0;
		if (A[d] == 2)
			P[3] = 0;
		if (A[d] == 3)
			P[2] = 0;

		//si hay una pared en uno de los cuatro lados iguala el punto correspondiente del vector P[] a cero
		if (t[I + 1][J] != ' '&&t[I + 1][J] != '.'&&t[I + 1][J] != '+'&&t[I + 1][J] != 'O'&&t[I + 1][J] != fant)
			P[0] = 0;
		if (t[I - 1][J] != ' '&&t[I - 1][J] != '.'&&t[I - 1][J] != '+'&&t[I - 1][J] != 'O'&&t[I - 1][J] != s && t[I - 1][J] != fant)
			P[1] = 0;
		if (t[I][J + 1] != ' '&&t[I][J + 1] != '.'&&t[I][J + 1] != '+'&&t[I][J + 1] != 'O'&&t[I][J + 1] != fant)
			P[2] = 0;
		if (t[I][J - 1] != ' '&&t[I][J - 1] != '.'&&t[I][J - 1] != '+'&&t[I][J - 1] != 'O'&&t[I][J - 1] != fant)
			P[3] = 0;

		//si un punto del veco p[] es igual a cero no deja que el fantasma vaya por ahí

		if (P[0] == 0 && P[1] == 0 && P[2] == 0 && P[3] == 0)//si no puede hacer nada entonces si deja que vaya hacia atras
		{
			if (A[d] == 0)
				P[1] = 2;
			if (A[d] == 1)
				P[0] = 1;
			if (A[d] == 2)
				P[3] = 4;
			if (A[d] == 3)
				P[2] = 3;
		}
		A[d] = rand() % 4;
		while (P[A[d]] == 0)
		{
			A[d] = rand() % 4;
		}

		t[I][J] = colafant[d];//iguala el punto del tablero con el valor previamente guardado

		if (t[I][J] != ' '&&t[I][J] != '.'&&t[I][J] != '+'&&t[I][J] != s)// si se chocan dos fantasmas pone puntos
			t[I][J] = '.';

		if (I == 10 && J == 0)// teletransporta al fantasma al legar al lado abierto
		{
			J = 17;
			A[d] = 3;
		}

		else if (I == 10 && J == 18)// igual pero en el otro lado
		{
			J = 1;
			A[d] = 2;
		}
		else
		{
			if (A[d] == 0)//mueve al fantasma dependiendo del movimiento aleatorio que haya salido
				I++;
			if (A[d] == 1)
				I--;
			if (A[d] == 2)
				J++;
			if (A[d] == 3)
				J--;
		}
		colafant[d] = t[I][J];//guarda el valor del tablero que hay antes de que se lo coma el fantasma

		t[I][J] = fant;// iguala ese punto al caracter del fantasma

		for (k = 0; k < 4; k++)//reiniciamos los caminos por donde puede ir el fantasma
		{
			P[k] = k + 1;
		}
		if (y == 0 && colafant[d] == 'O')//mietras fant vale 176 si te comes un fantasma ganas 100 puntos y el fantasma vuelve al inicio
		{
			*puntos += 100;
			t[I][J] = colafant[d];
			if (d == 0) { I = W; J = X; }
			else if (d == 1) { I = X; J = W; }
			else if (d == 2) { I = X; J = X; }
			else if (d == 3) { I = W; J = W; }
		}
		C[d] = I; D[d] = J;
	}//FIN FANTASMAS__________________________________________________________________________________________________
}

void Mover(int *puntos, char t[][19],int  *i,int  *j, int *B, char *m)
{
	if (_kbhit() == 1)//NO LEERA EL GETCH (lee cteclas especiales) HASTA QUE SE PRESIONE UNA TECLA
	{
		_getch();
		*m = _getch();
	}
	switch (*m)
	{
		// LE PONGO LAS CONDICIENDOS AL PROGRAMA PARA QUE SE MUEVA PACMAN, SI HAY UN OBSTACULO NO TE DEJA CONTINUAR HACIA DELANTE
	case 75://a
		if (t[*i][*j - 1] == '.' || t[*i][*j - 1] == ' ' || t[*i][*j - 1] == '+')
			(*j)-=1;
		if (t[*i][*j - 1] == '.')//SI TE COMES LOS PUNTOS TU PUNTUACION INCREMENTA
			(*puntos) += 10;
		break;
	case 77://d
		if (t[*i][*j + 1] == '.' || t[*i][*j + 1] == ' ' || t[*i][*j + 1] == '+')
			(*j)+=1;
		if (t[*i][*j + 1] == '.')
			(*puntos) += 10;
		break;
	case 72://w
		if (t[*i - 1][*j] == '.' || t[*i - 1][*j] == ' ' || t[*i - 1][*j] == '+')
			(*i)-=1;
		if (t[*i - 1][*j] == '.')
			(*puntos) += 10;
		break;
	case 80://s
		if (t[*i + 1][*j] == '.' || t[*i + 1][*j] == ' ' || t[*i + 1][*j] == '+')
			(*i)+=1;
		if (t[*i + 1][*j] == '.')
			(*puntos) += 10;
		break;
	case 27:
		*B = Menu();
		*m = 1;
		break;
	}
	
}
void Picture(char t[][19])
{
	char *T;
	int i=0, j=0, a=0;
	size_t size;
	T = (char*)calloc(2, sizeof(char));
	for (i = 0; i < 22; i++)
	{
		for (j = 0; j < 19; j++)
		{
			T[a]=t[i][j];
			a++;
			if (j < 18)
				T[a] = ' ';
			else
				T[a] = 10;
			a++;
			size = _msize(T);
			T = (char*)realloc(T,size+2*sizeof(char));
		}	
	}
	T[a] = ' ';
	a++;
	T[a] = 10;
	printf("%s%c                                                                                                                                                     ", T,13);
	free(T);
}
int Menu()
{
	FILE *fpt, *ofpt;
	int i, j, y = 0;
	char si[9][24], a = 'a', no[9][24];
	fpt = fopen("sino.txt", "r");

	ofpt = fopen("nosi.txt", "r");

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
	printf("Pause:\n ¿Quieres dejar la partida?\n");
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
			y = 1;
			break;
		case 75:
			a = 'a';
			y = 0;
			break;
		case 13:
			a = 'i';
			break;
		}
	}
	if (y == 1)
		return 1;
	if (y == 0)
		return 0;
	fclose(fpt);
	fclose(ofpt);
}