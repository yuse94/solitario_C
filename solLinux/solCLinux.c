#include <stdlib.h>
#include <unistd.h>   //_getch
#include <termios.h>  //_getch
#include <stdio.h>
#include <time.h>

#define p printf
#define s scanf

unsigned char cartaPartePosterio=176;

unsigned char numBaraja[53]={'0','1','2','3','4','5','6','7','8','9','0','J','Q','K',
								'1','2','3','4','5','6','7','8','9','0','J','Q','K',
								'1','2','3','4','5','6','7','8','9','0','J','Q','K',
								'1','2','3','4','5','6','7','8','9','0','J','Q','K'};
								
unsigned char palosBaraja[53]={0,35,35,35,35,35,35,35,35,35,35,35,35,35,
								36,36,36,36,36,36,36,36,36,36,36,36,36,
								37,37,37,37,37,37,37,37,37,37,37,37,37,
						        38,38,38,38,38,38,38,38,38,38,38,38,38};

unsigned char barajaMezclada[53];
unsigned char paloMezclado[53];

unsigned char barajaTablero[19][7];
unsigned char palosTablero[19][7];

unsigned char palos[4]={' ',' ',' ',' '};

unsigned char numCartaMonton;
unsigned char paloCartaMonton;

unsigned int posCartaMonton=0;
unsigned int cantidadCartasMonton = 24;

//FUNCIONES
void musicaJuegoNuevo();

void barajar ();
void ocultarCartas();
void tableroJuego ();
void menuJuego ();
void juego ();

unsigned char cambiarCartaMazo();
void quitarCartaMoton();
void moverCartasTablero ( unsigned char f1,  unsigned char c1, unsigned char f, unsigned char c );

void gameOver ();

char getch();

int main()
{

	p("\n\n%3c%4c%4c%4c Solitario%2c%4c%4c%4c\n\n",35,36,37,38,38,37,36,35);
	musicaJuegoNuevo();
	p("Presione cualquier tecla para empezar\n\n");

	barajar ();
	ocultarCartas();
	getch();

	juego();
	gameOver ();

	p("FELICIDADES.\nPresione cualquier tecla para salir\n\n");
	getch();

	return 0;
}

void musicaJuegoNuevo()
{
	unsigned char i;
	//unsigned int notas[8]={294,247,330,330,330,220,392};
	//unsigned int tiempo[8]={294,247,330,330,330,220,392};

	for(i = 0; i < 8; i++)
	{
		//Beep (notas[i],tiempo[i]);
	}
}

void barajar ()
{
	unsigned char estalibre[53];
	unsigned char i,pos;
	time_t t;

	srand((unsigned) time(&t));

	estalibre[0]=0;

	for(i=0; i<52; i++)
	{
		estalibre[i+1]=1;  //1 -> libre, 0 -> ocupado
	}

	for(i=0; i<52; i++)
	{
		pos=rand()%52;

		while (estalibre[pos+1]==0)
		{
			pos=rand()%52; //# 1 al 52
		}

		barajaMezclada[pos+1]=numBaraja[i+1];
		paloMezclado[pos+1]=palosBaraja[i+1];
		estalibre[pos+1]=0;
	}

	barajaMezclada[0] = cartaPartePosterio;
	paloMezclado[0] = cartaPartePosterio;
}

void ocultarCartas()
{
	unsigned char i, j, contaJ = 1;

	for (i=0; i<19; i++)
	{
		for (j=0; j<7; j++)
		{
			barajaTablero[i][j]=' ';
			palosTablero[i][j]=' ';
		}
	}

	for (i=0; i<6; i++)
	{
		for (j=contaJ; j<7; j++)
		{
			barajaTablero[i][j]=cartaPartePosterio;
			palosTablero[i][j]=cartaPartePosterio;
		}
		contaJ++;
	}

	for (i=0; i<7; i++)
	{
		barajaTablero[i][i]=barajaMezclada[46+i];
		palosTablero[i][i]=paloMezclado[46+i];
	}
}

void tableroJuego ()
{
	unsigned char i,j;

	system("clear");

	p("\n\n%3c%4c%4c%4c Solitario%2c%4c%4c%4c\n\n",35,36,37,38,38,37,36,35);

	numCartaMonton=barajaMezclada[posCartaMonton];
	paloCartaMonton=paloMezclado[posCartaMonton];

	p("\nBaraja: ");
	p("|");
	p("_");
	p("%c%c", numCartaMonton,paloCartaMonton);
	p("_");
	p("| \n\n\n");

	p("%3c%4c%4c%4c\n",35,36,37,38);
	for (i=0; i<4; i++)
	{
		p("|");
		p("_");
		p("%c", palos[i]);
		p("_");
	}
	p("| \n\n\n");

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
			p("%c%c",barajaTablero[i][j],palosTablero[i][j]);
			p("_");
		}
		p("|%d\n",i);
	}
}

void menuJuego ()
{
	unsigned int opcion,f,c,f1,c1;

	//Beep (300,100);

	p("\n8**********MENU**********8\n\n");
	p("1. Selecione una carta\n2. Desocultar carta\n3. Cambiar carta del monton\n4. Salir\n\n");
	p("Opcion: ");
	s("%d", &opcion);

	switch (opcion)
	{
		case 1:
			p("\n1. La carta del monton\n2. Una carta del tablero\n");
			p("Opcion: ");
			s("%d", &opcion);

			switch (opcion)
			{
				case 1:
					p("\n1. Mover la carta a:\n2. Enviar carta:\n");
					p("Opcion: ");
					s("%d", &opcion);

					switch (opcion)
					{
						case 1:
							p("\nIngrese la posicion a la que desea mover 'fila columna': ");

							s("%d", &f1);
							s("%d", &c1);

							if(barajaTablero[f1][c1]==' ')
							{
								//                                     ROJOS                                                   NEGROS
								if(((paloCartaMonton==35 || paloCartaMonton==36) && (palosTablero[f1-1][c1]==37 || palosTablero[f1-1][c1]==38)) || ((paloCartaMonton==37 || paloCartaMonton==38) && (palosTablero[f1-1][c1]==35 || palosTablero[f1-1][c1]==36)))
								{

									if(barajaTablero[f1-1][c1]==numCartaMonton+1 && numCartaMonton!='J')  // 1 al 8
									{
										barajaTablero[f1][c1]=numCartaMonton;
										palosTablero[f1][c1]=paloCartaMonton;
										quitarCartaMoton();
									}

									else if(numCartaMonton=='9' &&  barajaTablero[f1-1][c1]=='0') //9
									{
										barajaTablero[f1][c1]=numCartaMonton;
										palosTablero[f1][c1]=paloCartaMonton;
										quitarCartaMoton();
									}

									else if(numCartaMonton=='0' &&  barajaTablero[f1-1][c1]=='J') //10 == 0
									{
										barajaTablero[f1][c1]=numCartaMonton;
										palosTablero[f1][c1]=paloCartaMonton;
										quitarCartaMoton();
									}

									else if(numCartaMonton=='J' &&  barajaTablero[f1-1][c1]=='Q') //J
									{
										barajaTablero[f1][c1]=numCartaMonton;
										palosTablero[f1][c1]=paloCartaMonton;
										quitarCartaMoton();
									}

									else if(numCartaMonton=='Q' &&  barajaTablero[f1-1][c1]=='K') //Q
									{
										barajaTablero[f1][c1]=numCartaMonton;
										palosTablero[f1][c1]=paloCartaMonton;
										quitarCartaMoton();
									}
								}

								if(numCartaMonton=='K' && f1==0) // K
								{
									barajaTablero[f1][c1]=numCartaMonton;
									palosTablero[f1][c1]=paloCartaMonton;
									quitarCartaMoton();
								}
							}
							break;

						case 2:
							if(numCartaMonton==49)
							{
								palos[paloCartaMonton-35]=numCartaMonton;
								quitarCartaMoton();
							}

							else if(numCartaMonton-1 == palos[paloCartaMonton-35] && numCartaMonton!='K')
							{
								palos[paloCartaMonton-35]=numCartaMonton;    //Si es ♥ entonces palos[0], si es ♦ entoces palos[1]...
								quitarCartaMoton();
							}

							else if(palos[paloCartaMonton-35]=='9' && numCartaMonton=='0')
							{
								palos[paloCartaMonton-35]=numCartaMonton;
								quitarCartaMoton();
							}

							else if(palos[paloCartaMonton-35]=='0' && numCartaMonton=='J')
							{
								palos[paloCartaMonton-35]=numCartaMonton;
								quitarCartaMoton();
							}

							else if(palos[paloCartaMonton-35]=='J' && numCartaMonton=='Q')
							{
								palos[paloCartaMonton-35]=numCartaMonton;
								quitarCartaMoton();
							}

							else if(palos[paloCartaMonton-35]=='Q' && numCartaMonton=='K')
							{
								palos[paloCartaMonton-35]=numCartaMonton;
								quitarCartaMoton();
							}
							break;
					}
					break;

				case 2:
					p("\n1. Mover la carta a:\n2. Enviar  a:\n");
					p("Opcion: ");
					s("%d", &opcion);

					switch (opcion)
					{
						case 1:
							p("\nIngrese la posicion de la carta 'fila columna': ");
							s("%d",&f);
							s("%d",&c);

							while(barajaTablero[f][c]==' ')
							{
								s("%d",&f);
								s("%d",&c);
							}

							p("\nIngrese la nueva posicion: ");
							s("%d",&f1);
							s("%d",&c1);

							if(barajaTablero[f1][c1]==' ')
							{
								//                                     ROJOS                                                   NEGROS
								if(((palosTablero[f][c]==35 || palosTablero[f][c]==36) && (palosTablero[f1-1][c1]==37 || palosTablero[f1-1][c1]==38)) || ((palosTablero[f][c]==37 || palosTablero[f][c]==38) && (palosTablero[f1-1][c1]==35 || palosTablero[f1-1][c1]==36)))
								{
									if(barajaTablero[f1-1][c1]==barajaTablero[f][c]+1 && barajaTablero[f][c]!='J') // 1 al 8
									{
										moverCartasTablero(f1, c1, f, c);
									}

									else if(barajaTablero[f][c]=='9' && barajaTablero[f1-1][c1]=='0') //9
									{
										moverCartasTablero (f1, c1, f, c);
									}

									else if(barajaTablero[f][c]=='0' && barajaTablero[f1-1][c1]=='J') //10 == 0
									{
										moverCartasTablero (f1, c1, f, c);
									}

									else if(barajaTablero[f][c]=='J' && barajaTablero[f1-1][c1]=='Q') //J
									{
										moverCartasTablero (f1, c1, f, c);
									}

									else if(barajaTablero[f][c]=='Q' && barajaTablero[f1-1][c1]=='K') //Q
									{
										moverCartasTablero (f1, c1, f, c);
									}
								}

								if(barajaTablero[f][c]=='K' && f1==0) // K
								{
									moverCartasTablero (f1, c1, f, c);
								}
							}
							break;

						case 2:
							p("\nPosicion 'fila columna': ");
							s("%d",&f);
							s("%d",&c);

							if(barajaTablero[f+1][c]==' ')
							{
								if(barajaTablero[f][c]==49)
								{
									palos[palosTablero[f][c]-35]=barajaTablero[f][c];
									barajaTablero[f][c]=' ';
									palosTablero[f][c]=' ';
								}

								else if(barajaTablero[f][c]-1 == palos[palosTablero[f][c]-35] && barajaTablero[f][c] != 'K')
								{
									palos[palosTablero[f][c]-35]=barajaTablero[f][c];    //Si es ♥ entonces palos[0], si es ♦ entoces palos[1]...
									barajaTablero[f][c]=' ';
									palosTablero[f][c]=' ';
								}

								else if(palos[palosTablero[f][c]-35]=='9' && barajaTablero[f][c]=='0')
								{
									palos[palosTablero[f][c]-35]=barajaTablero[f][c];
									barajaTablero[f][c]=' ';
									palosTablero[f][c]=' ';
								}

								else if(palos[palosTablero[f][c]-35]=='0' && barajaTablero[f][c]=='J')
								{
									palos[palosTablero[f][c]-35]=barajaTablero[f][c];
									barajaTablero[f][c]=' ';
									palosTablero[f][c]=' ';
								}

								else if(palos[palosTablero[f][c]-35]=='J' && barajaTablero[f][c]=='Q')
								{
									palos[palosTablero[f][c]-35]=barajaTablero[f][c];
									barajaTablero[f][c]=' ';
									palosTablero[f][c]=' ';
								}

								else if(palos[palosTablero[f][c]-35]=='Q' && barajaTablero[f][c]=='K')
								{
									palos[palosTablero[f][c]-35]=barajaTablero[f][c];
									barajaTablero[f][c]=' ';
									palosTablero[f][c]=' ';
								}
							}
							break;
					}
					break;
			}
			break;

		case 2:
			p("\nPosicion 'fila columna': ");
			s("%d", &f);
			s("%d", &c);

			if(barajaTablero[f][c]==cartaPartePosterio && barajaTablero[f+1][c]==' ')
			{
				if(f==0)
				{
					barajaTablero[f][c]=barajaMezclada[24 + c];
					palosTablero[f][c]=paloMezclado[24 + c];
				}

				if(f==1)
				{
					barajaTablero[f][c]=barajaMezclada[29 + c];
					palosTablero[f][c]=paloMezclado[29 + c];
				}

				if(f==2)
				{
					barajaTablero[f][c]=barajaMezclada[33 + c];
					palosTablero[f][c]=paloMezclado[33 + c];
				}

				if(f==3)
				{
					barajaTablero[f][c]=barajaMezclada[36 + c];
					palosTablero[f][c]=paloMezclado[36 + c];
				}

				if(f==4)
				{
					barajaTablero[f][c]=barajaMezclada[38 + c];
					palosTablero[f][c]=paloMezclado[38 + c];
				}

				if(f==5)
				{
					barajaTablero[f][c]=barajaMezclada[39 + c];
					palosTablero[f][c]=paloMezclado[39 + c];
				}
			}
			break;

		case 3:
			cambiarCartaMazo();
			break;

		case 4:
			p("\nDesea guardar el juego:\n1. Si\n2. No\n");
			p("Respuesta: ");
			s("%d", &opcion);

			switch(opcion)
			{
				case 1:
					getch();
					break;

				case 2:
					getch();
					break;
			}
			break;
	}
}

void juego ()
{
	do
	{
		system("clear");
		tableroJuego();
		menuJuego();
	}
	while (palos[0]!='K' || palos[1]!='K' || palos[2]!='K' || palos[3]!='K');
}

unsigned char cambiarCartaMazo()
{

	if(posCartaMonton!=cantidadCartasMonton)
	{
		posCartaMonton++;
	}
	else {posCartaMonton=0;}

	return posCartaMonton;

}

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

void moverCartasTablero (unsigned char f1, unsigned char c1, unsigned char f, unsigned char c)
{
	unsigned char n=1;
	barajaTablero[f1][c1]=barajaTablero[f][c];
	barajaTablero[f][c]=' ';
	palosTablero[f1][c1]=palosTablero[f][c];
	palosTablero[f][c]=' ';
	do
	{
		barajaTablero[f1+n][c1]=barajaTablero[f+n][c];
		barajaTablero[f+n][c]=' ';
		palosTablero[f1+n][c1]=palosTablero[f+n][c];
		palosTablero[f+n][c]=' ';
		n++;
	}
	while(barajaTablero[f+n][c]!=' ');
}

void gameOver ()
{
	//unsigned int notas[8]={294,247,330,330,330,220,392};
	//unsigned int tiempo[8]={294,247,330,330,330,220,392};
	unsigned char conta=0;
	unsigned char i;

	do
	{
		for(i = 3; i < 7; i++)
		{
			p("\n\n");
			p("     %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", i, i,i, i,i, i,i, i,i, i,i, i,i, i,i, i);
			p("     %c  Has ganado  %c\n", i, i);
			p("     %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n\n", i, i,i, i,i, i,i, i,i, i,i, i,i, i,i, i);

			if(conta<7)
			{
				//Beep (notas[conta],tiempo[conta]);
			}
			conta++;
		}
	}
	while(conta<7);
}

char getch()
{
       char buf=0;
       struct termios old={0};
       fflush(stdout);
       if(tcgetattr(0, &old)<0)
           perror("tcsetattr()");
       old.c_lflag&=~ICANON;
       old.c_lflag&=~ECHO;
       old.c_cc[VMIN]=1;
       old.c_cc[VTIME]=0;
       if(tcsetattr(0, TCSANOW, &old)<0)
           perror("tcsetattr ICANON");
       if(read(0,&buf,1)<0)
           perror("read()");
       old.c_lflag|=ICANON;
       old.c_lflag|=ECHO;
       if(tcsetattr(0, TCSADRAIN, &old)<0)
           perror ("tcsetattr ~ICANON");
       printf("%c\n",buf);
       return buf;
    }
