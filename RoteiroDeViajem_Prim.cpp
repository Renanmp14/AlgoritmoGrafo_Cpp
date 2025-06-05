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
                                                   
    void adicionarAresta(string origem, string destino, int peso) //adicionar as arestas, e aproveitar para fazer a conexão de volta
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

    //Exibe como as conexões entre as cidades ficarão
    void exibirConexoes(){
    for (const pair<const string, vector<pair<string,int>>>& item : grafo){
        const string& cidade = item.first;
        const vector<pair<string,int>>& conexoes = item.second;

        cout << cidade << " -> ";
        for (const pair<string,int>& conexao : conexoes){
            cout << conexao.first << " (" << conexao.second << " km) ";
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