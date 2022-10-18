// geeks for geeks baby
// https://www.geeksforgeeks.org/bitonic-traveling-salesman-problem/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

struct Coord {
	double x,y;
};

vector<Coord> getCoords(string fileName);

int main(int argc, char** argv)
{
    if(argc != 2)
	{
		cout << "BAD" << endl;
	}

	vector<Coord> coords = getCoords(argv[1]);

	
}

vector<Coord> getCoords(string fileName)
{
    vector<Coord> coords;
    
    fstream fin;
    fin.open(fileName, ios::in);

    int num;
    fin >> num;

    for(int i = 0; i < num; i++)
    {
        Coord coord;
        fin >> coord.x >> coord.y;
		coords.push_back(coord);
    }

    fin.close();

    return coords;
}