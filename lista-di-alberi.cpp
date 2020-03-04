#include <fstream>

using namespace std;

template<typename H>
class Node
{
   public:
      Node(H element)
      {
         data = element;
         left = right = father = NULL;
      }

      H getData()
      {
         return data;
      }

      void setData(H element)
      {
         data = element;
      }

      Node<H> * getLeft()
      {
         return left;
      }

      void setLeft(Node<H> *ptr)
      {
         left = ptr;
      }

      Node<H> * getRight()
      {
         return right;
      }

      void setRight(Node<H> *ptr)
      {
         right = ptr;
      }

      Node<H> * getFather()
      {
         return father;
      }

      void setFather(Node<H> *ptr)
      {
         father = ptr;
      }

   private:
      H data;
      Node<H> *left;
      Node<H> *right;
      Node<H> *father;
};

template<typename H>
class BST
{
   public:
      BST(H value)
      {
         root = new Node<H>(value);
         next = NULL;
         counter = 1;
      }

      void insert(H value)
      {
         Node<H> *newNode = new Node<H>(value);
         if(!root)
            root = newNode;
         else
         {
            Node<H> *check = root;
            Node<H> *prev = NULL;
            while(check)
            {
               prev = check;
               if(value > check->getData())
                  check = check->getRight();
               else
                  check = check->getLeft();
            }
            newNode->setFather(prev);
            if(value > prev->getData())
               prev->setRight(newNode);
            else
               prev->setLeft(newNode);
         }
         counter++;
      }

      void remove(H value)
      {
         Node<H> *check = search(value);
         if(check)
         {
            if(check->getLeft() && check->getRight())
            {
               Node<H> *succ = minimo(check->getRight());
               H temp = succ->getData();
               remove(temp);
               check->setData(temp);
            }
            else
            {
               Node<H> *parent = check->getFather();
               Node<H> *child = check->getLeft();
               if(!child)
                  child = check->getRight();
               if(parent)
               {
                  if(value > parent->getData())
                     parent->setRight(child);
                  else
                     parent->setLeft(child);
               }
               else
                  root = child;
               if(child)
                  child->setFather(parent);
               delete check;
               counter--;
            }
         }
      }

      void preOrder(ostream &output)
      {
         _preOrder(root, output);
      }

      BST<H> * getNext()
      {
         return next;
      }

      void setNext(BST<H> *ptr)
      {
         next = ptr;
      }

      int getCounter()
      {
         return counter;
      }

   private:
      Node<H> *root;
      BST<H> *next;
      int counter;

      Node<H> * search(H value)
      {
         Node<H> *check = root;
         while(check && check->getData() != value)
            if(value > check->getData())
               check = check->getRight();
            else
               check = check->getLeft();
         return check;
      }

      Node<H> * minimo(Node<H> *check)
      {
         while(check->getLeft())
            check = check->getLeft();
         return check;
      }

      void _preOrder(Node<H> *check, ostream &output)
      {
         if(check)
         {
            output << check->getData() << " ";
            _preOrder(check->getLeft(), output);
            _preOrder(check->getRight(), output);
         }
      }
};

template<typename H>
class LoT
{
   public:
      LoT(int num)
      {
         k = num;
         head = NULL;
      }

      void insert(H value)
      {
         if(!head)
            head = new BST<H>(value);
         else if(head->getCounter() == k)
         {
            BST<H> *newBST = new BST<H>(value);
            newBST->setNext(head);
            head = newBST;
         }
         else
            head->insert(value);
      }

      void remove(H value)
      {
         BST<H> *check = head;
         BST<H> *prev = NULL;
         while(check)
         {
            check->remove(value);
            if(check->getCounter() == 0)
            {
               if(!prev)
                  head = head->getNext();
               else
                  prev->setNext(check->getNext());
               BST<H> *temp = check;
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
         BST<H> *check = head;
         while(check)
         {
            check->preOrder(output);
            check = check->getNext();
         }
         output << endl;
      }

   private:
      BST<H> *head;
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

      LoT<double> lot(k);

      string operazione;
      do
      {
         in >> operazione;

         if(operazione == "ins")
         {
            double valore;
            in >> valore;
            lot.insert(valore);
         }
         else if(operazione == "canc")
         {
            double valore;
            in >> valore;
            lot.remove(valore);
         }
      }
      while(operazione != "#");

      lot.print(out);
   }

   return 0;
}
