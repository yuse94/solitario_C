/* SOLITARIO CLASICO EN C
 *
 * @autor: Youssef Abarca
 * @version 2.0
 * Juega solitario desde la consola.
 *
 * INTERFAZ EN CONSOLA

      ♠   ♥   ♣   ♦  Solitario  ♦   ♣   ♥   ♠

    Monton: |_░░_|
    Pila base: |_♥_|_♦_|_♣_|_♠_|

         0    1    2    3    4    5    6
      ____________________________________
     0|_9♦_|_░░_|_░░_|_░░_|_░░_|_░░_|_░░_|0
     1|____|_6♦_|_░░_|_░░_|_░░_|_░░_|_░░_|1
     2|____|____|_1♥_|_░░_|_░░_|_░░_|_░░_|2
     3|____|____|____|_3♣_|_░░_|_░░_|_░░_|3
     4|____|____|____|____|_0♠_|_░░_|_░░_|4
     5|____|____|____|____|____|_6♣_|_░░_|5
     6|____|____|____|____|____|____|_Q♠_|6
     7|____|____|____|____|____|____|____|7
     8|____|____|____|____|____|____|____|8
     9|____|____|____|____|____|____|____|9
    10|____|____|____|____|____|____|____|10
    11|____|____|____|____|____|____|____|11
    12|____|____|____|____|____|____|____|12
    13|____|____|____|____|____|____|____|13
    14|____|____|____|____|____|____|____|14
    15|____|____|____|____|____|____|____|15
    16|____|____|____|____|____|____|____|16
    17|____|____|____|____|____|____|____|17
    18|____|____|____|____|____|____|____|18

    8**********MENU**********8

    1. Morver cartas dentro del tablero
    2. Morver carta del monton al tablero
    3. Cambiar carta del monton
    4. Desocultar carta del tablero
    5. Enviar carta a la pila base
    6. Salir

    Opcion:

 *
 */

// LIBRERIAS

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>

// DEFINICIONES

#define p printf
#define s scanf

// VARIABLES GLOBALES

// Caracter para ocultar carta
unsigned char cartaPartePosterior=176;

// Cartas dentro de la baraja
unsigned char numBaraja[53]={'0','1','2','3','4','5','6','7','8','9','0','J','Q','K',
                                 '1','2','3','4','5','6','7','8','9','0','J','Q','K',
							     '1','2','3','4','5','6','7','8','9','0','J','Q','K',
							     '1','2','3','4','5','6','7','8','9','0','J','Q','K'};

// Palos (Símboles) correspondientes a cada carta de la baraja
// El primero es cero debido a que se usa ese espacio para
// ocultar las cartas del monton con un caracter especial '176'
unsigned char palosBaraja[53]={0,3,3,3,3,3,3,3,3,3,3,3,3,3,
                                 4,4,4,4,4,4,4,4,4,4,4,4,4,
                                 5,5,5,5,5,5,5,5,5,5,5,5,5,
                                 6,6,6,6,6,6,6,6,6,6,6,6,6};

// Variables para guardar las cartas de forma aleatoria
unsigned char barajaMezclada[53];
unsigned char paloMezclado[53];

// Espacios para las cartas y los palos dentro del tablero
unsigned char barajaTablero[19][7];
unsigned char palosTablero[19][7];

// Arreglo para guardar la pila base
unsigned char palos[4]={3,4,5,6};

// Variables para controlar el estado de las cartas en el monton
unsigned char numCartaMonton=0;         // Guarda la carta actual que se esta mostrando
unsigned char paloCartaMonton=0;        // Guarda el palo actual que se esta mostrando
unsigned int posCartaMonton=0;          // Posicíon de la carta del monton a mostrar
unsigned int cantidadCartasMonton = 24; // Cantidad de cartas en el monton

// Variable para salir de juego
unsigned char salirDelJuego = 'n';

// FUNCIONES

void musicaJuegoNuevo();
void titulo ();
void barajar ();
void ocultarCartas();
void tableroJuego ();
void menuJuego ();
void juego ();

unsigned char cambiarCartaMazo();
void quitarCartaMoton();
void moverCartasTablero ( unsigned char f1,  unsigned char c1,
                            unsigned char f, unsigned char c );

void gameOver ();

int main()
{
    // Iniciamos la función System con color estandar que
    // nos permite más adelante cambiar los colores
	system("color 07");

	// Cargamos el título
    titulo ();

	musicaJuegoNuevo();


    barajar ();
	ocultarCartas();

	p("Presione cualquier tecla para empezar\n\n");
	getch();

	// Inicia el juego
	juego();

	// Termina el juego
	gameOver ();

	p("ADIOS.\nPresione cualquier tecla para salir\n\n");
	getch();

	return 0;
}

/*
 * Function:  musicaJuegoNuevo
 * --------------------
 * Reproduce un Beep con una nota con un tiempo determinado
 * hasta terminar todas las notas
 */
void musicaJuegoNuevo()
{
	unsigned char i;
	unsigned int notas[7]={294,247,330,330,330,220,392};
	unsigned int tiempo[7]={294,247,330,330,330,220,392};

	for(i = 0; i < 7; i++)
	{
		Beep (notas[i],tiempo[i]);
	}
}

/*
 * Function:  titulo
 * --------------------
 * Imprime el título:
   ♠   ♥   ♣   ♦  Solitario  ♦   ♣   ♥   ♠
 */
void titulo ()
{
    p("\n");
    p("\033[0m%3c",6);
    p("\033[1;31m%4c",3);
    p("\033[0m%4c",5);
    p("\033[1;31m%4c",4);
    p("\033[0m");

	p("  Solitario");

    p("\033[1;31m%3c",4);
    p("\033[0m%4c",5);
    p("\033[1;31m%4c",3);
    p("\033[0m%4c",6);

    p("\n");
}

/*
 * Function:  barajar
 * --------------------
 * Toma los arreglos numBaraja y palosBaraja y los mezcla
 * sin tomar la primera posición
 */
void barajar ()
{
    // Variable de control para saber si una posición ya fue
	// movida
	unsigned char estalibre[53];

	// pos: posición aleatoria
	unsigned char i, pos;

	// Generación de número aleatorio
	time_t t;
	srand((unsigned) time(&t));

	// Establece las pociciones libres y las ocupadas
	// 1 -> libre, 0 -> ocupado
	// Las posiciones libres seria del 1-52
	estalibre[0]=0;
	for(i =0; i<52; i++)
	{
		estalibre[i+1]=1;
	}

	// Genera una posición aleatoria para barajaMezclada y
	// paloMezclado y en esta se guardanda cada una de las
	// cartas de numBaraja y palosBaraja
	for(i=0; i<52; i++)
	{
		pos = rand()%52;    // random 1-52

		while (estalibre[pos+1]==0) // Mientras el espacio no este libre
                                    // genera una posición aleatoria
		{
			pos = rand()%52; // random 1-52

		}

		barajaMezclada[pos+1]=numBaraja[i+1];
		paloMezclado[pos+1]=palosBaraja[i+1];
		estalibre[pos+1]=0;     // Una vez utilizada una posición se marca
                                // como ocupada
	}

	// La primera posición se usa para ocultar las cartas
	// del monton
	barajaMezclada[0] = cartaPartePosterior;
	paloMezclado[0] = cartaPartePosterior;
}

/*
 * Function:  ocultarCartas
 * --------------------
 * Pone en todas los posiones del tablero un '_' para la carta
 * y '_' para el palo. Posteriormente, oculta los espacios donde
 * deberian aparecer cartas con su respectivo palo. Y por último
 * coloca las ultimas 7 cartas de nuestra baraja mezclada sobre
 * el tablero, posiciones 46-52
 *
         0    1    2    3    4    5    6
      ____________________________________
     0|_9♦_|_░░_|_░░_|_░░_|_░░_|_░░_|_░░_|0
     1|____|_6♦_|_░░_|_░░_|_░░_|_░░_|_░░_|1
     2|____|____|_1♥_|_░░_|_░░_|_░░_|_░░_|2
     3|____|____|____|_3♣_|_░░_|_░░_|_░░_|3
     4|____|____|____|____|_0♠_|_░░_|_░░_|4
     5|____|____|____|____|____|_6♣_|_░░_|5
     6|____|____|____|____|____|____|_Q♠_|6
 *
 */
void ocultarCartas()
{
	unsigned char i, j, contaJ = 1;

	for (i=0; i<19; i++)
	{
		for (j=0; j<7; j++)
		{
			barajaTablero[i][j]='_';
			palosTablero[i][j]='_';
		}
	}

	for (i=0; i<6; i++)
	{
		for (j=contaJ; j<7; j++)
		{
			barajaTablero[i][j]=cartaPartePosterior;
			palosTablero[i][j]=cartaPartePosterior;
		}
		contaJ++; // Suma para pasar a la siguiente columna
	}

	for (i=0; i<7; i++)
	{
		barajaTablero[i][i]=barajaMezclada[46+i];
		palosTablero[i][i]=paloMezclado[46+i];
	}
}

/*
 * Function:  tableroJuego
 * --------------------
 * Dibuja el tablero de juego con el estado actual de las cartas y palos
 * Dependiendo si el palo es rojo o negro, cambia el color de la fuente
 */
void tableroJuego ()
{
	unsigned char i,j;

	system("cls");

	titulo ();

	numCartaMonton=barajaMezclada[posCartaMonton];
	paloCartaMonton=paloMezclado[posCartaMonton];

	p("\nMonton: ");
	p("|");
	p("_");

	if(paloCartaMonton == 3 || paloCartaMonton == 4)
    {
        p("\033[1;31m%c%c", numCartaMonton,paloCartaMonton);
        p("\033[0m");
	}
	else
        p("%c%c", numCartaMonton,paloCartaMonton);

	p("_|");


	p("\nPila base: ");

	for (i=0; i<4; i++)
	{
		p("|");
		p("_");

		if(i < 2)
        {
            p("\033[1;31m%c%c", palos[i],i+3);
            p("\033[0m");
        }
        else
            p("%c%c", palos[i],i+3);

		p("_");
	}
	p("| \n\n");

	p("     0    1    2    3    4    5    6\n");
	p("  ____________________________________\n");
	for (i=0; i<19; i++)
	{
		if(i<10){p(" %d",i);}
		else{p("%d",i);}

		for (j=0; j<7; j++)
		{
			p("|");
			p("_");

            if(palosTablero[i][j] == 3 || palosTablero[i][j] == 4)
            {
                p("\033[1;31m%c%c", barajaTablero[i][j],palosTablero[i][j]);
                p("\033[0m");
            }
            else
                p("%c%c",barajaTablero[i][j],palosTablero[i][j]);

			p("_");
		}
		p("|%d\n",i);
	}
}

/*
 * Function:  menuJuego
 * --------------------
 * Menú de opciones para jugar
 */
void menuJuego ()
{
    // Variables para el control de posición
    // f=fila actual, c=columna actual, f1=fila futura, c1=columna futura
	unsigned int opcion,f,c,f1,c1;

	Beep (300,300);

	p("\n8**********MENU**********8\n\n");
	p("1. Morver cartas dentro del tablero\n");
	p("2. Morver carta del monton al tablero\n");
    p("3. Cambiar carta del monton\n");
    p("4. Desocultar carta del tablero\n");
    p("5. Enviar carta a la pila base\n");
    p("6. Salir\n\n");
	p("Opcion: ");
	s("%d", &opcion);

	switch (opcion)
	{
        case 1:
            p("Ingrese la posicion actual 'fila columna': ");
            s("%d",&f);
            s("%d",&c);

            p("Ingrese la nueva posicion: ");
            s("%d",&f1);
            s("%d",&c1);

            if(barajaTablero[f1][c1]=='_')
            {
                if(barajaTablero[f][c]=='K' && f1 == 0) // Condiciones para colocar K
                {
                    moverCartasTablero (f1, c1, f, c);
                }

                //                                     ROJOS                                                   NEGROS
                else if(((palosTablero[f][c]==3 || palosTablero[f][c]==4) && (palosTablero[f1-1][c1]==5 || palosTablero[f1-1][c1]==6)) ||
                    ((palosTablero[f][c]==5 || palosTablero[f][c]==6) && (palosTablero[f1-1][c1]==3 || palosTablero[f1-1][c1]==4)))
                {
                    if(barajaTablero[f1-1][c1]==barajaTablero[f][c]+1 &&
                       barajaTablero[f][c]!='J' && barajaTablero[f][c]!='0')    // Condiciones para colocar cartas del 1-8
                                                                                // debido a que J, K y 0, 1 son caracteres seguidos se
                                                                                // quitan estas opción como movimiento válido
                    {
                        moverCartasTablero(f1, c1, f, c);
                    }

                    else if(barajaTablero[f][c]=='9' && barajaTablero[f1-1][c1]=='0') // Condiciones para colocar 9
                    {
                        moverCartasTablero (f1, c1, f, c);
                    }

                    else if(barajaTablero[f][c]=='0' && barajaTablero[f1-1][c1]=='J') // Condiciones para colocar 10 == 0
                    {
                        moverCartasTablero (f1, c1, f, c);
                    }

                    else if(barajaTablero[f][c]=='J' && barajaTablero[f1-1][c1]=='Q') // Condiciones para colocar J
                    {
                        moverCartasTablero (f1, c1, f, c);
                    }

                    else if(barajaTablero[f][c]=='Q' && barajaTablero[f1-1][c1]=='K') // Condiciones para colocar Q
                    {
                        moverCartasTablero (f1, c1, f, c);
                    }
                }
            }
            break;

		case 2:
            p("Ingrese la posicion 'fila columna': ");

            s("%d", &f1);
            s("%d", &c1);

            if(numCartaMonton=='K' && f1 == 0) // Condiciones para colocar K
            {
                barajaTablero[f1][c1]=numCartaMonton;
                palosTablero[f1][c1]=paloCartaMonton;
                quitarCartaMoton();
            }

            else if(barajaTablero[f1][c1]=='_')
            {
                //                                     ROJOS                                                   NEGROS
                if(((paloCartaMonton==3 || paloCartaMonton==4) && (palosTablero[f1-1][c1]==5 || palosTablero[f1-1][c1]==6)) ||
                    ((paloCartaMonton==5 || paloCartaMonton==6) && (palosTablero[f1-1][c1]==3 || palosTablero[f1-1][c1]==4)))
                {

                    if(barajaTablero[f1-1][c1]==numCartaMonton+1 &&
                       numCartaMonton!='J' && numCartaMonton!='0')  // Condiciones para colocar cartas del 1-8
                                                                    // debido a que J, K y 0, 1 son caracteres seguidos se
                                                                    // quitan estas opción como movimiento válido
                    {
                        barajaTablero[f1][c1]=numCartaMonton;
                        palosTablero[f1][c1]=paloCartaMonton;
                        quitarCartaMoton();
                    }

                    else if(numCartaMonton=='9' &&  barajaTablero[f1-1][c1]=='0') // Condiciones para colocar 9
                    {
                        barajaTablero[f1][c1]=numCartaMonton;
                        palosTablero[f1][c1]=paloCartaMonton;
                        quitarCartaMoton();
                    }

                    else if(numCartaMonton=='0' &&  barajaTablero[f1-1][c1]=='J') // Condiciones para colocar 10 == 0
                    {
                        barajaTablero[f1][c1]=numCartaMonton;
                        palosTablero[f1][c1]=paloCartaMonton;
                        quitarCartaMoton();
                    }

                    else if(numCartaMonton=='J' &&  barajaTablero[f1-1][c1]=='Q') // Condiciones para colocar J
                    {
                        barajaTablero[f1][c1]=numCartaMonton;
                        palosTablero[f1][c1]=paloCartaMonton;
                        quitarCartaMoton();
                    }

                    else if(numCartaMonton=='Q' &&  barajaTablero[f1-1][c1]=='K') // Condiciones para colocar Q
                    {
                        barajaTablero[f1][c1]=numCartaMonton;
                        palosTablero[f1][c1]=paloCartaMonton;
                        quitarCartaMoton();
                    }
                }
            }
            break;

        case 3:
            cambiarCartaMazo();
            break;

        case 4:
			p("Posicion 'fila columna': ");
			s("%d", &f);
			s("%d", &c);

            // Para desocultar una carta el espacio de abajo debe de estar sin cartas
			if(barajaTablero[f][c]==cartaPartePosterior && barajaTablero[f+1][c]=='_')
			{
			    // Las cartas ocultas se toman de los arreglos mezclados
			    // desde la posición 25-45
				if(f==0)    //Cartas ocultas en la fila 0
				{
					barajaTablero[f][c]=barajaMezclada[24 + c];
					palosTablero[f][c]=paloMezclado[24 + c];
				}

				if(f==1)    //Cartas ocultas en la fila 1
				{
					barajaTablero[f][c]=barajaMezclada[29 + c];
					palosTablero[f][c]=paloMezclado[29 + c];
				}

				if(f==2)    //Cartas ocultas en la fila 2
				{
					barajaTablero[f][c]=barajaMezclada[33 + c];
					palosTablero[f][c]=paloMezclado[33 + c];
				}

				if(f==3)    //Cartas ocultas en la fila 3
				{
					barajaTablero[f][c]=barajaMezclada[36 + c];
					palosTablero[f][c]=paloMezclado[36 + c];
				}

				if(f==4)    //Cartas ocultas en la fila 4
				{
					barajaTablero[f][c]=barajaMezclada[38 + c];
					palosTablero[f][c]=paloMezclado[38 + c];
				}

				if(f==5)    //Cartas ocultas en la fila 5
				{
					barajaTablero[f][c]=barajaMezclada[39 + c];
					palosTablero[f][c]=paloMezclado[39 + c];
				}
			}
			break;

        case 5:
            // Enviar cartas a la pila base
            p("1. Del tablero\n2. Del monton\n");
			p("Respuesta: ");
			s("%d", &opcion);

			switch(opcion)
			{
                case 1:
                    p("Posicion 'fila columna': ");
                    s("%d",&f);
                    s("%d",&c);

                    // Verificar que no haya nada debajo de la carta a enviar
                    if(barajaTablero[f+1][c]=='_')
                    {
                        // Condiciones para enviar 1
                        if(barajaTablero[f][c]=='1')
                        {
                            palos[palosTablero[f][c]-3]=barajaTablero[f][c];    //Si es ♥ entonces palos[0], si es ♦ entoces palos[1]...
                            barajaTablero[f][c]='_';
                            palosTablero[f][c]='_';
                        }

                        // Condiciones para enviar del 2-9
                        else if(barajaTablero[f][c]-1 == palos[palosTablero[f][c]-3] && barajaTablero[f][c] != 'K') // Condiciones para colocar cartas del 1-8
                                                                                                                    // debido a que J, K son letras seguidas se
                                                                                                                    // quitar esta opción como movimiento válido
                        {
                            palos[palosTablero[f][c]-3]=barajaTablero[f][c];
                            barajaTablero[f][c]='_';
                            palosTablero[f][c]='_';
                        }

                        // Condiciones para enviar 10==0
                        else if(palos[palosTablero[f][c]-3]=='9' && barajaTablero[f][c]=='0')
                        {
                            palos[palosTablero[f][c]-3]=barajaTablero[f][c];
                            barajaTablero[f][c]='_';
                            palosTablero[f][c]='_';
                        }

                        // Condiciones para enviar J
                        else if(palos[palosTablero[f][c]-3]=='0' && barajaTablero[f][c]=='J')
                        {
                            palos[palosTablero[f][c]-3]=barajaTablero[f][c];
                            barajaTablero[f][c]='_';
                            palosTablero[f][c]='_';
                        }

                        // Condiciones para enviar Q
                        else if(palos[palosTablero[f][c]-3]=='J' && barajaTablero[f][c]=='Q')
                        {
                            palos[palosTablero[f][c]-3]=barajaTablero[f][c];
                            barajaTablero[f][c]='_';
                            palosTablero[f][c]='_';
                        }

                        // Condiciones para enviar K
                        else if(palos[palosTablero[f][c]-3]=='Q' && barajaTablero[f][c]=='K')
                        {
                            palos[palosTablero[f][c]-3]=barajaTablero[f][c];
                            barajaTablero[f][c]='_';
                            palosTablero[f][c]='_';
                        }
                    }
                    break;

                case 2:
                    // Condiciones para enviar 1
                    if(numCartaMonton=='1')
                    {
                        palos[paloCartaMonton-3]=numCartaMonton;
                        quitarCartaMoton();
                    }

                    // Condiciones para enviar del 2-9
                    else if(numCartaMonton-1 == palos[paloCartaMonton-3] && numCartaMonton!='K')    // Condiciones para colocar cartas del 1-8
                                                                                                    // debido a que J, K son letras seguidas se
                                                                                                    // quitar esta opción como movimiento válido
                    {
                        palos[paloCartaMonton-3]=numCartaMonton;    //Si es ♥ entonces palos[0], si es ♦ entoces palos[1]...
                        quitarCartaMoton();
                    }

                    // Condiciones para enviar 10==0
                    else if(palos[paloCartaMonton-3]=='9' && numCartaMonton=='0')
                    {
                        palos[paloCartaMonton-3]=numCartaMonton;
                        quitarCartaMoton();
                    }

                    // Condiciones para enviar J
                    else if(palos[paloCartaMonton-3]=='0' && numCartaMonton=='J')
                    {
                        palos[paloCartaMonton-3]=numCartaMonton;
                        quitarCartaMoton();
                    }

                    // Condiciones para enviar Q
                    else if(palos[paloCartaMonton-3]=='J' && numCartaMonton=='Q')
                    {
                        palos[paloCartaMonton-3]=numCartaMonton;
                        quitarCartaMoton();
                    }

                    // Condiciones para enviar K
                    else if(palos[paloCartaMonton-3]=='Q' && numCartaMonton=='K')
                    {
                        palos[paloCartaMonton-3]=numCartaMonton;
                        quitarCartaMoton();
                    }
                    break;
            }
            break;

        case 6:
            // Salir del juego
			p("\nDesea salir del juego?:\n1. Si\n2. No\n");
			p("Respuesta: ");
			s("%d", &opcion);

			switch(opcion)
			{
				case 1:
					salirDelJuego = 's';
					break;

				case 2:
					break;
			}
	}
}

/*
 * Function:  juego
 * --------------------
 * Actualiza el tablero y el menú hasta que las condiciones
 * de fin del juego se cumplan
 */
void juego ()
{
	do
	{
		tableroJuego();
		menuJuego();
	}
	while ((palos[0]!='K' || palos[1]!='K' || palos[2]!='K' || palos[3]!='K') && salirDelJuego == 'n');
}

/*
 * Function:  cambiarCartaMazo
 * --------------------
 * Va cambiando la posición de la carta del monton a mostrar
 * return: posición de la carta del monton para mostrar
 */
unsigned char cambiarCartaMazo()
{

	if(posCartaMonton!=cantidadCartasMonton)
	{
		posCartaMonton++;
	}
	else {posCartaMonton=0;}

	return posCartaMonton;

}

/*
 * Function:  quitarCartaMoton
 * --------------------
 * Siempre que se usa mueve todas las cartas que estan
 * seguidas a la carta que se quito a una posición anterior
 * y coloca la carta que se quito al final del arreglo que se usa
 * para el monton (1-24) de monton. Por ultimo reduce el tamaño
 * del monton y la posición para mostrar en el monton la posición
 * anterior
 */
void quitarCartaMoton()
{
	unsigned char i;

	for(i=posCartaMonton; i<cantidadCartasMonton; i++)
	{
		barajaMezclada[i]=barajaMezclada[i+1];
		paloMezclado[i]=paloMezclado[i+1];
	}

	barajaMezclada[cantidadCartasMonton]=numCartaMonton;
	paloMezclado[cantidadCartasMonton]=paloCartaMonton;

	posCartaMonton--;
	cantidadCartasMonton--;
}

/*
 * Function:  moverCartasTablero
 * --------------------
 * Mueve toda la pila de cartas del tablero a la nueva posición
 * f1: fila a mover
 * c1: columna a mover
 * f:  fila actual
 * c:  columna actual
 */
void moverCartasTablero (unsigned char f1, unsigned char c1, unsigned char f, unsigned char c)
{
	unsigned char n=0;

	do
	{
		barajaTablero[f1+n][c1]=barajaTablero[f+n][c];
		barajaTablero[f+n][c]='_';
		palosTablero[f1+n][c1]=palosTablero[f+n][c];
		palosTablero[f+n][c]='_';
		n++;
	}
	while(barajaTablero[f+n][c]!='_');
}

/*
 * Function:  gameOver
 * --------------------
 * En caso de haber ganado el juego reproduce
 * la melodia de game over y la animación
 */
void gameOver ()
{
	unsigned int notas[7]={294,247,330,330,330,220,392};
	unsigned int tiempo[7]={294,247,330,330,330,220,392};
	unsigned char conta=0;
	unsigned char i;

	system("cls");

	if(salirDelJuego=='n')
    {
        do
        {
            for(i = 3; i < 7; i++)
            {
                system("cls");

                p("\n\n");
                p("     %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", i, i,i, i,i, i,i, i,i, i,i, i,i, i,i, i);
                p("     %c  Has ganado  %c\n", i, i);
                p("     %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n\n", i, i,i, i,i, i,i, i,i, i,i, i,i, i,i, i);

                if(i < 5 ){system("color 7C");}
                else{system("color 70");}

                if(conta < 7)
                {
                    Beep (notas[conta],tiempo[conta]);
                }
                conta++;
            }
        }
        while(conta<7);
	}
}
