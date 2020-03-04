#include <fstream>

using namespace std;

int sort(int array[], int n)
{
   int distanza = 0;
   for(int i = 0; i < n - 1; i++)
   {
      int min = i;
      for(int j = i + 1; j < n; j++)
         if(array[j] < array[min])
            min = j;

      if(min != i)
      {
         int temp = array[i];
         array[i] = array[min];
         array[min] = temp;
         distanza += (min - i);
      }
   }
   return distanza;
}

int main()
{
   ifstream in("input.txt");
   ofstream out("output.txt");

   for(int i = 0; i < 100; i++)
   {
      int n;
      in >> n;

      int array[n];
      for(int i = 0; i < n; i++)
         in >> array[i];

      int distanza = sort(array, n);

      out << distanza << endl;
   }

   return 0;
}
