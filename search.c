#include "search.h"
#include "ds.h"

int binary_search(ArrayList* list, void* val) {
	if (list->type == STRING) {
		return 0;
	}

	int l = 0;
	int h = list->size - 1;
	while (l < h) {
		int mid = (l+h) / 2;

		if (eq(list->items[mid], val, list->type)) {
			return 1;
		} else if (gt(list->items[mid], val, list->type)) {
			h = mid;
		} else {
			l = mid + 1;
		}
	}

	return 0;
}

int dfs(GraphNode* node, ArrayList* set) {
	printf("\t");
	print_value(node->value, node->type);
	printf("\n");

	list_append(set, node->value);
	for (int i = 0; i < node->num_conn; i++) {
		void* value = ((GraphNode*)node->connections[i].node)->value; 

		if (list_contains(set, value)) {
			continue;
		} 

		dfs(node->connections[i].node, set);
	}
	return 0;
}
int bfs(GraphNode* node, Node** queue) {
	ArrayList set = list_init(0, GRAPHNODE);
	enqueue(queue, node, GRAPHNODE);
	list_append(&set, node);

	while (!isEmpty(*queue)) {
		Node* element = dequeue(queue);
		GraphNode* graphNode = (GraphNode*)element->value;

		printf("\t");
		print_value(graphNode->value, graphNode->type);
		printf("\n");
		for (int i = 0; i < graphNode->num_conn; i++) {
			if (list_contains(&set, graphNode->connections[i].node)) {
				continue;
			}

			list_append(&set, graphNode->connections[i].node);
			enqueue(queue, graphNode->connections[i].node, GRAPHNODE);
		}
		free_nodes(element);
	}

	list_clear(&set);
	return 0;
}

void dijkstras_shortest_path(Graph* graph, void* value, Hashmap* distances, Hashmap* paths) {
	*distances = init_map(7);
	*paths = init_map(7);
	ArrayList visited = list_init(0, STRING);

	int startIndex = indexof_graph(graph, value);
	int n = 0;
	update_map(distances, (const char*)graph->nodes[startIndex]->value, &n, INT);
	for (int i = 0; i < graph->size; i++) {
		if (i == startIndex) {
			continue;
		}

		int n = -1;
		update_map(distances, (const char*)graph->nodes[i]->value, &n, INT);
	}

	Node* queue = NULL;
	enqueue(&queue, graph->nodes[startIndex], GRAPHNODE);
	list_append(&visited, graph->nodes[startIndex]->value);
	while(!isEmpty(queue)) {
		Node* element = dequeue(&queue);
		GraphNode* node = (GraphNode*)element->value;
		list_append(&visited, node->value);

		Node* distNode = get_map(distances, (const char*)node->value);
		int distance = *(int*)distNode->value;

		for (int i = 0; i < node->num_conn; i++) {
			GraphNode* adj_node = (GraphNode*)node->connections[i].node;
			int weight = node->connections[i].weight;
			int sum = distance + weight;

			Node* adjDistNode = get_map(distances, (const char*)adj_node->value);
			int adjDist = *(int*)adjDistNode->value;

			if (sum < adjDist || adjDist == -1) {
				update_map(distances, (const char*)adj_node->value, &sum, INT);
				update_map(paths, (const char*)adj_node->value, node->value, STRING);
			}
		}
		
		unsigned int min = UINT_MAX;
		GraphNode* minNode = NULL;
		for (int i = 0; i < graph->size; i++) {
			if (list_contains(&visited, graph->nodes[i]->value)) {
				continue;
			}

			distNode = get_map(distances, (const char*)graph->nodes[i]->value);
			distance = *(int*)distNode->value;
			if (distance < min && distance != -1) {
				min = distance;
				minNode = graph->nodes[i];
			}
		}

		if (minNode != NULL) {
			enqueue(&queue, minNode, GRAPHNODE);
		}

		free(element);
	}

	list_clear(&visited);
}
void create_path(Hashmap* path, const char* start, const char* end, ArrayList* result) {
	Node* node = get_map(path, end);
	
	while (!eq(node->value, (void*)start, STRING)) {
		list_insert(result, 0, node->value);
		node = get_map(path, node->value);
	}
	list_append(result, (void*)end);
	list_insert(result, 0, (void*)start);
}
