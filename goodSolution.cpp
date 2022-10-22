// geeks for geeks baby
// https://www.geeksforgeeks.org/bitonic-traveling-salesman-problem/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <math.h>

using namespace std;

struct Coord {
	double x,y;
};

vector<Coord> coords;
double dp[200][200];

void getCoords(string fileName);
double dist(int i, int j);
double betspTour(int i, int j);

int main(int argc, char** argv)
{
	if(argc != 2)
	{
		cout << "Please add input file argument" << endl;
		return -1;
	}

	getCoords(argv[1]);
	
	int n = coords.size()-1;

	for(int j = 1; j < n-1; j++)
	{
		dp[n-1][j] = dist(n-1, n) + dist(j, n);
	}

	cout << betspTour(1, 1) << endl;

	return 0;
}

double betspTour(int i, int j)
{
	if(dp[i][j] > 0)
	{
		return dp[i][j];
	}

	double opt1 = betspTour(i+1, j) + dist(i, i+1);
	double opt2 = betspTour(i+1, i) + dist(j, i+1);

	if(opt1 < opt2)
	{
		dp[i][j] = opt1;
	}
	else
	{
		dp[i][j] = opt2;
	}
	
	return dp[i][j];
}

double dist(int i, int j)
{
	Coord a = coords[i], b = coords[j];

	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

void getCoords(string fileName)
{
    fstream fin;
    fin.open(fileName, ios::in);

    int n;
    fin >> n;

	Coord coord;
	coord.x = 0;
	coord.y = 0;
	coords.push_back(coord);

    for(int i = 0; i < n; i++)
    {
        fin >> coord.x >> coord.y;
		coords.push_back(coord);
    }

    fin.close();
}