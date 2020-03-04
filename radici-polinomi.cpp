#include <fstream>
#include <cmath>

using namespace std;

class Monomio
{
   public:
      Monomio(int x, int y)
      {
         c = x;
         exp = y;
         next = NULL;
      }

      int getC()
      {
         return c;
      }

      void setC(int x)
      {
         c = x;
      }

      int getExp()
      {
         return exp;
      }

      void setExp(int y)
      {
         exp = y;
      }

      Monomio * getNext()
      {
         return next;
      }

      void setNext(Monomio *ptr)
      {
         next = ptr;
      }

   private:
      int c;
      int exp;
      Monomio *next;
};

class Polinomio
{
   public:
      Polinomio()
      {
         head = NULL;
      }

      void leggi(istream &in)
      {
         char simbolo;
         do
         {
            int c = 1;
            int segno = 1;
            if(in.peek() != 'x')
            {
               if(in.peek() == '+')
                  in >> simbolo;
               else if(in.peek() == '-')
               {
                  in >> simbolo;
                  segno = -1;
               }

               if(in.peek() != 'x')
                  in >> c;

               c *= segno;
            }

            int exp = 0;
            simbolo = in.get();
            if(simbolo == 'x')
            {
               exp = 1;
               if(in.peek() == '^')
               {
                  in >> simbolo;
                  in >> exp;
               }
            }

            insert(c, exp);
         }
         while(simbolo != '\n');
      }

      void ruffini()
      {
         init();

         int flag = 0;
         while(!flag && head->getExp() > 1)
         {
            Monomio *tail = head;
            while(tail->getExp())
               tail = tail->getNext();

            int x = tail->getC() / head->getC();
            int div = 1;
            int rad = 0;
            do
            {
               while(div < 100 && x % div) // while(div <= abs(x) && x % div)
                  div++;

               int zero = totale(div);
               if(zero)
                  rad = div;
               else
               {
                  div *= -1;
                  zero = totale(div);
                  if(zero)
                     rad = div;
                  else
                     div = div * -1 + 1;
               }
            }
            while(!rad && div < 100); // while(!rad && div <= abs(x));

            if(rad)
            {
               addRad(rad);

               int last = 0;
               Polinomio poliB;
               Monomio *check = head;

               for(int exp = head->getExp(); exp > 0; exp--)
               {
                  int c;
                  if(exp != check->getExp())
                     c = last = last * rad;
                  else
                  {
                     if(check == head)
                        c = last = check->getC();
                     else
                        c = last = last * rad + check->getC();

                     check = check->getNext();
                  }

                  poliB.insert(c, exp - 1);

                  if(head->getExp() == 2 && exp == 1)
                     addRad(c * -1);
               }

               *this = poliB;
            }
            else
               flag = 1;
         }

         sort();
      }

      void stampa(ostream &out)
      {
         for(int i = 0; i < fine; i++)
         {
            out << "(x";

            if(radice[i] > 0) // if(radice[i] < 0)
               out << "+";

            out << radice[i] << ")"; // out << radice[i] * -1 << ")";

            if(multi[i] > 1)
               out << "^" << multi[i];

            if(i < fine - 1)
               out << " * ";
         }
         out << endl;
      }

   private:
      Monomio *head;
      int *radice;
      int *multi;
      int fine;

      void insert(int c, int exp)
      {
         Monomio *newMono = new Monomio(c, exp);
         Monomio *check = head;
         Monomio *prev = NULL;
         while(check && exp < check->getExp())
         {
            prev = check;
            check = check->getNext();
         }
         newMono->setNext(check);
         if(!prev)
            head = newMono;
         else
            prev->setNext(newMono);
      }

      void init()
      {
         int dim = head->getExp();

         radice = new int[dim];
         multi = new int[dim];
         for(int i = 0; i < dim; i++)
            radice[i] = multi[i] = 0;

         fine = 0;
      }

      int totale(int div)
      {
         double tot = 0;
         Monomio *temp = head;
         while(temp)
         {
            tot += (pow(div, temp->getExp()) * temp->getC());
            temp = temp->getNext();
         }
         if(!tot)
            return 1;
         else
            return 0;
      }

      void addRad(int rad)
      {
         int found = 0;

         for(int i = 0; i < fine; i++)
            if(radice[i] == rad)
            {
               multi[i]++;
               found = 1;
            }

         if(!found)
         {
            radice[fine] = rad;
            multi[fine] = 1;
            fine++;
         }
      }

      void sort()
      {
         for(int i = 0; i < fine - 1; i++)
         {
            int max = i; // int min = i;
            for(int j = i + 1; j < fine; j++)
               if(radice[j] > radice[max]) // if(radice[j] < radice[min])
                  max = j; // min = j;

            if(max != i) // if(min != i)
            {
               int tempR = radice[i];
               radice[i] = radice[max]; // radice[i] = radice[min];
               radice[max] = tempR; // radice[min] = tempR;

               int tempM = multi[i];
               multi[i] = multi[max]; // multi[i] = multi[min];
               multi[max] = tempM; // multi[min] = tempM;
            }
         }
      }

      Monomio * getHead()
      {
         return head;
      }

      const Polinomio & operator=(Polinomio &poliB)
      {
         Monomio *temp = head;
         while(temp)
         {
            head = head->getNext();
            delete temp;
            temp = head;
         }
         temp = poliB.getHead();
         while(temp)
         {
            insert(temp->getC(), temp->getExp());
            temp = temp->getNext();
         }
         return *this;
      }
};

int main()
{
   ifstream in("input.txt");
   ofstream out("output.txt");

   for(int i = 0; i < 100; i++)
   {
      Polinomio poliA;

      poliA.leggi(in);

      poliA.ruffini();

      poliA.stampa(out);
   }

   return 0;
}
