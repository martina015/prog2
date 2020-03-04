#include <fstream>

using namespace std;

void hanoi(int num, int mossa, int &counter, int a, int b, int c, ostream &out)
{
   if(counter < mossa)
   {
      if(num == 1)
      {
         counter++;

         if(counter == mossa)
            out << a << " " << c << endl;
      }
      else
      {
         hanoi(num - 1, mossa, counter, a, c, b, out);

         counter++;

         if(counter == mossa)
            out << a << " " << c << endl;

         hanoi(num - 1, mossa, counter, b, a, c, out);
      }
   }
}

int main()
{
   ifstream in("input.txt");
   ofstream out("output.txt");

   for(int i = 0; i < 100; i++)
   {
      int num;
      int mossa;
      in >> num >> mossa;

      int counter = 0;

      hanoi(num, mossa, counter, 1, 2, 3, out);
   }

   return 0;
}
