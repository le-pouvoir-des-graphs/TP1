#include <iostream>
#include <fstream>
#include <string> 
#include <vector>
using namespace std;

class Matrix
{
	private : 
		int ** matrix ;
		int sizeX;
		int sizeY;

	public : 
		Matrix(int x,int y);
		Matrix(string filePath);
		void initMatrix(int x);
		int ** getMatrix();
		void setMatrixXY(int x ,int y , int value);
		void displayMatrix();
		int getSizeX();
		int getSizeY();
		void loadMatrix(string filePath);
};