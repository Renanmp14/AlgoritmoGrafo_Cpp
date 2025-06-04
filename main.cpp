#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <functional>
#include <algorithm>

using namespace std;

class Grafo
{
private:
    // Cada par representa (pes, vizinho)
    vector<vector<pair<int, int>>> adj;

public:
    Grafo(int n)
    {
        adj.resize(n);
    }

    void insere_aresta(int u, int v, int peso = 1)
    {
        if (!tem_aresta(u, v))
        {
            adj[u].push_back({peso, v});
            adj[v].push_back({peso, u});
        }
    }

    void remove_aresta(int u, int v)
    {
        if (!tem_aresta(u, v))
            return;

        adj[u].erase(remove_if(adj[u].begin(), adj[u].end(),
                               [v](const pair<int, int> &par)
                               { return par.second == v; }),
                     adj[u].end());

        adj[v].erase(remove_if(adj[v].begin(), adj[v].end(),
                               [u](const pair<int, int> &par)
                               { return par.second == u; }),
                     adj[v].end());
    }

    bool tem_aresta(int u, int v)
    {
        for (auto &[peso, vizinho] : adj[u])
        {
            if (vizinho == v)
                return true;
        }

        return false;
    }

    void imprime_arestas() const
    {
        for (int u = 0; u < adj.size(); ++u)
        {
            for (const auto &[peso, v] : adj[u])
            {
                if (u < v) // Evita imprimir duplicadas
                    cout << "{" << u << ", " << v << "} peso: " << peso << endl;
            }
        }
    }

    void algoritmoDePrim(int origem)
    {
        /*         // Cada par representa (peso, vizinho)
                vector<vector<pair<int, int>>> adj; */

        vector<bool> visitados(adj.size(), false);

        // Arvore vai armazenar somente o arco e o peso. Não tera o vertice visitado (papel do vector<bool> visitados)
        // Arvore: cada par é (pai, filho, peso) Essa estrutura é necessária p poder saber os caminhos que foram feitos
        vector<tuple<int, int, int>> arvoreMinima;

        // Min-heap: (peso, vertice atual, pai)
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> minHeap;

        visitados[origem] = true;

        // Adiciona todos os viznhos do vertice origem
        for (auto [peso, vizinho] : adj[origem])
        {
            minHeap.push({peso, vizinho, origem});
        }

        while (!minHeap.empty())
        {

            auto [peso, verticeAtual, pai] = minHeap.top();
            minHeap.pop();

            if (visitados[verticeAtual] == true)
            {
                continue;
            }

            visitados[verticeAtual] = true;
            arvoreMinima.push_back({pai, verticeAtual, peso});

            for (auto [peso, novoVizinho] : adj[verticeAtual])
            {
                if (visitados[novoVizinho] == false)
                {
                    minHeap.push({peso, novoVizinho, verticeAtual});
                }
            }
        }

        imprimeArvore(arvoreMinima);
    }

    void imprimeArvore(const vector<tuple<int, int, int>> &arvoreMinima)
    {
        int total = 0;
        cout << "Árvore Geradora Mínima:\n";
        for (const auto &[pai, filho, peso] : arvoreMinima)
        {
            cout << pai << " -> " << filho << " (peso " << peso << ")\n";
            total += peso;
        }
        cout << "Peso total da árvore: " << total << endl;
    }
};

int main()
{
    Grafo g(7);

    g.insere_aresta(0, 1, 7);
    g.insere_aresta(0, 2, 8);
    g.insere_aresta(1, 2, 3);
    g.insere_aresta(1, 3, 5);
    g.insere_aresta(2, 3, 6);
    g.insere_aresta(2, 4, 3);
    g.insere_aresta(3, 4, 2);
    g.insere_aresta(3, 5, 4);
    g.insere_aresta(4, 5, 2);

    cout << "\nImprimindo arestas:" << endl;
    g.imprime_arestas();

    int origem;

    cout << "Informe o vértice inicial (de 0 a 5): ";
    cin >> origem;

    g.algoritmoDePrim(origem);
}
