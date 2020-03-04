#include <fstream>

using namespace std;

int sort(int array[], int n)
{
   int swap = 0;
   for(int i = 1; i < n; i++)
   {
      int j = i;
      while(j > 0 && array[j] < array[j - 1])
      {
         int temp = array[j];
         array[j] = array[j - 1];
         array[j - 1] = temp;
         swap++;
         j--;
      }
   }
   return swap;
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

      int swap = sort(array, n);

      out << swap << endl;
   }

   return 0;
}
