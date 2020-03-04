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

      void pop(H &value)
      {
         if(head)
         {
            Node<H> *temp = head;
            value = temp->getData();
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

      Node<H> * getHead()
      {
         return head;
      }

   private:
      Node<H> *head;
};

template<typename H>
class Queue
{
   public:
      Queue()
      {
      }

      void enqueue(H value)
      {
         a.push(value);
      }

      void dequeue()
      {
         travaso(a, b);
         H value;
         b.pop(value);
         travaso(b, a);
      }

      void travaso(Stack<H> &from, Stack<H> &to)
      {
         while(from.getHead())
         {
            H value;
            from.pop(value);
            to.push(value);
         }
      }

      void print(ostream &output)
      {
         travaso(a, b);
         b.print(output);
      }

   private:
      Stack<H> a;
      Stack<H> b;
};

template<typename H>
void manager(istream &in, ostream &out, H valore)
{
   Queue<H> coda;

   int n;
   in >> n;

   for(int i = 0; i < n; i++)
   {
      char simbolo;
      in >> simbolo;

      if(simbolo == 'i')
      {
         in >> valore;
         coda.enqueue(valore);
      }
      else if(simbolo == 'd')
      {
         coda.dequeue();
         in.ignore(6);
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
