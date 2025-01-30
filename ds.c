#include "ds.h"

// Helpers
void* alloc(size_t length, ContainerTypes type) {
	switch(type) {
	case STRING:
		return calloc(length, sizeof(char*));
	case INT:
		return calloc(length, sizeof(int*));
	case FLOAT:
		return calloc(length, sizeof(float*));
	case GRAPHNODE:
		return calloc(length, sizeof(GraphNode*));
	}
}
void* resize(ArrayList *list) {
	switch(list->type) {
	case STRING:
		return realloc(list->items, list->size * sizeof(char*));
	case INT:
		return realloc(list->items, list->size * sizeof(int*));
	case FLOAT:
		return realloc(list->items, list->size * sizeof(float*));
	case GRAPHNODE:
		return realloc(list->items, list->size * sizeof(GraphNode*));
	}
}
void* set_data(void* data, ContainerTypes type) {
	void* result = NULL;
	switch (type) {
	case STRING:
		result = calloc(MAX_LENGTH, sizeof(char));
		memcpy(result, data, MAX_LENGTH);
		break;
	case INT:
		result = calloc(1, sizeof(int));
		memcpy(result, data, sizeof(int));
		break;
	case FLOAT:
		result = calloc(1, sizeof(float));
		memcpy(result, data, sizeof(float));
		break;
	case GRAPHNODE:
		result = calloc(1, sizeof(GraphNode));
		memcpy(result, data, sizeof(GraphNode));
		break;
	}

	return result;
}
void swap(void* destination, void* buffer, size_t size, size_t capacity) {
	void* temp = calloc(size, capacity);
	memcpy(temp, destination, capacity);
	memcpy(destination, buffer, capacity);
	memcpy(buffer, temp, capacity);

	free(temp);
}
void print_value(void* data, ContainerTypes type) {
	switch(type) {
		case STRING: {
			char* buffer = data;
			if (buffer == NULL) {
				printf("(NULL)");
			} else {
				printf("'%s'", buffer);
			}
			break;
		}
		case INT: {
			int* buffer = data;
			if (buffer == NULL) {
				printf("(NULL)");
			} else {
				printf("%d", *buffer);
			}
			break;
		}
		case FLOAT: {
			float* buffer = data;
			if (buffer == NULL) {
				printf("(NULL)");
			} else {
				printf("%g", *buffer);
			}
			break;
		}
		default:
			break;
	}
}

// List
ArrayList list_init(size_t length, ContainerTypes type) {
	ArrayList list;
	list.size = length;
	list.type = type;
	list.items = alloc(length, type);
	return list;
}
void list_append(ArrayList* list, void* value) {
	list->size++;
	list->items = resize(list);	
	list->items[list->size - 1] = set_data(value, list->type);
}
void list_pop(ArrayList* list, int index) {
	if (index >= list->size || index < 0) {
		printf("\n***ArrayList Error***\nCan't pop at index: %d\n", index);
		return;
	}

	size_t pop_index = index;
	free(list->items[index]);
	for (int i = index + 1; i < list->size; i++) {
		list->items[i - 1] = set_data(list->items[i], list->type);
	}
	list->size--;
	list->items[list->size] = NULL;
	list->items = resize(list);
}
void list_insert(ArrayList* list, int index, void* value) {
	if (index > list->size || index < 0) {
		printf("\n***ArrayList Error***\nCan't insert at index: %d\nList size: %d\n", index, list->size);
		return;
	}

	list->size++;
	list->items = resize(list);
	for (int i = list->size - 1; i > index; i--) {
		list->items[i] = set_data(list->items[i - 1], list->type);
	}
	list->items[index] = set_data(value, list->type);
}
int list_contains(ArrayList* list, void *value) {
	for (int i = 0; i < list->size; i++) {
		if (eq(list->items[i], value, list->type)) {
			return 1;
		}
	}
	return 0;
}
void list_clear(ArrayList* list) {
	for (int i = 0; i < list->size; i++) {
		free(list->items[i]);
	}
	free(list->items);
	list->size = 0;
}
void print_list(ArrayList *list) {
	printf("[");
	for (int i = 0; i < list->size; i++) {
		print_value(list->items[i], list->type);
		if (i == list->size - 1) {
			break;
		}
		printf(", ");
	}
	printf("]\n");
}

// void* Operations
int eq(void* element1, void* element2, ContainerTypes type) {
	switch(type) {
		case INT: {
			int first = *(int*)element1;
			int second = *(int*)element2;
			if (first == second) {
				return 1;
			}
			break;
		}
		case FLOAT: {
			float first = *(float*)element1;
			float second = *(float*)element2;
			if (first == second) {
				return 1;
			}
			break;
		}
		case STRING: {
			char* first = (char*)element1;
			char* second = (char*)element2;
			if (strncmp(first, second, strlen(first)) == 0) {
				return 1;				
			}
			break;
		}
		case GRAPHNODE: {
			GraphNode* first = (GraphNode*)element1;
			GraphNode* second = (GraphNode*)element2;
			if (eq(first->value, second->value, first->type)) {
				return 1;
			}
			break;
		}
		default:
			break;
	}

	return 0;
}
int gt(void* element1, void* element2, ContainerTypes type) {
	switch(type) {
		case INT: {
			int first = *(int*)element1;
			int second = *(int*)element2;
			if (first > second) {
				return 1;
			}
			break;
		}
		case FLOAT: {
			float first = *(float*)element1;
			float second = *(float*)element2;
			if (first > second) {
				return 1;
			}
			break;
		}
		default:
			break;
	}
	return 0;
}
int lt(void* element1, void* element2, ContainerTypes type) {
	switch(type) {
		case INT: {
			int first = *(int*)element1;
			int second = *(int*)element2;
			if (first < second) {
				return 1;
			}
			break;
		}
		case FLOAT: {
			float first = *(float*)element1;
			float second = *(float*)element2;
			if (first < second) {
				return 1;
			}
			break;
		}
		default:
			break;
	}
	return 0;
}
int ge(void* element1, void* element2, ContainerTypes type) {
	switch(type) {
		case INT: {
			int first = *(int*)element1;
			int second = *(int*)element2;
			if (first >= second) {
				return 1;
			}
			break;
		}
		case FLOAT: {
			float first = *(float*)element1;
			float second = *(float*)element2;
			if (first >= second) {
				return 1;
			}
			break;
		}
		default:
			break;
	}
	return 0;
}
int le(void* element1, void* element2, ContainerTypes type) {
	switch(type) {
		case INT: {
			int first = *(int*)element1;
			int second = *(int*)element2;
			if (first <= second) {
				return 1;
			}
			break;
		}
		case FLOAT: {
			float first = *(float*)element1;
			float second = *(float*)element2;
			if (first <= second) {
				return 1;
			}
			break;
		}
		default:
			break;
	}
	return 0;
}

// Node Helpers
int isEmpty(Node* root) {
	if (root == NULL) {
		return 1;
	}
	return 0;
}
int size(Node* root) {
	if (isEmpty(root)) {
		return 0;
	}
	return size(root->next) + 1;
}
Node* set_node(void* value, ContainerTypes type) {
	Node* node = (Node*)calloc(1, sizeof(Node));
	node->value = set_data(value, type);
	node->type = type;
	node->key = NULL;
	node->next = NULL;
	node->prev = NULL;
	return node;
}
void print_nodes(Node *node) {
	if (node == NULL) {
		printf("\n");
		return;
	}
	
	print_value(node->value, node->type);

	if (node->next != NULL) {
		printf(" --> "); 
	}

	print_nodes(node->next);
}
void free_nodes(Node *node) {
	if (node == NULL) {
		return;
	}
	free_nodes(node->next);
	free(node);
}

// Stack
void push(Node** stack, void* value, ContainerTypes type) {
	if (*stack == NULL) {
		*stack = set_node(value, type);
		return;
	}

	Node* node = set_node(value, type);
	node->next = *stack;
	(*stack)->prev = node;
	*stack = node;
}
Node* pop(Node** stack) {
	if (stack == NULL) {
		return NULL;
	}
	
	Node* popped = (*stack);
	*stack = (*stack)->next;

	(*stack)->prev= NULL;
	popped->next = NULL;
	popped->prev = NULL;
	
	return popped;
}
void* peek(Node* stack) {
	return stack->value;
}

// Queue
void enqueue(Node** queue, void* value, ContainerTypes type) {
	if (*queue == NULL) {
		*queue = set_node(value, type);
		return;
	}
	if ((*queue)->next == NULL) {
		Node* node = set_node(value, type);
		node->prev = *queue;
		(*queue)->next = node;
		return;
	}

	enqueue(&(*queue)->next, value, type);
}
Node* dequeue(Node** queue) {
	if (*queue == NULL) {
		return NULL;
	}

	if ((*queue)->next == NULL) {
		Node* dequeued = *queue;
		dequeued->next = NULL;
		dequeued->prev=  NULL;

		*queue = NULL;
		return dequeued;
	}

	Node* dequeued = *queue;
	*queue = (*queue)->next;
	(*queue)->prev = NULL;

	dequeued->prev = NULL;
	dequeued->next = NULL;
	return dequeued;
}
void* view(Node* queue) {
	return queue->value;
}

// Hashmap
int hash(const char* key, size_t size) {
	int ascii_sum = 0;
	for (int i = 0; i < strlen(key); i++) {
		ascii_sum += key[i];
	}
	return ascii_sum % size;
}
Hashmap init_map(size_t capacity) {
	Hashmap map;
	map.size = 0;
	map.capacity = capacity;
	map.items = (Node*)calloc(capacity, sizeof(Node));
	for (int i = 0; i < capacity; i++) {
		map.items[i].value = NULL;
		map.items[i].key = NULL;
		map.items[i].next = NULL;
		map.items[i].prev = NULL;
	}
	return map;
}
Node* get_map(Hashmap* map, const char* key) {
	int index = hash(key, map->capacity);

	if (map->items[index].key != NULL && strncmp(map->items[index].key, key, MAX_LENGTH) == 0) {
		return &map->items[index];
	}

	Node* curr = map->items[index].next;
	while (curr != NULL) {
		if (strncmp(curr->key, key, MAX_LENGTH) == 0) {
			return curr;
		}
		curr = curr->next;
	}

	return NULL;
}
void update_map(Hashmap* map, const char* key, void* value, ContainerTypes type) {
	int index = hash(key, map->capacity);
	
	if (map->items[index].key == NULL) {
		map->items[index].key = (char*)calloc(MAX_LENGTH, sizeof(char));
		memcpy(map->items[index].key, key, strlen(key));
		map->items[index].value = set_data(value, type);
		map->items[index].type = type;
		map->size++;
		return;
	}

	if (strncmp(map->items[index].key, key, MAX_LENGTH) == 0) {
		map->items[index].value = set_data(value, type);
		map->items[index].type = type;
		return;
	}

	Node* prev = &map->items[index];
	Node* curr = map->items[index].next;
	while (curr != NULL) {
		if (strncmp(curr->key, key, MAX_LENGTH) == 0) {
			curr->value = set_data(value, type);
			return;
		}

		prev = curr;
		curr = curr->next;
	}

	curr = set_node(value, type);
	curr->key = (char*)calloc(MAX_LENGTH, sizeof(char));
	memcpy(curr->key, key, MAX_LENGTH);
	curr->value = set_data(value, type);
	prev->next = curr;
	curr->prev = prev;
	map->size++;
}
void delete_map(Hashmap* map, const char* key) {
	Node* node = get_map(map, key);
	if (node == NULL) {
		printf("\tCouldn't Delete Pair (Unknown Key): %s\n", key);
		return;
	}
	
	if (node->value == NULL) {
		printf("\tPair entry is empty at: %s\n", key);
		return;
	}

	map->size--;
	if (node->prev == NULL) {
		node->value = NULL;
		free(node->key);
		node->key = NULL;
		return;
	}
	
	if (node->next == NULL) {
		node->prev->next = NULL;
		node->prev = NULL;
		free(node);
		return;
	}
	
	node->next->prev = node->prev;
	node->prev->next = node->next;
	node->next = NULL;
	node->prev = NULL;
	free(node);
}
void print_map(Hashmap* map) {
	int items = 0;
	printf("{");
	for (int i = 0; i < map->capacity; i++) {
		if (map->items[i].key != NULL) {
			items++;
			printf("%s: ", map->items[i].key);
			print_value(map->items[i].value, map->items[i].type);
			if (items < map->size) {
				printf(" | ");
			}
		}

		Node* curr = map->items[i].next;
		while (curr != NULL) {
			items++;
			printf("%s: ", curr->key);
			print_value(curr->value, curr->type);

			if (items < map->size) {
				printf(" | ");
			}
			curr = curr->next;
		}
	}
	printf("}\n");
}
void print_map_layout(Hashmap* map) {
	printf("{");
	for (int i = 0; i < map->capacity; i++) {
		printf(":> ");
		print_nodes(&map->items[i]);
	}
	printf("}\n");
}
void clear_map(Hashmap* map) {
	for (int i = 0; i < map->capacity; i++) {
		free_nodes(map->items[i].next);
	}
	free(map->items);
}

// Graph
Graph init_graph() {
	Graph graph;
	graph.size = 0;
	graph.nodes = (GraphNode**)calloc(0, sizeof(GraphNode*));
	return graph;
}
int indexof_graph(Graph* graph, void* value) {
	for (int i = 0; i < graph->size; i++) {
		if (eq(graph->nodes[i]->value, value, graph->nodes[i]->type)) {
			return i;
		}
	}
	return -1;
}
GraphNode* update_graph(Graph* graph, void* value, ContainerTypes type) {
	for (int i = 0; i < graph->size; i++) {
		if (graph->nodes[i]->type != type) {
			continue;
		}
		if (eq(graph->nodes[i]->value, value, type)) {
			return graph->nodes[i];			
		}
	}

	graph->size++;
	graph->nodes = (GraphNode**)realloc(graph->nodes, graph->size * sizeof(GraphNode*));
	graph->nodes[graph->size - 1] = (GraphNode*)calloc(1, sizeof(GraphNode));
	graph->nodes[graph->size - 1]->value = set_data(value, type);
	graph->nodes[graph->size - 1]->type = type;
	graph->nodes[graph->size - 1]->num_conn = 0;
	graph->nodes[graph->size - 1]->connections = (Connection*)calloc(0, sizeof(Connection));
	return graph->nodes[graph->size - 1];
}
void make_connection(Graph* graph, void* start, void* end, ContainerTypes type, unsigned int weight) {
	GraphNode* node1 = update_graph(graph, start, type);
	GraphNode* node2 = update_graph(graph, end, type);
	
	node1->num_conn++;
	node1->connections = (Connection*)realloc(node1->connections, node1->num_conn * sizeof(Connection));
	node1->connections[node1->num_conn - 1].node = node2;
	node1->connections[node1->num_conn - 1].weight = weight;
}
void make_two_way_connection(Graph* graph, void* first, void* second, ContainerTypes type, unsigned int weight) {
	GraphNode* node1 = update_graph(graph, first, type);
	GraphNode* node2 = update_graph(graph, second, type);

	node1->num_conn++;
	node1->connections = (Connection*)realloc(node1->connections, node1->num_conn * sizeof(Connection));
	node1->connections[node1->num_conn - 1].node = node2;
	node1->connections[node1->num_conn - 1].weight = weight;

	node2->num_conn++;
	node2->connections = (Connection*)realloc(node2->connections, node2->num_conn * sizeof(Connection));
	node2->connections[node2->num_conn - 1].node = node1;
	node2->connections[node2->num_conn - 1].weight = weight;
}
void print_graphnode(GraphNode* node) {
	print_value(node->value, node->type);
}
void print_graph(Graph* graph) {
	printf("---------------------------------\n");
	for (int i = 0; i < graph->size; i++) {
		print_value(graph->nodes[i]->value, graph->nodes[i]->type);
		printf(": ");

		for (int j = 0; j < graph->nodes[i]->num_conn; j++) {
			printf("(Weight: %u, Value: ", graph->nodes[i]->connections[j].weight);
			print_graphnode((GraphNode*)graph->nodes[i]->connections[j].node);
			printf(")");
			if (j < graph->nodes[i]->num_conn - 1) {
				printf(", ");
			}
		}
		
		printf("\n");
	}
	printf("---------------------------------\n");
}
void print_graph_items(Graph* graph) {
	printf("(");
	for (int i = 0; i < graph->size; i++) {
		print_value(graph->nodes[i]->value, graph->nodes[i]->type);
		if (i < graph->size - 1) {
			printf(", ");
		}
	}
	printf(")\n");
}
void free_graph(Graph* graph) {
	free(graph->nodes);
}
