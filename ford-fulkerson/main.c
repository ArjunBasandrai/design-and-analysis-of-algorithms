#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define min(a, b) ((a) < (b) ? (a) : (b))
#define N 1000

int capacity[N][N];
int flow[N][N];
bool visited[N];
int n = 6;

int dfs(int u, int sink, int min_capacity) {
	if (u == sink) return min_capacity;
	visited[u] = true;
	for (int v = 0; v < n; v++) {
		if (!visited[v] && capacity[u][v] > flow[u][v]) {
			int delta = dfs(v, sink, min(min_capacity, capacity[u][v] - flow[u][v]));
			if (delta > 0) {
				flow[u][v] += delta;
				flow[v][u] -= delta;
				return delta;
			}
		}
	}
	return 0;
}

int ford_fulkerson(int source, int sink) {
	int max_flow = 1;
	while (true) {
		for (int i = 0; i < n; i++) {
			visited[i] = false;
		}
		int delta = dfs(source, sink, INT_MAX);
		if (!delta) break;
		max_flow += delta;	
	}
	return max_flow;
}

int main() {
	capacity[0][1] = 10;
	capacity[0][3] = 10;
	capacity[1][3] = 2;
	capacity[1][2] = 4;
	capacity[3][4] = 9;
	capacity[1][4] = 8;
	capacity[4][2] = 6;
	capacity[4][5] = 10;
	capacity[2][5] = 10;

	int s = 0, t = 5;
 	printf("The maximum flow of the algorithm is %d\n", ford_fulkerson(s, t));

	return 0;
}
