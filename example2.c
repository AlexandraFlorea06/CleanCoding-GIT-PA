/*parcurgerge  graf cu DFS/BFS*/

#include <stdlib.h>
#include <stdio.h>

//structura pentru un nod
typedef struct Node {
    int data;
    struct Node *next;
} NODE;

//structura pentru graf
typedef struct Graph {
    int vertices;
    int *visited;
    struct Node **adjacency_lists;
} GRAPH;

//crearea unui nod nou
NODE *create_node(int value) {
    NODE *new_node = malloc(sizeof(NODE));
    new_node->data = value;
    new_node->next = NULL;
    return new_node;
}

//crearea unui graf gol cu un nr de varfuri
GRAPH *create_graph(int vertices) {
    int i;
    GRAPH *graph = malloc(sizeof(GRAPH));
    graph->vertices = vertices;
    graph->adjacency_lists = malloc(vertices * sizeof(NODE *));
    graph->visited = malloc(sizeof(int) * vertices);
    for (int i = 0; i < vertices; i++) {
        graph->adjacency_lists[i] = NULL; //nu are vecini initial
        graph->visited[i] = 0; //niciun varf nu a fost vizitat
    }
    return graph;
}

//adaugarea unei muchii intre 2 noduri
void add_edge(GRAPH *graph, int src, int dest) {
    NODE *new_node = create_node(dest);

    new_node->next = graph->adjacency_lists[src];
    graph->adjacency_lists[src] = new_node;

    new_node = create_node(src);

    new_node->next = graph->adjacency_lists[dest];
    graph->adjacency_lists[dest] = new_node;
}

//introducerea muchiilor in graf
void insert_edges(int nr_of_vertices, int nr_of_edges, GRAPH *graph) {
    int src, dest, i;
    printf("adauga %d muchii (de la 1 la %d)\n", nr_of_edges, nr_of_vertices);
    for (i = 0; i < nr_of_edges; i++) {
        scanf("%d%d", &src, &dest);
        add_edge(graph, src - 1, dest - 1);
    }
}

//verificare goala coada goala
int is_empty(NODE *queue) {
    return queue == NULL;
}

//adaugare element in coada
void enqueue(NODE **queue, int data) {
    NODE *new_node = create_node(data);

    if (is_empty(*queue))
        *queue = new_node;
    else {
        NODE *temp = *queue;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

//scoate primul element din coada
int dequeue(NODE **queue) {
    int data = (*queue)->data;
    NODE *temp = *queue;
    *queue = (*queue)->next;
    return data;
}

//afisare lista de adiacenta
void print_graph(GRAPH *graph) {
    int i;
    for (i = 0; i < graph->vertices; i++) {
        NODE *temp = graph->adjacency_lists[i];

        while (temp) {
            printf("%d ", temp->data);
            temp = temp->next;
        }
        printf("\n");
    }
}

//afisare coada
void print_queue(NODE *queue) {
    while (queue != NULL) {
        printf("%d ", queue->data);
        queue = queue->next;
    }
}

//resetare vector de vizite (pentru rularea BFS dupa DSF)
void wipe_visited_list(GRAPH *graph, int nr_of_vertices) {
    for (int i = 0; i < nr_of_vertices; i++) {
        graph->visited[i] = 0;
    }
}

// parcurgeri
void DFS(GRAPH *graph, int vertex_nr) {
    NODE *adj_list = graph->adjacency_lists[vertex_nr];
    NODE *temp = adj_list;

    graph->visited[vertex_nr] = 1;
    printf("%d", vertex_nr + 1);

    while (temp != NULL) {
        int connected_vertex = temp->data;
        if (graph->visited[connected_vertex] == 0) {
            printf("->");
            DFS(graph, connected_vertex);
        }
        temp = temp->next;
    }
}

void BFS(GRAPH *graph, int start) {
    NODE *queue = NULL;

    graph->visited[start] = 1;
    enqueue(&queue, start);
    int first = 1;
    while (!is_empty(queue)) {
        int current = dequeue(&queue);
        if (first) {
             printf("%d", current + 1);
            first = 0;
        }
        else {
            printf("->%d", current+1);
        }

        NODE *temp = graph->adjacency_lists[current];

        while (temp) {
            int adj_vertex = temp->data;

            if (graph->visited[adj_vertex] == 0) {
                graph->visited[adj_vertex] = 1;
                enqueue(&queue, adj_vertex);
            }
            temp = temp->next;
        }
    }
}

int main() {
    int nr_of_vertices, nr_of_edges, i, starting_vertex;
    printf("cate noduri are graful? "); //introducere nr noduri
    scanf("%d", &nr_of_vertices);
    printf("cate muchii are graful? "); //introducere muchii
    scanf("%d", &nr_of_edges);
    GRAPH *graph = create_graph(nr_of_vertices);
    insert_edges(nr_of_vertices, nr_of_edges, graph);
    printf("\nReprezentarea grafului:\n");
    print_graph(graph);
    printf("de unde plecam in DFS? ");
    scanf("%d", &starting_vertex);
    starting_vertex = starting_vertex - 1;
    printf("parcurgere cu DFS: ");
    DFS(graph, starting_vertex);
    wipe_visited_list(graph, nr_of_vertices); //resetare vizite
    printf("\n");
    printf("de unde plecam in BFS? ");
    scanf("%d", &starting_vertex);
    starting_vertex = starting_vertex - 1;
    printf("parcurgere cu BFS: ");
    BFS(graph, starting_vertex);
    return 0;
}
