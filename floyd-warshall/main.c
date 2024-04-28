#include <stdio.h>

#define INF 100
#define V 4

void print_graph(int graph[V][V], int i) {
	printf("A%d = \n", i);

        for (int l = 0; l < V; l++) {
                for (int m = 0; m < V; m++) {
                        printf("%d ", graph[l][m]);
		}
                printf("\n");
        }
	printf("\n");
}

void floyd_warshall(int graph[V][V]) {

	int i;

	for (i = 0; i < V; i++) {

		print_graph(graph, i);

		for (int l = 0; l < V; l++) {
                        for (int m = 0; m < V; m++) {
                                if (graph[l][i] + graph[i][m] < graph[l][m]) {
					graph[l][m] = graph[l][i] + graph[i][m];
				}
                        }
		}
	}

	print_graph(graph, i);

}

int main() {
	int graph[4][4] = {
		{0, 3, INF, 5},
		{2, 0, INF, 4},
		{INF, 1, 0, INF},
		{INF, INF, 2, 0}
	};
	floyd_warshall(graph);
	return 0;
}
