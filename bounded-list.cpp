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
class List
{
   public:
      List(H value)
      {
         head = new Node<H>(value);
         next = NULL;
         counter = 1;
      }

      void insert(H value)
      {
         Node<H> *newNode = new Node<H>(value);
         if(!head)
            head = newNode;
         else
         {
            Node<H> *check = head;
            Node<H> *prev = NULL;
            while(check && value >= check->getData())
            {
               prev = check;
               check = check->getNext();
            }
            newNode->setNext(check);
            if(!prev)
               head = newNode;
            else
               prev->setNext(newNode);
         }
         counter++;
      }

      void remove(H value)
      {
         Node<H> *check = head;
         Node<H> *prev = NULL;
         while(check && value > check->getData())
         {
            prev = check;
            check = check->getNext();
         }
         if(check && value == check->getData())
         {
            if(!prev)
               head = head->getNext();
            else
               prev->setNext(check->getNext());
            delete check;
            counter--;
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
      }

      List<H> * getNext()
      {
         return next;
      }

      void setNext(List<H> *ptr)
      {
         next = ptr;
      }

      int getCounter()
      {
         return counter;
      }

   private:
      Node<H> *head;
      List<H> *next;
      int counter;
};

template<typename H>
class KBList
{
   public:
      KBList(int num)
      {
         k = num;
         head = NULL;
      }

      void insert(H value)
      {
         if(!head)
            head = new List<H>(value);
         else if(head->getCounter() == k)
         {
            List<H> *newList = new List<H>(value);
            newList->setNext(head);
            head = newList;
         }
         else
            head->insert(value);
      }

      void remove(H value)
      {
         List<H> *check = head;
         List<H> *prev = NULL;
         while(check)
         {
            check->remove(value);
            if(check->getCounter() == 0)
            {
               if(!prev)
                  head = head->getNext();
               else
                  prev->setNext(check->getNext());
               List<H> *temp = check;
               check = check->getNext();
               delete temp;
            }
            else
            {
               prev = check;
               check = check->getNext();
            }
         }
      }

      void print(ostream &output)
      {
         List<H> *check = head;
         while(check)
         {
            check->print(output);
            check = check->getNext();
         }
         output << endl;
      }

   private:
      List<H> *head;
      int k;
};

int main()
{
   ifstream in("input.txt");
   ofstream out("output.txt");

   for(int i = 0; i < 100; i++)
   {
      string tipo;
      int k;
      in >> tipo >> k;

      KBList<double> kbl(k);

      string operazione;
      do
      {
         in >> operazione;

         if(operazione == "ins")
         {
            double valore;
            in >> valore;
            kbl.insert(valore);
         }
         else if(operazione == "canc")
         {
            double valore;
            in >> valore;
            kbl.remove(valore);
         }
      }
      while(operazione != "#");

      kbl.print(out);
   }

   return 0;
}
