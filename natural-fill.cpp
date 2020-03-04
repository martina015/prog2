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

      void naturalFill(H array[])
      {
         int i = 0;
         _naturalFill(root, array, i);
      }

      void postOrder(ostream &output)
      {
         _postOrder(root, output);
         output << endl;
      }

   private:
      Node<H> *root;

      void _naturalFill(Node<H> *check, H array[], int &i)
      {
         if(check)
         {
            _naturalFill(check->getLeft(), array, i);
            check->setData(array[i++]);
            _naturalFill(check->getRight(), array, i);
         }
      }

      void _postOrder(Node<H> *check, ostream &output)
      {
         if(check)
         {
            _postOrder(check->getLeft(), output);
            _postOrder(check->getRight(), output);
            output << check->getData() << " ";
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

      BST<double> tree;

      for(int i = 0; i < n; i++)
      {
         double valore;
         in >> valore;
         tree.insert(valore);
      }

      double array[n];
      for(int j = 0; j < n; j++)
         in >> array[j];

      tree.naturalFill(array);

      tree.postOrder(out);
   }

   return 0;
}
