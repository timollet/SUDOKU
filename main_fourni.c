#include <stdlib.h>
#include <stdio.h>
#include <math.h>


/* --Le--nommage--de--certaines--valeurs------------------------------------- */

#define VALUE 0

#define COUNT ( Size + 1 )

/* --Les--constantes--de--compilation---------------------------------------- */

#define Max_size_bloc 5

#define Max_size ( Max_size_bloc * Max_size_bloc )

#define Size ( Size_bloc * Size_bloc )

/* --Les--variables--globales------------------------------------------------ */

int Size_bloc ;

int Sudoku[ Max_size + 1 ][ Max_size + 1 ][ Max_size + 2 ] ;

int * Lines[ Max_size + 1 ][ Max_size + 1 ] ;

int * Columns[ Max_size + 1 ][ Max_size + 1 ] ;

int * Blocs[ Max_size + 1 ][ Max_size + 1 ] ;

int Optimise_one , Optimise_two ;

char Transcode[ 16 + 1 ]
= { ' ' , '1' , '2' , '3' , '4' , '5' , '6' , '7' , '8' , '9' ,
    'A' , 'B' , 'C' , 'D' , 'E' , 'F' , 'G' } ;

char Transcode_ext[ 25 + 1 ]
= { ' ' , 'A' , 'B' , 'C' , 'D' , 'E' , 'F' , 'G' , 'H' , 'I' , 'J' , 'K' , 'L' ,
    'M' , 'N' , 'O' , 'P' , 'Q' , 'R' , 'S' , 'T' , 'U' , 'V' , 'W' , 'X' , 'Y' } ;

/* --Quelques--exemples--pour--le--test-------------------------------------- */

#include "grids.c"

/* --Les--prototypes--des--fonctions--fournies------------------------------- */

void setup_Lines_Columns_Blocs ( void ) ;
void fill_squares_line ( int * squares[ ] , int li ) ;
void fill_squares_column ( int * squares[ ] , int co ) ;
void fill_squares_bloc ( int * squares[ ] , int base_li , int base_co ) ;

void optimise ( void ) ;

int fill_and_count_squares_Sudoku ( int value_list[ ] ) ;
int main ( void ) ;

/* --Les--prototypes--des--fonctions--a--fournir----------------------------- */

void print_Sudoku ( void ) ;

void fill_possibilities ( void ) ;

int optimise_possibilities ( int * squares[ ] ) ;

int back_track ( int squares_filled ) ;

void possibilite_li_co_blocs(int * TAB[],int li,int co);

/* --Les--fonctions--fournies------------------------------------------------ */

void setup_Lines_Columns_Blocs ( void )
     {int i ;
      for ( i = 1 ; i <= Size ; i++ )
          {fill_squares_line( Lines[ i ] , i ) ;
           fill_squares_column( Columns[ i ] , i ) ;
           fill_squares_bloc( Blocs[ i ] ,
                              1 + ( i - 1 ) / Size_bloc * Size_bloc ,
                              1 + ( i - 1 ) % Size_bloc * Size_bloc ) ;
          }
     }

void fill_squares_line ( int * squares[ ] , int li )
     {int co , index = 1 ;
      for ( co = 1 ; co <= Size ; co++ )
          squares[ index++ ] = Sudoku[ li ][ co ] ;
     }

void fill_squares_column ( int * squares[ ] , int co )
     {int li , index = 1 ;
      for ( li = 1 ; li <= Size ; li++ )
          squares[ index++ ] = Sudoku[ li ][ co ] ;
     }

void fill_squares_bloc ( int * squares[ ] , int base_li , int base_co )
     {int offset_li , offset_co , index = 1 ;
      for ( offset_li = 0 ; offset_li < Size_bloc ; offset_li++ )
          for ( offset_co = 0 ; offset_co < Size_bloc ; offset_co++ )
              squares[ index++ ] = Sudoku[ base_li + offset_li ][ base_co + offset_co ] ;
     }

void optimise ( void )
     {int i , iterate ;
      do {iterate = 0 ;
          for ( i = 1 ; i <= Size ; i++ )
              {iterate = optimise_possibilities ( Lines[ i ] ) ;
               iterate = optimise_possibilities ( Columns[ i ] ) || iterate ;
               iterate = optimise_possibilities ( Blocs[ i ] ) || iterate ;
              }
         }
      while ( iterate ) ;
     }

int fill_and_count_squares_Sudoku ( int value_list[ ] )
    {int li , co , value , index = 0 , sum = 0 ;
     for ( li = 1 ; li <= Size ; li++ )
         for ( co = 1 ; co <= Size ; co++ )
             {value = value_list[ index ++ ] ;
              Sudoku[ li ][ co ][ VALUE ] = value ;
              if ( value )
                 sum++ ;
             }
     return( sum ) ;
    }

int main ( void )
{
     int solution_found , number_squares ;
     int li,co,i;

     Size_bloc = 2 ;
     setup_Lines_Columns_Blocs( ) ;
     Optimise_one = 1 ;
     Optimise_two = 1 ;
     number_squares = fill_and_count_squares_Sudoku( Grid_four ) ;
     print_Sudoku( ) ;
     fill_possibilities();
     //boucles pour parcourir le sudoku nous affichons pour chaque case le vecteur de bits des possibilité
     //le nombre de possibilité ( count) et la valeur ( 0 si il y en a pas )
     for(li=1;li<=Size;li++)
        {
            for(co=1;co<=Size;co++)
            {
                for(i=1;i<=Size;i++)
                {
                    (void)printf( " %d  ",Sudoku[li][co][i] ) ;

                }
                (void)printf( "\n VALUE : %d \n",Sudoku[li][co][VALUE] ) ;
                (void)printf( " COUNT :%d \n\n",Sudoku[li][co][COUNT] ) ;
            }
        }
     solution_found = back_track( number_squares ) ;
     if ( solution_found )
        {(void)printf( "\nNous avons trouve la solution :\n\n" ) ;
         print_Sudoku( ) ;
        }
     else
        (void)printf( "\nNous n'avons pas trouve de solution.\n" ) ;
     (void)printf( "Bye !" ) ;
        printf("\n");





     return( 0 ) ;
    }

/* --Les--autres--prototypes------------------------------------------------- */

/* Ce sont les proptotypes des autres fonctions que vous introduisez. *
/* --La--fonction--d--impression--------------------------------------------- */

void print_Sudoku ( void )
     {
		 int m,i,j,k;
		 k=1;
		 j=0;
		 while(k<=Size)
		 {
		     if (((k-1)%Size_bloc))
             {
                 for(i=0;i<Size;i=i+1)
                {
				printf("------");
                }
             }
             else
             {
                 for(i=0;i<Size;i=i+1)
                {
				printf("******");
                }
             }

			printf("\n");
	for(i=0;i<Size;i=i+1)
			{

			    if((i+1)%Size_bloc)
			    {
                    if (i==0)
                    {
                        printf("*    |");
                    }
                    else
                    {
                        printf("     |");
                    }
			    }
                else
                {

                    if (i==0)
                    {
                        printf("*    *");
                    }
                    else
                    {
                        printf("     *");
                    }
                }
			}
			printf("\n");
			m=0;
			for(j;j<k*Size;j=j+1)
			{
			    if((j+1)%Size_bloc)
                {
                    if(m==0)
                {
                  if(Grid_four[j]<10)
                    {
                        printf("* %d  |",Grid_four[j]);
                    }
                    else
                    {
                        printf("* %d |",Grid_four[j]);
                    }
                    m=m+1;
                }
                else
                {
                    if(Grid_four[j]<10)
                    {
                        printf("  %d  |",Grid_four[j]);
                    }
                    else
                    {
                        printf("  %d |",Grid_four[j]);
                    }
                }
                }
                else
                {
                    if(m==0)
                {
                  if(Grid_four[j]<10)
                    {
                        printf("* %d  *",Grid_four[j]);
                    }
                    else
                    {
                        printf("* %d *",Grid_four[j]);
                    }
                    m=m+1;
                }
                else
                {
                    if(Grid_four[j]<10)
                    {
                        printf("  %d  *",Grid_four[j]);
                    }
                    else
                    {
                        printf("  %d *",Grid_four[j]);
                    }
                }
                }

			}
			printf("\n");
			for(i=0;i<Size;i=i+1)
			{

			    if((i+1)%Size_bloc)
			    {
                    if (i==0)
                    {
                        printf("*    |");
                    }
                    else
                    {
                        printf("     |");
                    }
			    }
                else
                {

                    if (i==0)
                    {
                        printf("*    *");
                    }
                    else
                    {
                        printf("     *");
                    }
                }
			}
			printf("\n");
			k=k+1;
		 }
		 for(i=0;i<Size;i=i+1)
		{
			printf("******");
		}
     }

/* Les fonctions auxiliaires de print_Sudoku */

/* --Le--raisonnement--au--niveau--zero-------------------------------------- */
void fill_possibilities ( void )
     {
        int li,co,i,bl;
        for(li=1;li<=Size;li++)
        {
            for(co=1;co<=Size;co++)
            {
                if (Sudoku[li][co][VALUE]==0)
                {
                    //initialiser le vecteur de bits des valeurs possibles à 1 que si y a une valeur a changer!!
                           for(i=1;i<=Size;i++)
                            {
                                Sudoku[li][co][i]=1;
                            }
                    //initialiser le counter a Size
                    Sudoku[li][co][COUNT]=Size;
                    possibilite_li_co_blocs(Lines[li],li,co);
                    possibilite_li_co_blocs(Columns[co],li,co);
                    bl=numbloc(li,co);
                    possibilite_li_co_blocs(Blocs[bl],li,co);
                }
            }
        }
     }


/* Les fonctions auxiliaires de fill_possibilities */

//Recherche des possibilité dans un tableau ( Lines, Columns ou Blocs)
void possibilite_li_co_blocs(int * TAB[],int li,int co)
{
        int x,j;
        //Parcours du tableau
        for(j=1;j<=Size;j++)
            {
                if(TAB[j][VALUE]!=0)
                {
                    x=TAB[j][VALUE];
                    //decrementation du count si la valeur devient impossible et 0 pour la valeur sur le vecteur de bits des possibilites
                    if(Sudoku[li][co][x]==1)
                    {
                        Sudoku[li][co][COUNT]=Sudoku[li][co][COUNT]-1;
                        Sudoku[li][co][x]=0;
                    }
                }
            }
}



//Fonction qui calcule le numéro du bloc e fonction du numero de la ligne et de la colonne

int numbloc(li,co)
{
    int ls,cs,nb;
    ls=li / Size_bloc;
    if (li%Size_bloc != 0)
    {
        ls=ls+1;
    }

    cs=co / Size_bloc;
    if (co%Size_bloc!=0)
    {
        cs=cs+1;
    }

    nb=Size_bloc*(ls-1)+(cs-1)+1;
    return nb;
}

/* Les fonctions auxiliaires de fill_possibilities */

/* --Les--optimisations------------------------------------------------------ */

int optimise_possibilities ( int * squares[ ] )
    {
     /* ... */
    }

/* --Une--valeur--proposee--une--seule--fois--------------------------------- */

/* Les fonctions correspondant a la premiere optimisation */

/* --Deux--cases--a--possibilites--doubles----------------------------------- */

/* Les fonctions correspondant a la seconde optimisation */

/* --Le--back--track--------------------------------------------------------- */

int back_track ( int squares_filled )
    {
        int i,j;
        int MinPossible;
        int res;
        int poss;
        int fin;

		if (squares_filled == Size*Size)
		{
			return(1);
		}
		else
		{
			fill_possibilities();
			MinPossible = CompteLeMoinsDePossibilité(&i,&j);
			if(MinPossible == 0)
			{
				return(0);
			}
			else
			{
				poss=1;
				fin=0;
				while((poss<Size+1)||(fin==0))
				{
					if(Sudoku[i][j][poss]==1)
					{
						Sudoku[i][j][VALUE]=poss;
						fin=1;
					}
                    res=back_track(squares_filled + 1);
                    if (res==1)
                    {
                        return(1);
                    }
                    else
                    {
                        Sudoku[i][j][VALUE]=0;
                    }
                    poss=poss+1;
                }
			return(0);
            }
        }
    }

/* Les fonctions auxiliaires de back_track */

int CompteLeMoinsDePossibilité(int *li, int *co)
{
	int i,j;
	int nbrPossible = Size;
	for(i=1;i<Size+1;i++)
	{
		for(j=1;j<Size+1;j++)
		{
			if((Sudoku[i][j][VALUE]!=0)&&(Sudoku[i][j][COUNT]<nbrPossible))
			{
				nbrPossible=Sudoku[i][j][COUNT];
				*li=i;
				*co=j;
			}
		}
	}
	return(nbrPossible);
}

/* -------------------------------------------------------------------------- */
