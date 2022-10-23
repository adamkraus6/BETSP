#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <math.h>
#include <limits>

using namespace std;

struct Coord {
	double x,y;
};

vector<Coord> coords;
int n = 0;

void getCoords(string fileName);
double dist(int i, int j);

int main(int argc, char** argv)
{
	if(argc != 2)
	{
		cout << "Please add input file argument" << endl;
		return -1;
	}

	getCoords(argv[1]);
	
	n = coords.size()-1;

	vector<double> M; // tour lengths
	vector<double> K; // key points
	M.resize(n+1);
	K.resize(n+1);

	M[1] = 0;
	M[2] = 2*dist(1,2);
	K[2] = 1;

	// calculate optimal tour length and key points
	for(int i = 3; i <= n; i++)
	{
		M[i] = numeric_limits<double>::max();
		double link = 0;
		for(int k = i-2; k >= 1; k--)
		{
			link += dist(k+1, k+2);
			double locallen = link + dist(k, i) + M[k+1] - dist(k, k+1);
			if(locallen < M[i])
			{
				M[i] = locallen;
				K[i] = k;
			}
		}
	}

	double k;
	int temp_n = n;
	vector<Coord> segments;
	Coord s;
	vector<int> order;
	vector<bool> used;
	used.resize(n);

	// get segments from key points K
	s.x = n-2;
	s.y = n-1;
	segments.push_back(s);
	do {
		k = K[n];
		s.x = k-1;
		s.y = n-1;
		segments.push_back(s);
		for(int i = k+1; i <= n-2; i++)
		{
			s.x = i-1;
			s.y = i;
			segments.push_back(s);
		}
		n = k+1;
	} while(k != 1);

	n = temp_n;

	int p = 0;

	// sort segments by ascending first point
	for(int i = 0; i < n-1; i++)
	{
		for(int j = 0; j < n-i-1; j++)
		{
			if(segments[j].x > segments[j+1].x)
			{
				Coord temp = segments[j];
				segments[j] = segments[j+1];
				segments[j+1] = temp;
			}
		}
	}

	// get one half of tour from segments
	for(int i = 0; i < n; i++)
	{
		if(p == segments[i].x)
		{
			p = segments[i].y;
			used[i] = true;
			order.push_back(p);
		}
	}

	// right most point
	p = n-1;

	// get other half of tour
	for(int i = n-1; i >= 0; i--)
	{
		if(p == segments[i].y && !used[i])
		{
			p = segments[i].x;
			used[i] = true;
			order.push_back(p);
		}
	}

	// missing 0 point
	order.push_back(0);

	string inFileName = string(argv[1]);
    string outFileName = string(inFileName.erase(inFileName.size() - 3)) + ".out";
    ofstream fout(outFileName);

	// print tour order
	for(int i = n-1; i > 0; i--)
	{
		fout << order[i] << ' ';
	}
	fout << order[0] << endl;

	fout << M[n] << endl;

	return 0;
}

double dist(int i, int j)
{
	Coord a = coords[i], b = coords[j];

	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

void getCoords(string fileName)
{
    ifstream fin(fileName);

    int n;
    fin >> n;

	Coord coord;

	// indexing fix
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