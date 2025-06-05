#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <utility>
#include <functional>
#include <algorithm>
#include <map>

using namespace std;

class Grafo
{
private:
    vector<vector<pair<int, int>>> adj;
    map<string, int> nomeParaIndice;
    vector<string> indiceParaNome;

public:
    Grafo() {}

    void insere_vertice(const string &nome)
    {
        if (nomeParaIndice.find(nome) == nomeParaIndice.end())
        {
            nomeParaIndice[nome] = adj.size();
            indiceParaNome.push_back(nome);
            adj.emplace_back(); // adiciona nova lista de adjacência
        }
    }

    void insere_aresta(const string &origem, const string &destino, int peso)
    {
        insere_vertice(origem);
        insere_vertice(destino);

        int u = nomeParaIndice[origem];
        int v = nomeParaIndice[destino];

        if (!tem_aresta(u, v))
        {
            adj[u].push_back({peso, v});
            adj[v].push_back({peso, u});
        }
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

    // void imprime_arestas() const
    // {
    //     for (int u = 0; u < adj.size(); ++u)
    //     {
    //         for (const auto &[peso, v] : adj[u])
    //         {
    //             if (u < v)
    //                 cout << "{" << indiceParaNome[u] << ", " << indiceParaNome[v] << "} peso: " << peso << endl;
    //         }
    //     }
    // }

    void algoritmoDePrim(const string &origemStr)
    {
        if (nomeParaIndice.find(origemStr) == nomeParaIndice.end())
        {
            cout << "Vértice de origem não encontrado." << endl;
            return;
        }

        int origem = nomeParaIndice[origemStr];
        vector<bool> visitados(adj.size(), false);
        vector<tuple<int, int, int>> arvoreMinima;
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> minHeap;

        visitados[origem] = true;
        for (auto [peso, vizinho] : adj[origem])
        {
            minHeap.push({peso, vizinho, origem});
        }

        while (!minHeap.empty())
        {
            auto [peso, verticeAtual, pai] = minHeap.top();
            minHeap.pop();

            if (visitados[verticeAtual])
                continue;

            visitados[verticeAtual] = true;
            arvoreMinima.push_back({pai, verticeAtual, peso});

            for (auto [p, vizinho] : adj[verticeAtual])
            {
                if (!visitados[vizinho])
                {
                    minHeap.push({p, vizinho, verticeAtual});
                }
            }
        }

        imprimeArvore(arvoreMinima);
    }

    void imprimeArvore(const vector<tuple<int, int, int>> &arvoreMinima)
    {
        int total = 0;
        cout << "\nTempo de Contaminação: \n";
        for (const auto &[pai, filho, peso] : arvoreMinima)
        {
            cout << indiceParaNome[pai] << " -> " << indiceParaNome[filho] << " (" << peso << " minutos)\n";
            total += peso;
        }
        cout << "Tempo de contaminação Total:  " << total << " minutos" <<endl;
    }

    void carregarArquivo(const string &nomeArquivo)
    {
        ifstream arquivo(nomeArquivo);
        string linha;

        while (getline(arquivo, linha))
        {
            stringstream ss(linha);
            string origem, destino, pesoStr;
            getline(ss, origem, ';');
            getline(ss, destino, ';');
            getline(ss, pesoStr);

            int peso = stoi(pesoStr);
            insere_aresta(origem, destino, peso);
        }
    }

    void listarVertices()
    {
        //cout << "Vértices disponíveis:\n";
        for (const auto &[nome, idx] : nomeParaIndice)
        {
            cout << "- " << nome << endl;
        }
    }
};

int main()
{
    Grafo g;

    g.carregarArquivo("arestas.txt");

    cout << "\nTipos Sangueneos:\n" << endl;
    //g.imprime_arestas();

    g.listarVertices();

    string origem;
    cout << "Informe o Tipo Sanguineo de inicio: ";
    cin >> origem;

    g.algoritmoDePrim(origem);
}
