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
      List()
      {
         head = NULL;
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
            while(check && value > check->getData())
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
      }

      void print(ostream &out)
      {
         Node<H> *check = head;
         while(check)
         {
            out << "," << check->getData();
            check = check->getNext();
         }
      }

   private:
      Node<H> *head;
};

template<typename H>
class Grafo
{
   public:
      Grafo(int n, int a)
      {
         nodi = n;
         archi = a;
         nodo = new H[nodi];
         adj = new List<H>[nodi];
      }

      void init(istream &in)
      {
         for(int i = 0; i < nodi; i++)
         {
            H valore;
            in >> valore;
            nodo[i] = valore;
         }

         for(int i = 1; i < nodi; i++)
         {
            int j = i;
            while(j > 0 && nodo[j] < nodo[j - 1])
            {
               H temp = nodo[j];
               nodo[j] = nodo[j - 1];
               nodo[j - 1] = temp;
               j--;
            }
         }

         for(int i = 0; i < archi; i++)
         {
            char parentesi;
            H nodoA;
            H nodoB;

            in >> parentesi;
            in >> nodoA;
//            in.ignore();
            in >> nodoB;
            in >> parentesi;

            int a = findIndex(nodoA);

            adj[a].insert(nodoB);
         }
      }

      void stampa(ostream &out)
      {
         for(int i = 0; i < nodi; i++)
         {
            out << "(" << nodo[i];
            adj[i].print(out);
            out << ") ";
         }
         out << endl;
      }

   private:
      H *nodo;
      List<H> *adj;
      int nodi;
      int archi;

      int findIndex(H value)
      {
         int i = 0;
         while(nodo[i] != value)
            i++;
         return i;
      }
};

template<typename H>
void manager(istream &in, ostream &out, int nodi, int archi, H valore)
{
   Grafo<H> gf(nodi, archi);

   gf.init(in);

   gf.stampa(out);
}

int main()
{
   ifstream in("input.txt");
   ofstream out("output.txt");

   for(int i = 0; i < 100; i++)
   {
      int nodi;
      int archi;
      in >> nodi >> archi;

      string tipo;
      in >> tipo;

      double numero;
      char lettera;

      if(tipo == "char")
         manager(in, out, nodi, archi, lettera);
      else
         manager(in, out, nodi, archi, numero);
   }

   return 0;
}
