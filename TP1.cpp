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
			}
			elems = temp;
			taille++;
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
		
		void afficher()
		{
			cout << "pile :" << endl;
			for(int i = 0; i < taille; i++)
				cout << elems[i] << " ";
			cout << "\n" << endl;
		}
};



/* remplit le sommet destination ainsi que la matrice des capacités,
on suppose que le fichier donné à une matrice valide */
void remplissage(int &t, int **&c)
{
	cout << "Saisissez le nom de fichier contenant une matrice " << endl ;
	string nom;
	cin >> nom ;

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
	Pile P = Pile();
	bool stop = false;
	for(int i = 0; i < t+1; i++)
	{
		visites[i] = false; ch[i] = -1;
	}
	P.empiler(s);
	while(P.nonVide() && (!stop))
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
					if(((c[i][j] > 0) && (c[i][j] > f[i][j])) || ((c[j][i] > 0) && (f[j][i] > 0)))
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
	int temp;
	int i = ch[t];
	int j = t;
	temp = c[i][j];
	while(true)
	{
		if(i == s) 
		{
			if(temp > (c[i][j]-f[i][j]))
			{
				temp = c[i][j]-f[i][j];
			}
			break;
		}
		if(temp > (c[i][j]-f[i][j]))
		{
			temp = c[i][j]-f[i][j];
		}
		j = i;
		i = ch[i];
	}
	return temp;
}

void flotmax(int **c, int **&f, int s, int t)
{
	// on initialise la matrice des flux
	f = new int * [t+1];
	for(int i = 0; i < t+1; i++)
		f[i] = new int[t+1];
	for(int i = 0; i < t+1; i++)
	{
		for(int j = 0; j < t+1; j++)
		{
			f[i][j] = 0;
		}
	}
	
	// tableau de la liste des arcs de la chaine augmentante
	int *ch;
	ch = new int[t+1];
	chaineaugmentante(ch,c,f,s,t);
	while(ch[t] != -1)
	{
		int augm = increment(ch,c,f,s,t);
		int i = ch[t];
		int j = t;
		while(true)
		{
			if(i == s) 
			{
				f[i][j] += augm;
				break;
			}
			f[i][j] += augm;
			j = i;
			i = ch[i];
		}
		chaineaugmentante(ch,c,f,s,t);
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
	
	// calcul du flot max
	flotmax(c,f,1,3);
	
	// affichage du flot max
	for(int i = 0; i < t+1; i++)
	{
		for(int j = 0; j < t+1; j++)
		{
			cout << f[i][j] << " " ;
		}
		cout << endl ;
	}
	return 0;
}
