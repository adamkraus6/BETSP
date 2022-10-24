#include <iostream>
#include <algorithm>
#include <fstream>
#include <cmath>
#include <vector>

using namespace std;

struct Coord
{
    double x, y;
};

bool operator<(Coord lhs, Coord rhs)
{
    return lhs.x < rhs.x ? true : false;
}

bool operator==(Coord lhs, Coord rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y ? true : false;
}

vector<Coord> getCoords(string fileName);
bool checkBitonic(vector<Coord> path);
double findPathLength(vector<Coord> path);
double findPointDistance(Coord p1, Coord p2);

int main(int argc, char **argv)
{
    cout << "Brute force solution for bitonic traveling salesman problem." << endl;

    if (argc != 2)
    {
        cout << "Please provide an input file!" << endl;
        exit(-1);
    }

    vector<Coord> ogCoords = getCoords(argv[1]);
    vector<Coord> coords = ogCoords;
    vector<Coord> shortestPathOrder;
    double shortestPath = INT16_MAX;
    int permsDone = 0;

    while (next_permutation(coords.begin(), coords.end()))
    {
        bool bitonic = checkBitonic(coords);

        if (bitonic)
        {
            double length = findPathLength(coords);
            if (length < shortestPath)
            {
                shortestPath = length;
                shortestPathOrder = coords;
            }
        }
    }

    string inFileName = string(argv[1]);
    string outFileName = string(inFileName.erase(inFileName.size() - 3)) + ".out";
    ofstream outFile(outFileName);

    for (auto coord : shortestPathOrder)
    {
        auto pos = find(ogCoords.begin(), ogCoords.end(), coord);
        int index = pos - ogCoords.begin();
        cout << index << " ";
        outFile << index << "  ";
    }

    cout << endl
         << "Shortest path is " << shortestPath << endl;
    outFile << endl
            << shortestPath << endl;

    outFile.close();
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

double findPathLength(vector<Coord> path)
{
    Coord minCoord = path[0];
    for (auto coord : path)
    {
        minCoord = min(minCoord, coord);
    }
    path.push_back(minCoord); // add the min spot so that the path is complete!

    Coord prevPoint = path[0];
    double length = 0;

    for (int i = 1; i < path.size(); i++)
    {
        length = length + findPointDistance(prevPoint, path[i]);
        prevPoint = path[i];
    }

    return length;
}

double findPointDistance(Coord p1, Coord p2)
{
    return sqrt((pow(p2.x - p1.x, 2) + (pow(p2.y - p1.y, 2))));
}

// read in points from the input file
// generate every permutation of paths to travel
// check if path is bitonic (every x is increasing then decreasing)
// if it is, calculate the length of the path
// if the lenght is less than the current shortest path, make that path the winner
// yay all done

// will be ugly and slow but will work!