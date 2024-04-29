#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_V 26

typedef struct edge {
    int s, d;
    struct edge* next;
} edge;

edge* head = NULL;

void parse_and_fill(char input[], int graph[][MAX_V]) {
    char source, destination;
    int weight;
    sscanf(input, "%c-%c %d", &source, &destination, &weight);
    int source_index = source - 'A';
    int destination_index = destination - 'A';
    graph[source_index][destination_index] = weight;
}

void insert_edge(int src, int des) {
    edge* ptr = (edge*)malloc(sizeof(edge));
    ptr->s = src;
    ptr->d = des;
    ptr->next = NULL;
    if (head == NULL) {
        head = ptr;
    } else {
        edge* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = ptr;
    }
}

int main() {
    int graph[MAX_V][MAX_V] = {0};
    char input[] = "A-B 6\nA-C 4\nA-D 5\nC-B -2\nD-C -2\nB-E -1\nC-E 3\nD-F -1\nE-F 3";

    char *line = strtok(input, "\n");
    while (line != NULL) {
        parse_and_fill(line, graph);
        line = strtok(NULL, "\n");
    }

    int vertices = 6;
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            if (graph[i][j] != 0) {
                insert_edge(i, j);
            }
        }
    }

    int shortest_path[MAX_V];

    for (int i = 0; i < vertices; i++) {
        shortest_path[i] = INT_MAX;
    }

    shortest_path[0] = 0;
    for (int i = 1; i < vertices; i++) {
        edge* temp = head;
        while (temp != NULL) {
            if (shortest_path[temp->s] + graph[temp->s][temp->d] < shortest_path[temp->d] && shortest_path[temp->s] != INT_MAX) {
                shortest_path[temp->d] = shortest_path[temp->s] + graph[temp->s][temp->d];
            }
            temp = temp->next;
        }
    }

    for (int i = 0; i < vertices; i++) {
        if (shortest_path[i] == INT_MAX) {
            printf("Node %c is unreachable\n", i + 'A');
            continue;
        }
        printf("Shortest path from A to %c is %d\n", i + 'A', shortest_path[i]);
    }

    edge *curr = head;
    while (curr != NULL) {
        edge *temp = curr;
        curr = curr->next;
        free(temp);
    }

    return 0;
}
