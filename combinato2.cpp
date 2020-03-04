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

      int head = -1;
      int index = -1;

      for(int i = 0; i < num; i++)
      {
         char simbolo;
         in >> simbolo;

         if(simbolo == 'i')
         {
            in >> k[++index];

            if(head == -1)
            {
               head = index;
               n[index] = -1;
            }
            else
            {
               int check = head;
               int prev = -1;

               while(check != -1 && k[index] >= k[check])
               {
                  prev = check;
                  check = n[check];
               }

               n[index] = check;
               if(prev == -1)
                  head = index;
               else
                  n[prev] = index;
            }
         }
         else if(simbolo == 'c')
         {
            int valore;
            in >> valore;

            int posI = head;
            int prevI = -1;

            while(posI != index)
            {
               prevI = posI;
               posI = n[posI];
            }

            int posC = head;
            int prevC = -1;

            while(k[posC] != valore)
            {
               prevC = posC;
               posC = n[posC];
            }

            int newH = head;

            if(head == index)
               newH = posC;
            else
               n[prevI] = posC;

            if(head != posC)
               n[prevC] = n[posC];
            else if(n[head] != index)
               newH = n[head];

            k[posC] = k[index];
            n[posC] = n[index];
            head = newH;

            index--;
         }
      }

      for(int j = 0; j <= index; j++)
         out << n[j] << " ";
      out << endl;
   }

   return 0;
}
