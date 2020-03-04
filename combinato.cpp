#include <fstream>

using namespace std;

int main()
{
   ifstream in("input.txt");
   ofstream out("output.txt");

   for(int i = 0; i < 100; i++)
   {
      int num;
      in >> num;

      int k[num];
      int n[num];

      in >> k[0];
      n[0] = -1;

      int h = 0;

      for(int i = 1; i < num; i++)
      {
         in >> k[i];

         int check = h;
         int prev = -1;

         while(check != -1 && k[i] >= k[check])
         {
            prev = check;
            check = n[check];
         }

         n[i] = check;
         if(prev == -1)
            h = i;
         else
            n[prev] = i;
      }

      for(int j = 0; j < num; j++)
         out << n[j] << " ";
      out << endl;
   }

   return 0;
}
