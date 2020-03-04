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
      BST()
      {
         root = NULL;
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
      }

      void remove(H value)
      {
         Node<H> *check = search(value);
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
         }
      }

      void leaf(ostream &output)
      {
         output << _leaf(root) << endl;
      }

   private:
      Node<H> *root;

      Node<H> * search(H value)
      {
         Node<H> *check = root;
         while(check->getData() != value)
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

      int _leaf(Node<H> *check)
      {
         if(!check)
            return 0;
         else if(!check->getLeft() && !check->getRight())
            return 1;
         else
            return _leaf(check->getLeft()) + _leaf(check->getRight());
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

      BST<double> tree;

      for(int i = 0; i < n; i++)
      {
         char simbolo;
         in >> simbolo;

         if(simbolo == 'i')
         {
            in.ignore(3);
            double valore;
            in >> valore;
            tree.insert(valore);
         }
         else if(simbolo == 'c')
         {
            in.ignore(4);
            double valore;
            in >> valore;
            tree.remove(valore);
         }
      }

      tree.leaf(out);
   }

   return 0;
}
