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

      void dequeue()
      {
         if(head)
         {
            Node<H> *temp = head;
            head = head->getNext();
            delete temp;
         }
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
class Stack
{
   public:
      Stack()
      {
         head = NULL;
      }

      void push(H element)
      {
         Node<H> *newNode = new Node<H>(element);
         newNode->setNext(head);
         head = newNode;
      }

      void pop()
      {
         if(head)
         {
            Node<H> *temp = head;
            head = head->getNext();
            delete temp;
         }
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

      void travasa(Queue<H> &coda)
      {
         while(head)
         {
            coda.enqueue(head->getData());
            pop();
         }
      }

   private:
      Node<H> *head;
};

template<typename H>
void manager(istream &in, ostream &out, H valore)
{
   Stack<H> pila;
   Queue<H> coda;

   int n;
   in >> n;

   for(int i = 0; i < n; i++)
   {
      char simbolo;
      in >> simbolo;

      if(simbolo == 'e')
      {
         in.ignore();
         in >> valore;
         coda.enqueue(valore);
      }
      else if(simbolo == 'd')
      {
         coda.dequeue();
         in.ignore(6);
      }
      else if(simbolo == 't')
      {
         pila.travasa(coda);
         in.ignore(6);
      }
      else if(simbolo == 'p')
      {
         in >> simbolo;

         if(simbolo == ':')
         {
            in >> valore;
            pila.push(valore);
         }
         else
         {
            pila.pop();
            in.ignore();
         }
      }
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
