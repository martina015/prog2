#include <fstream>

using namespace std;

template<typename H>
class Node
{
   public:
      Node(H element)
      {
         data = element;
         next = NULL;
      }

      H getData()
      {
         return data;
      }

      void setData(H element)
      {
         data = element;
      }

      Node<H> * getNext()
      {
         return next;
      }

      void setNext(Node<H> *ptr)
      {
         next = ptr;
      }

   private:
      H data;
      Node<H> *next;
};

template<typename H>
class Queue
{
   public:
      Queue()
      {
         head = tail = NULL;
      }

      void enqueue(H element)
      {
         Node<H> *newNode = new Node<H>(element);
         if(!head)
            head = newNode;
         else
            tail->setNext(newNode);
         tail = newNode;
      }

      void print(ostream &output)
      {
         Node<H> *temp = head;
         while(temp)
         {
            output << temp->getData() << " ";
            temp = temp->getNext();
         }
         output << endl;
      }

   private:
      Node<H> *head;
      Node<H> *tail;
};

template<typename H>
void manager(istream &in, ostream &out, H valore)
{
   Queue<H> coda;

   int n;
   in >> n;

   for(int i = 0; i < n; i++)
   {
      in >> valore;
      coda.enqueue(valore);
   }

   coda.print(out);
}

int main()
{
   ifstream in("input.txt");
   ofstream out("output.txt");

   for(int i = 0; i < 100; i++)
   {
      double numero;
      char lettera;

      string tipo;
      in >> tipo;

      if(tipo == "char")
         manager(in, out, lettera);
      else
         manager(in, out, numero);
   }

   return 0;
}
