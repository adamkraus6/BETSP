#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;

struct Coord
{
    double x, y;
};

bool operator<(Coord lhs, Coord rhs)
{
    return lhs.x < rhs.x ? true : false;
}

vector<Coord> getCoords(string fileName);
bool checkBitonic(vector<Coord> path);

int main(int argc, char **argv)
{
    cout << "Brute force solution for bitonic traveling salesman problem." << endl;

    if (argc != 2)
    {
        cout << "Please provide an input file!" << endl;
        exit(-1);
    }

    vector<Coord> coords = getCoords(argv[1]);

    while (next_permutation(coords.begin(), coords.end()))
    {
        bool bitonic = checkBitonic(coords);
        // cout << bitonic << endl;

        if (bitonic)
        {
            for (auto coord : coords)
            {
                cout << coord.x << " " << coord.y << endl;
            }
            cout << endl;
        }
    }
}

vector<Coord> getCoords(string fileName)
{
    vector<Coord> coords;

    ifstream fin;
    fin.open(fileName, ios::in);

    int num;
    fin >> num;

    for (int i = 0; i < num; i++)
    {
        Coord coord;
        fin >> coord.x >> coord.y;
        coords.push_back(coord);
    }

    fin.close();

    return coords;
}

bool checkBitonic(vector<Coord> path)
{
    double maxX = 0;
    double minX = INT32_MAX;

    for (auto coord : path)
    {
        maxX = max(coord.x, maxX);
        minX = min(coord.x, minX);
    }

    if (path[0].x != minX)
    {
        return false;
    }

    double prevX = path[0].x;
    bool increasing = true;
    bool decreasing = false;

    for (auto coord : path)
    {
        if (coord.x == maxX)
        {
            // change from increasing to decreasing
            increasing = false;
            decreasing = true;
        }
        else if ((coord.x > prevX && decreasing) || (coord.x < prevX && increasing))
        {
            return false;
        }

        prevX = coord.x;
    }

    return true;
}

// read in points from the input file
// generate every permutation of paths to travel
// check if path is bitonic (every x is increasing then decreasing)
// if it is, calculate the length of the path
// if the lenght is less than the current shortest path, make that path the winner
// yay all done

// will be ugly and slow but will work!