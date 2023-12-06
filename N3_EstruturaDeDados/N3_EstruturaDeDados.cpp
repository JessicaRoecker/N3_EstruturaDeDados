#include <stdio.h>
#include <limits.h>

#define V 9

int minDistance(int dist[], int sptSet[]) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (sptSet[v] == 0 && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

void printPath(int parent[], int j) {
    // Caso base: quando atingimos o vértice de origem
    if (parent[j] == -1)
        return;

    printPath(parent, parent[j]);

    printf(" -> %d", j);
}

void printSolution(int dist[], int parent[], int n, int src, int dest) {
    printf("Vertice   Distancia do ponto A   Caminho\n");
    for (int i = 0; i < V; i++) {
        printf("%d \t\t %d \t\t\t\t %d", i, dist[i], src);
        printPath(parent, i);
        printf("\n");
    }

    // Imprimir o caminho do ponto A ao ponto B
    printf("\nCaminho do ponto A (%d) ao ponto B (%d): %d", src, dest, src);
    printPath(parent, dest);
    printf("\n");
}

void dijkstra(int graph[V][V], int src, int dest) {
    int dist[V];
    int sptSet[V];
    int parent[V];

    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = 0;
        parent[i] = -1;
    }

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet);

        sptSet[u] = 1;

        if (u == dest) {
            // Se chegamos ao destino, imprimimos a solução e interrompemos o algoritmo
            printSolution(dist, parent, V, src, dest);
            return;
        }

        for (int v = 0; v < V; v++) {
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }

    // Imprimir a solução
    printSolution(dist, parent, V, src, dest);
}

int main() {
    int graph[V][V] = {
        {0, 4, 0, 0, 0, 0, 0, 8, 0},
        {4, 0, 8, 0, 0, 0, 0, 11, 0},
        {0, 8, 0, 7, 0, 4, 0, 0, 2},
        {0, 0, 7, 0, 9, 14, 0, 0, 0},
        {0, 0, 0, 9, 0, 10, 0, 0, 0},
        {0, 0, 4, 14, 10, 0, 2, 0, 0},
        {0, 0, 0, 0, 0, 2, 0, 1, 6},
        {8, 11, 0, 0, 0, 0, 1, 0, 7},
        {0, 0, 2, 0, 0, 0, 6, 7, 0} };

    dijkstra(graph, 0, 8);  // Encontrar o menor caminho do ponto A (0) ao ponto B (8)

    return 0;
}
