# Árvore Geradora Mínima com Algoritmo de Prim

Este projeto implementa um grafo não direcionado e ponderado em C++ e utiliza o **algoritmo de Prim** para encontrar a **Árvore Geradora Mínima (MST - Minimum Spanning Tree)**.

## 📌 Descrição

- O grafo é representado por uma lista de adjacência.
- As arestas possuem pesos.
- O algoritmo de Prim é utilizado para encontrar a MST a partir de um vértice de origem fornecido pelo usuário.
- A estrutura de dados `priority_queue` (min-heap) é usada para garantir que a próxima aresta de menor peso seja escolhida eficientemente.

## 📂 Estrutura do Projeto

- `main.cpp` — Código-fonte principal com definição da classe `Grafo` e execução do algoritmo de Prim.