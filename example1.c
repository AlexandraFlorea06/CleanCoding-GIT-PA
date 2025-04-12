/*Determinati daca exista sau nu drum direct intre doua restaurante dintr-o retea de tip graf*/

#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int data;
    struct Node *next;
} NODE;


typedef struct Graph {
    int vertexCount;
    int *visited;
    struct Node **AdjList;
} GRAPH;

typedef struct Stack {
    int top;
    int capacity;
    int *array;
} STACK;

NODE *create_node(int nodeValue) {
    NODE *NewNode = malloc(sizeof(NODE));
    NewNode->data = nodeValue;
    NewNode->next = NULL;
    return NewNode;
}

void add_edge(GRAPH *graph, int src, int dest) {
    NODE *NewNode = create_node(dest);
    NewNode->next = graph->AdjList[src];
    graph->AdjList[src] = NewNode;
    NewNode = create_node(src);
    NewNode->next = graph->AdjList[dest];
    graph->AdjList[dest] = NewNode;
}

GRAPH *create_graph(int vertex) {
    int i;
    GRAPH *graph = malloc(sizeof(GRAPH));
    graph->vertexCount = vertex;
    graph->AdjList = malloc(vertex * sizeof(NODE *));
    graph->visited = malloc(sizeof(int) * vertex);

    for (int i = 0; i < vertex; i++) {
        graph->AdjList[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

STACK *create_stack(int capacity) {
    STACK *stack = malloc(sizeof(STACK));
    stack->array = malloc(capacity * sizeof(int));
    stack->top = -1;
    stack->capacity = capacity;

    return stack;
}

void push(int value, STACK *stack) {
    if (stack->top + 1 < stack->capacity) {
        stack->top = stack->top + 1;
        stack->array[stack->top] = value;
    }
}

void DFS(GRAPH *graph, STACK *stack, int v_nr) {
    NODE *adj_list = graph->AdjList[v_nr];
    NODE *aux = adj_list;
    graph->visited[v_nr] = 1;
    push(v_nr, stack);
    while (aux != NULL) {
        int neighbor = aux->data;
        if (graph->visited[neighbor] == 0)
            DFS(graph, stack, neighbor);
        aux = aux->next;
    }
}

void insert_edges(GRAPH *graph, int edge_count, int vertex_count) {
    int src, dest, i;
    printf("adauga %d munchii (de la 0 la %d)\n", edge_count, vertex_count - 1);
    for (i = 0; i < edge_count; i++) {
        scanf("%d%d", &src, &dest);
        add_edge(graph, src, dest);
    }
}

void wipe(GRAPH *graph, int vertex_count) {
    for (int i = 0; i < vertex_count; i++) {
        graph->visited[i] = 0;
    }
}

void CanReachPath(GRAPH *g, int vertex_count, STACK *stack1, STACK *stack2) // 0 sau 1 daca poate fi sau nu ajuns
{
    int start, end;
    printf("Introduceti nodul de start: ");
    scanf("%d", &start);
    printf("Introduceti nodul final: ");
    scanf("%d", &end);
    stack1->top = -1;
    for (int i = 0; i < vertex_count; i++)
        g->visited[i] = 0;
    DFS(g, stack1, start);
    if (g->visited[end])printf("Exista drum intre %d si %d", start, end);
    else printf("Nu exista drum intre %d si %d", start, end);
}


int main() {
    int vertex_count;
    int edge_count;

    printf("Cate noduri are graful?\n");
    scanf("%d", &vertex_count);

    printf("Cate muchii are graful?\n");
    scanf("%d", &edge_count);

    GRAPH *graph = create_graph(vertex_count);
    STACK *stack1 = create_stack(2 * vertex_count);
    STACK *stack2 = create_stack(2 * vertex_count);

    insert_edges(graph, edge_count, vertex_count);

    CanReachPath(graph, vertex_count, stack1, stack2);
    return 0;
}
