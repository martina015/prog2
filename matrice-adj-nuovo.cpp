#include <fstream>

using namespace std;

template<typename H>
class Grafo
{
   public:
      Grafo(int n, int a)
      {
         nodi = n;
         archi = a;

         nodo = new H[nodi];

         adj = new H*[nodi];
         for(int i = 0; i < nodi; i++)
         {
            adj[i] = new H[nodi];
            for(int j = 0; j < nodi; j++)
               adj[i][j] = 0;
         }
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
            int b = findIndex(nodoB);

            adj[a][b] = 1;   
         }
      }

      void stampa(ostream &out)
      {
         for(int i = 0; i < nodi; i++)
         {
            out << "(" << nodo[i];
            for(int j = 0; j < nodi; j++)
               if(adj[i][j])
                  out << " " << nodo[j];
            out << ") ";
         }
         out << endl;
      }

   private:
      H *nodo;
      H **adj;
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
