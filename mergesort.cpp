#include <fstream>

using namespace std;

void merge(int array[], int start, int middle, int end)
{
   int *temp = new int[end - start + 1];
   int left = start;
   int right = middle + 1;
   int index = 0;

   while(left <= middle && right <= end)
      if(array[right] < array[left])
         temp[index++] = array[right++];
      else
         temp[index++] = array[left++];

   while(left <= middle)
      temp[index++] = array[left++];

   while(right <= end)
      temp[index++] = array[right++];

   index = 0;
   while(start <= end)
      array[start++] = temp[index++];

   delete [] temp;
}

int sort(int array[], int start, int end)
{
   if(start >= end)
      return 0;
   else
   {
      int middle = (start + end) / 2;
      int somma = array[start];
      somma += sort(array, start, middle);
      somma += sort(array, middle + 1, end);
      merge(array, start, middle, end);
      return somma;
   }
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

      int somma = sort(array, 0, n - 1);

      out << somma << endl;
   }

   return 0;
}
