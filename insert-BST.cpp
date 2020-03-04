#include <fstream>

using namespace std;

template<typename H>
class Node
{
   public:
      Node(H element)
      {
         data = element;
         left = right = NULL;
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

   private:
      H data;
      Node<H> *left;
      Node<H> *right;
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
            if(value > prev->getData())
               prev->setRight(newNode);
            else
               prev->setLeft(newNode);
         }
      }

      void preOrder(ostream &output)
      {
         _preOrder(root, output);
         output << endl;
      }

      void inOrder(ostream &output)
      {
         _inOrder(root, output);
         output << endl;
      }

      void postOrder(ostream &output)
      {
         _postOrder(root, output);
         output << endl;
      }

   private:
      Node<H> *root;

      void _preOrder(Node<H> *check, ostream &output)
      {
         if(check)
         {
            output << check->getData() << " ";
            _preOrder(check->getLeft(), output);
            _preOrder(check->getRight(), output);
         }
      }

      void _inOrder(Node<H> *check, ostream &output)
      {
         if(check)
         {
            _inOrder(check->getLeft(), output);
            output << check->getData() << " ";
            _inOrder(check->getRight(), output);
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

template<typename H>
void manager(istream &in, ostream &out, H valore)
{
   BST<H> tree;

   int n;
   in >> n;

   string stampa;
   in >> stampa;

   for(int i = 0; i < n; i++)
   {
      in >> valore;
      tree.insert(valore);
   }

   if(stampa == "preorder")
      tree.preOrder(out);
   else if(stampa == "inorder")
      tree.inOrder(out);
   else
      tree.postOrder(out);
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
