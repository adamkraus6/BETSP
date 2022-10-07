///////////////////////////////////////////////////////////////////
//      Check output from Traveling Salesman Program             //
///////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <cstring>
using namespace std;

const int max_city = 200;

typedef  float dist_type;
typedef  int tour [ max_city ];
typedef  dist_type dist_matrix [ max_city ] [ max_city ];

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

dist_type tour_length (tour  t, dist_matrix d, int n)
  {
  int       i;
  dist_type ans;
   
  ans = d[t[0]][t[n - 1]];
  for (i = 0; i < n - 1; i++)
    ans += d[t[i]][t[i+1]];
  return  ans;
  }; // tour_length 

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

void  read_file(char file_name[], dist_matrix d, int &n)
  {
  float      d1;
  float      d2;
  float      x[max_city];
  float      y[max_city];
  int        i;
  ifstream   infile;
  int        j;

  infile . open(file_name);
  if (infile.fail())
    {
    cout << "Error opening file '" << file_name << "'" << endl;
    exit(1);
    }
  infile >>  n;

  // Read entire list of points and compute distance matrix

  for (i = 0; i < n; i++)
    infile >> x[i] >> y[i];
  for (i = 0; i < n; i++)
    {
    for (j = 0; j < n; j++)
      {
      d1 = x[i] - x[j];
      d2 = y[i] - y[j];
      d[i][j] = sqrt(d1*d1 + d2*d2);
      }
    }

  } // read_file 

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
  {
  dist_type     best_dist;
  char          in_file_name[100];
  ifstream      tour_file;
  char          tour_file_name[100];
  tour          best_tour;
  dist_type     current_dist;
  tour          current_tour;
  dist_matrix   d;
  int           i;
  int           n;
  dist_type     file_dist;

  strcpy(in_file_name, argv[1]);
  strcat(in_file_name, ".in");
  read_file(in_file_name, d, n);
  strcpy(tour_file_name, argv[1]);
  strcat(tour_file_name, ".out");
  tour_file.open(tour_file_name);

  cout << "Tour read:  ";
  for (i = 0; i < n; i++)
    {
    tour_file >> best_tour[i];
    cout << best_tour[i] << "  ";
    }
  cout << endl;
  tour_file >> file_dist;
  best_dist = tour_length(best_tour, d, n);
  cout << "Distance from file: " << file_dist << endl;
  cout << "Distance computed:  " << best_dist << endl;
  cout << "Difference:  " << file_dist - best_dist << endl;
  }
