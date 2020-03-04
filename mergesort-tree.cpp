#include <fstream>

using namespace std;

template<typename H>
class Node
{
   public:
      Node(H elements[], int n)
      {
         size = n;

         arrayIn = new H[size];
         arrayOut = new H[size];
         for(int i = 0; i < size; i++)
            arrayIn[i] = arrayOut[i] = elements[i];

         sort();

         right = left = father = NULL;
      }

      void printIn(ostream &output)
      {
         for(int i = 0; i < size; i++)
            output << arrayIn[i] << " ";
      }

      void printOut(ostream &output)
      {
         for(int i = 0; i < size; i++)
            output << arrayOut[i] << " ";
      }

      Node<H> * getRight()
      {
         return right;
      }

      void setRight(Node<H> *ptr)
      {
         right = ptr;
      }

      Node<H> * getLeft()
      {
         return left;
      }

      void setLeft(Node<H> *ptr)
      {
         left = ptr;
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
      H *arrayIn;
      H *arrayOut;
      int size;
      Node<H> *right;
      Node<H> *left;
      Node<H> *father;

      void sort()
      {
         for(int i = 1; i < size; i++)
         {
            int j = i;
            while(j > 0 && arrayOut[j] < arrayOut[j - 1])
            {
               H temp = arrayOut[j];
               arrayOut[j] = arrayOut[j - 1];
               arrayOut[j - 1] = temp;
               j--;
            }
         }
      }
};

template<typename H>
class MSTree
{
   public:
      MSTree(H array[], int n)
      {
         root = new Node<H>(array, n);
         divide(root, array, n);
      }

      void preOrder(ostream &output)
      {
         _preOrder(root, output);
         output << endl;
      }

   private:
      Node<H> *root;

      void divide(Node<H> *parent, H array[], int n)
      {
         if(n > 1)
         {
            int m = n / 2;

            Node<H> *newLeft = new Node<H>(array, m);
            parent->setLeft(newLeft);
            newLeft->setFather(parent);

            Node<H> *newRight = new Node<H>(array + m, n - m);
            parent->setRight(newRight);
            newRight->setFather(parent);

            divide(newLeft, array, m);
            divide(newRight, array + m, n - m);
         }
      }

      void _preOrder(Node<H> *check, ostream &output)
      {
         if(check)
         {
            output << "[ ";
            check->printIn(output);
            output << ": ";
            check->printOut(output);
            output << "] ";

            _preOrder(check->getLeft(), output);
            _preOrder(check->getRight(), output);
         }
      }
};

template<typename H>
void manager(istream &in, ostream &out, H valore)
{
   int n;
   in >> n;

   H array[n];
   for(int i = 0; i < n; i++)
      in >> array[i];

   MSTree<H> mst(array, n);

   mst.preOrder(out);
}

int main()
{
   ifstream in("input.txt");
   ofstream out("output.txt");

   for(int i = 0; i < 100; i++)
   {
      string tipo;
      in >> tipo;

      double numero;
      char lettera;

      if(tipo == "char")
         manager(in, out, lettera);
      else
         manager(in, out, numero);
   }

   return 0;
}
