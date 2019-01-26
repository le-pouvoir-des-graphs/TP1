#include "Matrix.h"

Matrix::Matrix(int x , int y)
{
	sizeX = x;
	sizeY = y;
	matrix = new int * [x];
	for(int i = 0; i < x; ++i)
    	matrix[i] = new int[y];
}

Matrix::Matrix(string filePath)
{
	int lineNumber = 0 ;
	int columnNumber = 0 ;

	string line;

	vector <string> strFile ;

	ifstream file(filePath, ios::in);

	if ( file )
	{

		while ( getline(file, line) )
		{
			lineNumber+=1;
			strFile.push_back(line);
		}
		for ( int i = 0 ; i < line.size() ; i ++ )
		{
			if ( line[i] != ' ' && line[i] != '\n')
			{
				columnNumber += 1;
			}
		}

		sizeX = lineNumber ;
		sizeY = columnNumber ; 

		matrix = new int * [columnNumber];
		for(int i = 0; i < columnNumber; ++i)
    		matrix[i] = new int[lineNumber];

		int index = 0 ;
		for ( int i = 0 ; i < lineNumber ; i ++ )
		{
			for ( int j = 0 ; index < columnNumber ; j++  )
			{
				if ( strFile[i][j] != ' ' && strFile[i][j] != '\n' )
				{
					int value = stoi(&strFile[i][j]);
					matrix[i][index]=value;
					// cout << value ;
					index += 1;
				}
			}
			// cout << endl ;
			index = 0 ;
		}
		file.close();
	}
	else
		cerr << " Fichier introuvable " << endl ;
}


void Matrix::initMatrix(int x)
{
	for(int i = 0; i < sizeX; ++i)
	{
		for(int j = 0; j < sizeY; ++j)
		{
			matrix[i][j] = x ; 
		}
	}
}

void Matrix::setMatrixXY(int x , int y , int value)
{
	matrix[x][y] = value ;
}

void Matrix::displayMatrix()
{
	cout << " Matrix Displayer :\n  - dim " << sizeX << "*" << sizeY << endl ;
	for(int i = 0; i < sizeX; ++i)
	{
		for(int j = 0; j < sizeY; ++j)
		{
			cout << " " << matrix[i][j] ; 
		}
		cout << endl;
	}
}

int Matrix::getSizeX()
{
	return sizeX ;
}

int Matrix::getSizeY()
{
	return sizeY ;
}


