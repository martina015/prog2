#include <fstream>

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
         in >> simbolo;
         while(simbolo != ')')
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
            in >> simbolo;
            if(simbolo == 'x')
            {
               exp = 1;
               if(in.peek() == '^')
               {
                  in >> simbolo;
                  in >> exp;
               }

               if(in.peek() == ')')
                  in >> simbolo;
            }

            insert(c, exp);
         }
      }

      void totale(char op, Polinomio &poliB)
      {
         Monomio *tempB = poliB.getHead();
         while(tempB)
         {
            if(op == '-')
               tempB->setC(tempB->getC() * -1);
            insert(tempB->getC(), tempB->getExp());
            tempB = tempB->getNext();
         }
      }

      void stampa(ostream &out)
      {
         Monomio *temp = head;
         while(temp)
         {
            if(temp != head && temp->getC() > 0)
               out << "+";

            if(temp->getExp() == 0 || (temp->getC() != 1 && temp->getC() != -1))
               out << temp->getC();
            else if(temp->getC() == -1)
               out << "-";

            if(temp->getExp() == 1)
               out << "x";
            else if(temp->getExp() > 1)
               out << "x^" << temp->getExp();

            temp = temp->getNext();
         }
         out << endl;
      }

   private:
      Monomio *head;

      void insert(int c, int exp)
      {
         if(!head)
            head = new Monomio(c, exp);
         else
         {
            Monomio *check = head;
            Monomio *prev = NULL;
            while(check && exp < check->getExp())
            {
               prev = check;
               check = check->getNext();
            }
            if(check && exp == check->getExp())
            {
               check->setC(check->getC() + c);
               if(check->getC() == 0)
                  remove(check);
            }
            else
            {
               Monomio *newMono = new Monomio(c, exp);
               newMono->setNext(check);
               if(!prev)
                  head = newMono;
               else
                  prev->setNext(newMono);
            }
         }
      }

      void remove(Monomio *check)
      {
         Monomio *temp = head;
         Monomio *prev = NULL;
         while(temp != check)
         {
            prev = temp;
            temp = temp->getNext();
         }
         if(!prev)
            head = head->getNext();
         else
            prev->setNext(check->getNext());
         delete check;
      }

      Monomio * getHead()
      {
         return head;
      }
};

int main()
{
   ifstream in("input.txt");
   ofstream out("output.txt");

   for(int i = 0; i < 100; i++)
   {
      int n;
      in >> n;

      Polinomio poliA;
      poliA.leggi(in);

      for(int j = 1; j < n; j++)
      {
         char segno;
         in >> segno;

         Polinomio poliB;
         poliB.leggi(in);

         poliA.totale(segno, poliB);
      }

      poliA.stampa(out);
   }

   return 0;
}
