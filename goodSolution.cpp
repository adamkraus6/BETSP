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

void getCoords(string fileName);
double dist(int i, int j);
void outputDP(double dp[200][200], int n);
double betspTour(double dp[200][200], int i, int j);

int main(int argc, char** argv)
{
	double dp[200][200];

    if(argc != 2)
	{
		cout << "Please add input file argument" << endl;
		return -1;
	}

	int n = coords.size();

	for(int j = 1; j < n - 1; j++)
	{
		dp[n-1][j] = dist(n-1, n) + dist(j, n);
	}

	outputDP(dp, n);

	return 0;
}

double betspTour(double dp[200][200], int i, int j)
{
	if(dp[i][j] > 0)
	{
		return dp[i][j];
	}

	dp[i][j] = min(betspTour(dp, i+1, j) + dist(i, i+1), betspTour(dp, i+1, i));

	return dp[i][j];
}

double dist(int i, int j)
{
	Coord a = coords[i], b = coords[j];

	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

void outputDP(double dp[200][200], int n)
{
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			cout << setw(8) << setprecision(5) << dp[i][j];
		}
		cout << endl;
	}
}

void getCoords(string fileName)
{
    vector<Coord> coords;
    
    fstream fin;
    fin.open(fileName, ios::in);

    int n;
    fin >> n;

    for(int i = 0; i < n; i++)
    {
        Coord coord;
        fin >> coord.x >> coord.y;
		coords.push_back(coord);
    }

    fin.close();
}