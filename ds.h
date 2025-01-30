#ifndef data_structures_header
#define data_structures_header

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 20

typedef enum ContainerTypes {
	STRING,
	INT,
	FLOAT,
	GRAPHNODE
} ContainerTypes;

typedef struct ArrayList {
	int size;
	ContainerTypes type;
	void** items;
} ArrayList;

ArrayList list_init(size_t length, ContainerTypes type);
void list_append(ArrayList* list, void* value);
void list_pop(ArrayList* list, int index);
void list_insert(ArrayList* list, int index, void* value);
int list_contains(ArrayList* list, void* value);
void list_clear(ArrayList* list);
void print_list(ArrayList* list);

int eq(void* element1, void* element2, ContainerTypes type);
int gt(void* element1, void* element2, ContainerTypes type);
int lt(void* element1, void* element2, ContainerTypes type);
int ge(void* element1, void* element2, ContainerTypes type);
int le(void* element1, void* element2, ContainerTypes type);

void print_value(void* data, ContainerTypes type);

typedef struct Node {
	char* key;
	void* value;
	struct Node* next;
	struct Node* prev;
	ContainerTypes type;
} Node;

int isEmpty(Node* root);
int size(Node* root);
void print_nodes(Node* node);
void free_nodes(Node* node);

// Stack
void push(Node** stack, void* value, ContainerTypes type);
Node* pop(Node** stack);
void* peek(Node* stack);

// Queue
void enqueue(Node** queue, void* value, ContainerTypes type);
Node* dequeue(Node** queue);
void* view(Node* queue);

// Hashmap
typedef struct Hashmap {
	int size;
	size_t capacity;
	Node* items;
} Hashmap;

int hash(const char* key, size_t capacity);
Hashmap init_map(size_t capacity);
Node* get_map(Hashmap* map, const char* key);
void update_map(Hashmap* map, const char* key, void* value, ContainerTypes type);
void delete_map(Hashmap* map, const char* key);
void print_map(Hashmap* map);
void print_map_layout(Hashmap* map);
void clear_map(Hashmap* map);

// Graph
typedef struct Connection {
	unsigned int weight;
	void* node;
} Connection;
typedef struct GraphNode {
	void* value;
	ContainerTypes type;
	size_t num_conn;
	Connection* connections;
} GraphNode;
typedef struct Graph {
	size_t size;
	GraphNode** nodes;
} Graph;

Graph init_graph();
int indexof_graph(Graph* graph, void* value);
GraphNode* update_graph(Graph* graph, void* value, ContainerTypes type);
void make_connection(Graph* graph, void* start, void* end, ContainerTypes type, unsigned int weight);
void make_two_way_connection(Graph* graph, void* first, void* second, ContainerTypes type, unsigned int weight);
void print_graph(Graph* graph);
void print_graph_items(Graph* graph);
void free_graph(Graph* graph);

#endif
