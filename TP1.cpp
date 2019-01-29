#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <math.h>

using namespace std;

/********** PILE ***********/
class Pile
{
	private :
		int * elems;
		int taille;

	public :
		Pile() { elems = NULL, taille = 0; }

		~Pile() {
			if(taille > 0)
			{
				delete[] elems;
				taille = 0;
			}
		}

		bool nonVide()
		{
			if(taille > 0) return true;
			else false;
		}

		void empiler(const int & e)
		{
			int *temp = new int[taille+1];
			for(int i = 0; i < taille; i++)
				temp[i] = elems[i];
			temp[taille] = e;
			if(taille > 0)
			{
				delete[] elems;
				taille = 0;
			}
			elems = temp;
			taille ++;
		}

		int depiler()
		{
			int * temp = new int[taille-1];
			int rtn = elems[--taille];
			for(int i = 0; i < taille; i++)
				temp[i] = elems[i];
			delete[] elems;
			elems = temp;
			return rtn;
		}
};



/* remplit le sommet destination ainsi que la matrice des capacités,
on suppose que le fichier donné à une matrice valide */
void remplissage(int &t, int **&c)
{
	//cout << "Saisissez le nom de fichier contenant une matrice " << endl ;
	string nom = "matrice1";
	//cin >> nom ;

	ifstream fichier(nom);
	if(fichier.is_open())
	{
		int taille = 0;
		vector<string> lignesFichier ;
		string ligne;
		// on cherche la taille de la matrice et on stocke chaque ligne
		while(getline(fichier, ligne))
		{
			taille += 1;
			lignesFichier.push_back(ligne);
		}
		// attribution de la mémoire pour la matrice
		c = new int * [taille];
		for(int i = 0; i < taille; i++)
    		c[i] = new int[taille];

		// on remplit la matrice
		for (int i = 0 ; i < lignesFichier.size(); i++ )
		{
			int j = 0;
			istringstream iss(lignesFichier[i]);
			string buffer;
			// on peut changer le séparateur suivant les besoins
			while(getline(iss, buffer, ' ')) {
			    c[i][j] = stoi(buffer);
					j++;
			}
		}
		fichier.close();
		t = taille-1; // on commence de 0 donc on enlève 1
	}
	else
	{
		cerr << "ERREUR le fichier " << nom << " n'existe pas" << endl;
	}
}


// remplit un tableau avec la liste des sommets constituants une chaine augmentante
void chaineaugmentante(int *&ch, int **c, int **f, int s, int t)
{
  bool *visites = new bool[t+1];
	ch = new int[t+1];
	Pile P = Pile();
	bool stop = false;
	for(int i = 0; i < t+1; i++)
	{
		visites[i] = false; ch[i] = -1;
	}
	P.empiler(s);
	while(P.nonVide() && !stop)
	{
		int i = P.depiler();
		if(i == t)
		{
			stop = true;
		}
		else if(visites[i] == false)
		{
			visites[i] = true;
			for(int j = 0; j < t+1; j++)
			{
				if(visites[j] == false)
				{
					if(((c[i][j] > 0) && (c[i][j] > f[i][j])) || ((c[j][i] > 0) && (f[i][j] > 0)))
					{
						P.empiler(j); ch[j] = i;
					}
				}
			}
		}
	}
}

int increment(int *ch, int **c, int **f, int s, int t)
{
	int i = t;
	while(ch[i] != s)
	{
		i = ch[i];
	}
}

int main()
{
  // matrice des capacités :
  int **c;
  // matrice des flots
  int **f;
  // sommet source toujours le premier sommet donc 0
  int s = 0;
  // sommet destination
  int t;

	// on remplit la matrice des capacités et le sommet destination
	remplissage(t,c);
	// on initialise la matrice des flux
	int taille = (int) sqrt(t+1);
	f = new int * [taille];
	for(int i = 0; i < taille; i++)
			f[i] = new int[taille];
	for(int i = 0; i < taille; i++)
	{
		for(int j = 0; j < taille; j++)
		{
			f[i][j] = 0;
		}
	}

  // tableau d'éléments
  int *ch;
  chaineaugmentante(ch,c,f,s,t);

  return 0;
}
