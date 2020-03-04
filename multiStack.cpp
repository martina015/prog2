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
      Stack(H value)
      {
         head = new Node<H>(value);
         next = NULL;
      }

      void push(H element)
      {
         Node<H> *newNode = new Node<H>(element);
         newNode->setNext(head);
         head = newNode;
      }

      H* pop()
      {
         H *value = NULL;
         if(head)
         {
            Node<H> *temp = head;
            value = new H(temp->getData());
            head = head->getNext();
            delete temp;
         }
         return value;
      }

      void print(ostream &output)
      {
         Node<H> *temp = head;
         while(temp)
         {
            output << temp->getData() << " ";
            temp = temp->getNext();
         }
      }

      Stack<H> * getNext()
      {
         return next;
      }

      void setNext(Stack<H> *ptr)
      {
         next = ptr;
      }

      bool empty()
      {
         return head == NULL;
      }

      H topValue()
      {
         return head->getData();
      }

   private:
      Node<H> *head;
      Stack<H> *next;
};

template<typename H>
class MultiStack
{
   public:
      MultiStack()
      {
         head = NULL;
      }

      void newPush(H value)
      {
         Stack<H> *newStack = new Stack<H>(value);
         if(!head)
            head = newStack;
         else
         {
            Stack<H> *check = head;
            Stack<H> *prev = NULL;
            while(check && value >= check->topValue())
            {
               prev = check;
               check = check->getNext();
            }
            newStack->setNext(check);
            if(!prev)
               head = newStack;
            else
               prev->setNext(newStack);
         }
      }

      void push(H value)
      {
         head->push(value);
         sort();
      }

      H* pop()
      {
         H *value = head->pop();
         if(head->empty())
         {
            Stack<H> *temp = head;
            head = head->getNext();
            delete temp;
         }
         else
            sort();
         return value;
      }

      void print(ostream &output)
      {
         Stack<H> *check = head;
         while(check)
         {
            check->print(output);
            check = check->getNext();
         }
         output << endl;
      }

   private:
      Stack<H> *head;

      void sort()
      {
         Stack<H> *check = head->getNext();
         Stack<H> *prev = NULL;
         while(check && head->topValue() >= check->topValue())
         {
            prev = check;
            check = check->getNext();
         }
         if(prev)
         {
            Stack<H> *temp = head;
            head = head->getNext();
            prev->setNext(temp);
            temp->setNext(check);
         }
      }
};

int main()
{
   ifstream in("input.txt");
   ofstream out("output.txt");

   for(int i = 0; i < 100; i++)
   {
      string tipo;
      int n;
      in >> tipo >> n;

      MultiStack<double> multi;

      for(int i = 0; i < n; i++)
      {
         char simbolo;
         in >> simbolo;

         if(simbolo == 'n')
         {
            in.ignore();
            double valore;
            in >> valore;
            multi.newPush(valore);
         }
         else if(simbolo == 'p')
         {
            in >> simbolo;

            if(simbolo == ':')
            {
               double valore;
               in >> valore;
               multi.push(valore);
            }
            else
            {
               multi.pop();
               in.ignore();
            }
         }
      }

      multi.print(out);
   }

   return 0;
}
