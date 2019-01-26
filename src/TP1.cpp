#include <iostream>
#include <stdio.h>
#include "Matrix.h"
using namespace std;


string saisie()
{
	cout << " Saisissez un nom de fichiere contenant une matrice " << endl ;
	string line ;
	cin >> line ;
	return line ;
}


// renvoie un tableau avec la liste des sommets constituants une chaine augmentante
int* chaineaugmentante(int *ch, int **c, int **f, int s, int t)
{
  return ch;
}

int main()
{

  /*

  //matrice des capacités
  int **c;
  // matrice des flots
  int **f;
  // sommet source
  int s;
  // sommet destination
  int t;
  // tableau d'éléments
  int *ch = new int[t+1];
  chaineaugmentante(ch,c,f,s,t);

  */

  Matrix * c = new Matrix(10,10);
  c->initMatrix(0);
  c->displayMatrix();

  Matrix * m = new Matrix(saisie());
  m->displayMatrix();

  cout << "Fin du main" << endl ;
  return 0;
}
