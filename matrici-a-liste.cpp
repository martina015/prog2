#include <fstream>

using namespace std;

class Node
{
   public:
      Node(int element)
      {
         data = element;
         next = NULL;
      }

      int getData()
      {
         return data;
      }

      void setData(int element)
      {
         data = element;
      }

      Node * getNext()
      {
         return next;
      }

      void setNext(Node *ptr)
      {
         next = ptr;
      }

   private:
      int data;
      Node *next;
};

class List
{
   public:
      List()
      {
         head = tail = NULL;
         next = NULL;
      }

      void insert(int value)
      {
         Node *newNode = new Node(value);
         if(!head)
            head = newNode;
         else
            tail->setNext(newNode);
         tail = newNode;
      }

      void print(ostream &out)
      {
         Node *check = head;
         while(check)
         {
            out << check->getData() << " ";
            check = check->getNext();
         }
      }

      List * getNext()
      {
         return next;
      }

      void setNext(List *ptr)
      {
         next = ptr;
      }

      Node* getHead()
      {
         return head;
      }

      void setHead(Node *ptr)
      {
         head = ptr;
      }

   private:
      Node *head;
      Node *tail;
      List *next;
};

class LMatrix
{
   public:
      LMatrix()
      {
         head = tail = NULL;
      }

      void init(int n, int m, istream &in)
      {
         for(int i = 0; i < n; i++)
         {
            List *newList = new List;
            if(!head)
               head = newList;
            else
               tail->setNext(newList);
            tail = newList;

            for(int j = 0; j < m; j++)
            {
               int value;
               in >> value;
               newList->insert(value);
            }
         }
      }

      LMatrix* multi(LMatrix &lmB, int p)
      {
         LMatrix *lmC = new LMatrix;
         List *checkListA = head;

         while(checkListA)
         {
            List *newListC = new List;
            if(lmC->empty())
               lmC->setHead(newListC);
            else
               lmC->getTail()->setNext(newListC);
            lmC->setTail(newListC);

            for(int j = 0; j < p; j++)
            {
               Node *checkNodeA = checkListA->getHead();
               List *checkListB = lmB.getHead();
               int valueC = 0;

               while(checkNodeA)
               {
                  Node *checkNodeB = checkListB->getHead();
                  for(int k = 0; k < j; k++)
                     checkNodeB = checkNodeB->getNext();

                  valueC += checkNodeA->getData() * checkNodeB->getData();

                  checkNodeA = checkNodeA->getNext();
                  checkListB = checkListB->getNext();
               }
               newListC->insert(valueC);
            }
            checkListA = checkListA->getNext();
         }
         return lmC;
      }

      void print(ostream &out)
      {
         List *check = head;
         while(check)
         {
            check->print(out);
            check = check->getNext();
         }
         out << endl;
      }

   private:
      List *head;
      List *tail;

      List * getHead()
      {
         return head;
      }

      void setHead(List *ptr)
      {
         head = ptr;
      }

      List * getTail()
      {
         return tail;
      }

      void setTail(List *ptr)
      {
         tail = ptr;
      }

      bool empty()
      {
         return head == NULL;
      }
};

int main()
{
   ifstream in("input.txt");
   ofstream out("output.txt");

   for(int i = 0; i < 100; i++)
   {
      int n;
      int m;
      int p;
      in >> n >> m >> p;

      LMatrix lmA;
      lmA.init(n, m, in);

      LMatrix lmB;
      lmB.init(m, p, in);

      LMatrix *lmC = lmA.multi(lmB, p);
      lmC->print(out);
   }

   return 0;
}
