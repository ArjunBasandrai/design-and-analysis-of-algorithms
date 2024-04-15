#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node {
    char data;
    int freq;
    struct node *left, *right;
};

typedef struct {
    struct node **arr;
    int size;
    int capacity;
} min_heap;

struct node *new_node(char data, int freq) {
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;
    return temp;
}

void free_node(struct node *n) {
    if (n == NULL) return;
    free_node(n->left);
    free_node(n->right);
    free(n);
}

min_heap *create_min_heap(int capacity) {
    min_heap *temp = (min_heap *)malloc(sizeof(min_heap));
    temp->size = 0;
    temp->capacity = capacity;
    temp->arr = (struct node **)malloc(temp->capacity * sizeof(struct node *));
    return temp;
}

void free_min_heap(min_heap *h) {
    for (int i = 0; i < h->size; i++) {
        free_node(h->arr[i]);
    }
    free(h->arr);
    free(h);
}

void swap_node(struct node **a, struct node **b) {
    struct node *temp = *a;
    *a = *b;
    *b = temp;
}

void min_heapify(min_heap *h, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < h->size && h->arr[left]->freq < h->arr[smallest]->freq) {
        smallest = left;
    }

    if (right < h->size && h->arr[right]->freq < h->arr[smallest]->freq) {
        smallest = right;
    }

    if (smallest != i) {
        swap_node(&h->arr[i], &h->arr[smallest]);
        min_heapify(h, smallest);
    }
}

int is_size_one(min_heap *h) {
    return h->size == 1;
}

int is_leaf(struct node *n) {
    return !(n->left) && !(n->right);
}

struct node *extract_min(min_heap *h) {
    struct node *temp = h->arr[0];
    --h->size;
    h->arr[0] = h->arr[h->size];
    min_heapify(h, 0);
    return temp;
}

void insert_min_heap(min_heap *h, struct node *n)  {
    ++h->size;
    int i = h->size - 1;
    while (i && n->freq < h->arr[(i - 1) / 2]->freq) {
        h->arr[i] = h->arr[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    h->arr[i] = n;
}

void build_min_heap(min_heap *h) {
    int n = h->size - 1;
    for (int i = (n - 1) / 2; i >= 0; i--) {
        min_heapify(h, i);
    }
}

void print_arr(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
    }
    printf("\n");
}

min_heap* create_and_build_min_heap(char data[], int freq[], int size) {
    min_heap *h = create_min_heap(size);
    for (int i = 0; i < size; i++) {
        h->arr[i] = new_node(data[i], freq[i]);
    }
    h->size = size;
    build_min_heap(h);
    return h;
}

struct node* build_huffman_tree(char data[], int freq[], int size) {
    struct node *left, *right, *top;
    min_heap *h = create_and_build_min_heap(data, freq, size);
    while (!is_size_one(h)) {
        left = extract_min(h);
        right = extract_min(h);
        top = new_node('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        insert_min_heap(h, top);
    }
    struct node *root = extract_min(h);
    free_min_heap(h);
    return root;
}

void print_codes(struct node *root, int arr[], int top) {
    if (root->left) {
        arr[top] = 0;
        print_codes(root->left, arr, top + 1);
    }
    if (root->right) {
        arr[top] = 1;
        print_codes(root->right, arr, top + 1);
    }
    if (is_leaf(root)) {
        printf("%c: ", root->data);
        print_arr(arr, top);
    }
}

void huffman_codes(char data[], int freq[], int size) {
    struct node *root = build_huffman_tree(data, freq, size);
    int arr[100], top = 0;
    print_codes(root, arr, top);
    free_node(root);
}

int main() {
    char data[7] = {'m', 'a', 'd', 'i', 's', 'n', ' '};
    int freq[7] = {3, 4, 2, 2, 1, 1, 3}; 

    int size = sizeof(data) / sizeof(data[0]);
    huffman_codes(data, freq, size);
    return 0;
}