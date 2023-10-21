#include <iostream>
#include <ctime>

using namespace std;

int distanceMatrix[10][10] = {
    {0, 374, 350, 223, 108, 178, 252, 285, 240, 356},
    {374, 0, 27, 166, 433, 199, 135, 95, 136, 17},
    {350, 27, 0, 41, 52, 821, 180, 201, 131, 247},
    {223, 166, 41, 0, 430, 47, 52, 84, 40, 155},
    {108, 433, 52, 430, 0, 453, 478, 344, 389, 423},
    {178, 199, 821, 47, 453, 0, 91, 37, 64, 181},
    {252, 135, 180, 52, 478, 91, 0, 25, 83, 117},
    {285, 95, 201, 84, 344, 37, 25, 0, 51, 42},
    {240, 136, 131, 40, 389, 64, 83, 51, 0, 118},
    {356, 17, 247, 155, 423, 181, 117, 42, 118, 0}};

void SequenceToSpanningTree(int *P, int len, int *T)
{
  int i, j, q = 0;
  int n = len + 2;
  int *V = new int[n];

  for (i = 0; i < n; i++)
    V[i] = 0;

  for (i = 0; i < len; i++)
    V[P[i] - 1] += 1;

  for (i = 0; i < len; i++)
  {
    for (j = 0; j < n; j++)
    {
      if (V[j] == 0)
      {
        V[j] = -1;
        T[q++] = j + 1;
        T[q++] = P[i];
        V[P[i] - 1]--;
        break;
      }
    }
  }

  j = 0;
  for (i = 0; i < n; i++)
  {
    if (V[i] == 0 && j == 0)
    {
      T[q++] = i + 1;
      j++;
    }
    else if (V[i] == 0 && j == 1)
    {
      T[q++] = i + 1;
      break;
    }
  }

  delete[] V;
}

int calculateDistance(int *T, int size, int *elementFrequency)
{
  int distance = 0;

  int firstNode, secondNode, firstFrequency, secondFrequency;

  for (int i = 0; i < size - 1; i += 2)
  {
    firstNode = T[i] - 1;
    secondNode = T[i + 1] - 1;

    firstFrequency = elementFrequency[firstNode];
    secondFrequency = elementFrequency[secondNode];

    if (firstFrequency >= 4)
    {
      distance += distanceMatrix[firstNode][secondNode] + 250 * (firstFrequency - 3);
    }
    else if (secondFrequency >= 4)
    {
      distance += distanceMatrix[firstNode][secondNode] + 250 * (secondFrequency - 3);
    }
    else
    {
      distance += distanceMatrix[firstNode][secondNode];
    }
  }

  return distance;
}

void printSpanningTree(int *T, int len)
{
  char cities[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};

  cout << "(";
  for (int i = 0; i < 2 * (len + 1); i++)
  {
    cout << " " << cities[T[i] - 1];
    if ((i + 1) % 2 == 0 && i < 2 * len)
      cout << " -";
  }
  cout << " )" << endl;
}

void findShortestPath(int n, int k)
{
  int q;
  int *P = new int[k];
  int *temp = new int[k];

  for (int i = 0; i < k; i++)
    P[i] = temp[i] = 0;

  int distance;
  int bestDistance = 5000; // inf

  int len = k;
  int *T = new int[2 * (len + 1)];
  int size = 2 * (len + 1);

  int *bestPath = new int[2 * (len + 1)];

  do
  {
    for (int i = 0; i < k; i++)
      temp[i] = P[i] + 1;

    SequenceToSpanningTree(temp, len, T);
    int elementFrequency[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    for (int i = 0; i < size; i++)
    {
      elementFrequency[T[i] - 1]++;
    }

    distance = calculateDistance(T, size, elementFrequency);

    if (distance < bestDistance)
    {
      bestDistance = distance;
      for (int j = 0; j < size; j++)
      {
        bestPath[j] = T[j];
      }
    }

  skip:

    q = k - 1;
    while (q >= 0)
    {
      P[q]++;
      if (P[q] == n)
      {
        P[q] = 0;
        q--;
      }
      else
        break;
    }

  } while (q >= 0);

  cout << "Minimalna cena: " << bestDistance << endl;
  printSpanningTree(bestPath, len);

  delete[] P;
  delete[] T;
  delete[] bestPath;
}

int main()
{
  time_t startTime;
  std::time(&startTime);

  findShortestPath(10, 8);

  time_t endTime;
  std::time(&endTime);
  cout << "\nTime of execution: " << endTime - startTime << " seconds" << endl;
  return 0;
}
