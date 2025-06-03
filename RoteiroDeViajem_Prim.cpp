#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <string>

using namespace std;

string nomeArquivo = "caminhos.txt";

class Grafo
{
    public:
    map<string, vector<pair<string, int>>> grafo; //grafo representado por um mapa de strings para vetores de pares de strings e inteiros, ordenados por ordem alfabética
                                                   
    void adicionarAresta(string origem, string destino, int peso)
    {
        grafo[origem].push_back(make_pair(destino,peso));
        grafo[destino].push_back(make_pair(origem,peso));
    }

    void construirGrafo(string nomeArquivo)
    {
        ifstream arquivo(nomeArquivo);
        if (!arquivo.is_open()){
            cout << "Erro ao ler o arquivo" << endl;
            return;
        }

        string linha;
        while (getline(arquivo,linha)){
            stringstream ss(linha); //separa a linha em espaços permitindo sua leitura
            string cidade1, cidade2, distanciaStr;
            int distancia;

            //criar o segapador na leitura da linha
            getline(ss,cidade1,';');
            getline(ss,cidade2,';');
            getline(ss,distanciaStr,';');
            distancia = stoi(distanciaStr);

            adicionarAresta(cidade1,cidade2,distancia);
        }
        arquivo.close();
    }

    void exibirConexoes(){
        for (const auto& [cidade, conexoes] : grafo){
            cout << cidade << " -> ";
            for (const auto& [conexao, distancia] : conexoes){
                cout << conexao << " (" << distancia << " km) ";
        }
        cout << "\n"<<endl;
        }
    }
};

int main()
{
    Grafo grafo;
    grafo.construirGrafo(nomeArquivo);
    grafo.exibirConexoes();
    
    return 0;
}