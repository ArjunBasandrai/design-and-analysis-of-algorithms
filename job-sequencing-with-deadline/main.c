#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int id;
    int deadline;
    int time;
    int profit;
} Job;

typedef struct {
    int *selected;
    int id;
    int u;
    int c;
} node;

node queue[1000];
int front = 0, rear = 0;
int upper = INT_MAX;

void enqueue(node *curr) {
    queue[rear++] = *curr;
}

node dequeue() {
    return queue[front++];
}

void job_sequencing(Job *jobs, node curr, int n) {
    for (int i = curr.id; i < n; i++) {
        if (curr.selected[i] == 0) {
            node next;
            next.id = i + 1;
            next.selected = (int *)malloc(n * sizeof(int));
            for (int j = 0; j < n; j++) {
                next.selected[j] = curr.selected[j];
            }
            next.selected[i] = 1;
            enqueue(&next);
        }
    }
    int u = 0, c = 0, t = 0, d = 0;
    for (int i = 0; i < n; i++) {
        if (curr.selected[i] != 0) {
            u += jobs[i].profit;
            t += jobs[i].time;
            if (jobs[i].deadline > d) {
                d = jobs[i].deadline;
            }
        }
    }
    for (int i = 0; i < curr.id; i++) {
        if (curr.selected[i] != 0) {
            c += jobs[i].profit;
        }
    }
    curr.c = c;
    curr.u = u;
    if (c > upper || t > d) {
        free(curr.selected);
        return;
    }
    if (u < upper) {
        upper = u;
    }
    if (curr.id == n) {
        printf("Selected jobs: ");
        for (int i = 0; i < n; i++) {
            if (curr.selected[i] != 0) {
                printf("%d ", i + 1);
            }
        }
        printf("\n");
        printf("Profit: %d\n", u);
        free(curr.selected);
        return;
    }
    job_sequencing(jobs, dequeue(), n);
}

int main() {
    int n;

    printf("Enter the number of jobs: ");
    scanf("%d", &n);

    Job *jobs = (Job *)malloc(n * sizeof(Job));

    for (int i = 0; i < n; i++) {
        printf("Enter the deadline, time and profit of job %d: ", i + 1);
        scanf("%d %d %d", &jobs[i].deadline, &jobs[i].time, &jobs[i].profit);
        jobs[i].id = i + 1;
    }

    node root;
    root.id = 0;
    root.selected = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        root.selected[i] = 0;
    }
    root.u = 0;
    root.c = 0;

    job_sequencing(jobs, root, n);

    free(jobs);
    return 0;
}
