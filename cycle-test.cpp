#include <fstream>

#define WHITE 0
#define GRAY 1
#define BLACK 2

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
         color = new int[nodi];
         for(int i = 0; i < nodi; i++)
         {
            adj[i] = new H[nodi];
            color[i] = WHITE;
            for(int j = 0; j < nodi; j++)
               adj[i][j] = 0;
         }

         cicli = 0;
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

      void dfs()
      {
         for(int i = 0; i < nodi; i++)
            if(color[i] == WHITE)
               _dfs(i);
      }

      void stampa(ostream &out)
      {
         out << cicli << endl;
      }

   private:
      int nodi;
      int archi;
      H *nodo;
      H **adj;
      int *color;
      int cicli;

      int findIndex(H value)
      {
         int i = 0;
         while(nodo[i] != value)
            i++;
         return i;
      }

      void _dfs(int i)
      {
         color[i] = GRAY;

         for(int j = 0; j < nodi; j++)
            if(adj[i][j])
            {
               if(color[j] == WHITE)
                  _dfs(j);
               else if(color[j] == GRAY)
                  cicli++;
            } 

         color[i] = BLACK;
      }
};

template<typename H>
void manager(istream &in, ostream &out, int nodi, int archi, H valore)
{
   Grafo<H> gf(nodi, archi);

   gf.init(in);

   gf.dfs();

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
