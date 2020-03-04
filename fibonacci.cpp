#include <fstream>

using namespace std;

int main()
{
   ifstream in("input.txt");
   ofstream out("output.txt");

   long int fibo[61] = {0, 1};
   for(int i = 2; i <= 60; i++)
      fibo[i] = fibo[i - 1] + fibo[i - 2];

   for(int i = 0; i < 100; i++)
   {
      int n;
      in >> n;
      out << fibo[n] << endl;
   }

   return 0;
}
