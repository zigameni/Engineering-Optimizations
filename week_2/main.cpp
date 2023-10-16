#include <stdio.h>
// #include <algorithm>
#include <iostream>
#include <vector>
#include <time.h> // To calculate time
#include <cmath> // use sqrt

using namespace std;

int next_permutation(const int N, int *P)
{
  int s;
  int *first = &P[0];
  int *last = &P[N - 1];
  int *k = last - 1;
  int *l = last;
  // find larges k so that P[k] <P [k+1] while (k>first) I
  while (k > first)
  {
    if (*k < *(k + 1))
    {
      break;
    }
    k--;
  }
  // if no P[k]<p[k+1], p is the last permutation in lexicographic order
  if(*k>*(k+1))
  {
    return 0;
  }
  // find the larges l so that P[k]< P[l]
  while(l>k)
  {
    if(*l>*k)
    {
      break;
    }
    l--;
  }
  // swap P[l] and P[k]
  s=*k;
  *k=*l;
  *l=s;
  // reverse the remaining P[k+1]...P[N-1]
  first=k+1;
  while(first<last)
  {
    s=*first;
    *first = *last;
    *last=s;

    first++;
    last--;
  }

  return 1;
}


struct Point {
  double x, y;
};

// Izracunamo daljinu izmedju dve tacke.
double calculateDistance(const Point &p1, const Point &p2){
  // √((x_2-x_1)²+(y_2-y_1)²)
  double dx = p2.x - p1.x;
  double dy = p2.y - p1.y;
  return sqrt(dx*dx + dy*dy);
}

// Koristili smo da generisemo matricu daljina. 
void generateDistanceMatrix(const vector<Point>& p, double distanceMatrix[12][12]) {
    int n = p.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            distanceMatrix[i][j] = calculateDistance(p[i], p[j]);
        }
    }
}

const double inf = 1000.0;
double distanceMatrix[12][12] = {
        {0, 23.7, 9.63328, 20.7135, 20.64, 13.448, 22.6877, 20.204, 41.1491, 25.7381, 32.6939, 43.7379},
        {23.7, 0, 17.6977, 7.54718, 14.3388, 22.7982, 21.7816, 31.446, 30.9222, 35.9235, 44.138, 53.4218},
        {9.63328, 17.6977, 0, 12.5, 11.0675, 6.68506, 13.565, 15.7544, 31.5995, 21.1294, 29.1302, 39.6308},
        {20.7135, 7.54718, 12.5, 0, 6.8, 16.2308, 14.2394, 24.3813, 25.4908, 28.5955, 36.7739, 45.9004},
        {20.64, 14.3388, 11.0675, 6.8, 0, 11.8017, 7.44312, 18.6132, 21.3002, 22.3002, 30.371, 39.1996},
        {13.448, 22.7982, 6.68506, 16.2308, 11.8017, 0, 10.1213, 9.1526, 29.0327, 14.4506, 22.5016, 32.9462},
        {22.6877, 21.7816, 13.565, 14.2394, 7.44312, 10.1213, 0, 13.1746, 18.913, 15.6978, 23.4649, 31.8454},
        {20.204, 31.446, 15.7544, 24.3813, 18.6132, 9.1526, 13.1746, 0, 29.7168, 5.59017, 13.3765, 24.0333},
        {41.1491, 30.9222, 31.5995, 25.4908, 21.3002, 29.0327, 18.913, 29.7168, 0, 29.2308, 34.1248, 37.476},
        {25.7381, 35.9235, 21.1294, 28.5955, 22.3002, 14.4506, 15.6978, 5.59017, 29.2308, 0, 8.23286, 18.5162},
        {32.6939, 44.138, 29.1302, 36.7739, 30.371, 22.5016, 23.4649, 13.3765, 34.1248, 8.23286, 0, 11.0766},
        {43.7379, 53.4218, 39.6308, 45.9004, 39.1996, 32.9462, 31.8454, 24.0333, 37.476, 18.5162, 11.0766, 0}
    };

vector<Point> points = {
    {2.7, 33.1}, //point 1
    {2.7, 56.8}, //point 2
    {9.1, 40.3}, //point 3
    {9.1, 52.8}, //point 4
    {15.1, 49.6}, //point 5
    {15.3, 37.8}, //point 6
    {21.5, 45.8}, //point 7
    {22.9, 32.7}, //point 8
    {33.4, 60.5}, //point 9
    {28.4,31.7}, //point 10
    {34.7,26.4}, //point 11
    {45.7,25.1}, //point 12
    // {34.7,45.1}, //point 13
    // {46.0,45.1}, //point 14
    // {54.2,29.1}, //point 15
    // {57.7,42.1}, //point 16
    // {67.9,19.6}, //point 17
    // {51.7,56.0}, //point 18
    // {57.5,56.0}, //point 19
    // {62.0,58.4} //point 20
  };

double calculatePathLength(int* path, int length){
  double distance = 0;

  for (int i = 0; i < length-1; i++)
    distance += distanceMatrix[path[i]][path[i+1]];
  
  // for (int i = 0; i < length-1; i++)
  //   distance += calculateDistance(points[path[i]], points[path[i+1]]);
    
  return distance;
}

void findTheShortestPath(int numberOfHoles){
  int* path = new int [numberOfHoles];

  // Initialize the first permutation
  for(int i=0; i<numberOfHoles; i++){
    path[i]=i;
  }

  double distance;
  double bestDistance = inf;
  int* bestPath = new int[numberOfHoles];

  do {
    distance = calculatePathLength(path, numberOfHoles);
    if(distance < bestDistance){
      bestDistance = distance;
      for (int i = 0; i < numberOfHoles; i++)
        bestPath[i] = path[i];
    }
    
  }while(next_permutation(numberOfHoles, path));

  cout << "Best path for the first: "<<numberOfHoles<<" holes"<<endl;
  for (int i = 0; i<numberOfHoles; i++ ) {
      cout << bestPath[i]+1 << " ";
  }

  cout << "\nShortest path length: " << bestDistance << endl;
}


int main(void){
  int N = 12;
  // int N = 8;  
  
  time_t startTime;
  time(&startTime);

  // Find the shortest path  
  findTheShortestPath(N);
  
  time_t endTime;
  time(&endTime);
  cout<<"Time of execution: "<<endTime - startTime<<" seconds"<<endl;
  // delete [] path;
  return 0;
}
