#include "ds.h"
#include "search.h"

void test_array();
void test_stack();
void test_queue();
void test_map();
void test_graph();

int main(void) {
	test_array();
//	test_stack();
//	test_queue();
//	test_map();
//	test_graph();

	Graph graph = init_graph();
	make_two_way_connection(&graph, "D", "E", STRING, 2);
	make_two_way_connection(&graph, "D", "A", STRING, 4);
	make_two_way_connection(&graph, "A", "C", STRING, 3);
	make_two_way_connection(&graph, "A", "E", STRING, 4);
	make_two_way_connection(&graph, "E", "C", STRING, 4);
	make_two_way_connection(&graph, "E", "G", STRING, 5);
	make_two_way_connection(&graph, "C", "B", STRING, 2);
	make_two_way_connection(&graph, "C", "G", STRING, 5);
	make_two_way_connection(&graph, "B", "F", STRING, 2);
	make_two_way_connection(&graph, "F", "G", STRING, 5);
	make_two_way_connection(&graph, "G", "I", STRING, 4);
	make_two_way_connection(&graph, "G", "H", STRING, 5);
	make_two_way_connection(&graph, "I", "J", STRING, 2);
	print_graph_items(&graph);
	print_graph(&graph);
	
//	printf("DFS:\n");
//	ArrayList set = list_init(0, STRING);
//	dfs(graph.nodes[0], &set);
//	list_clear(&set);
//
//	printf("BFS:\n");
//	Node* queue = NULL;
//	bfs(graph.nodes[0], &queue);
//	free_nodes(queue);

	Hashmap distances;
	Hashmap paths;
	dijkstras_shortest_path(&graph, "D", &distances, &paths);
	print_map(&paths);
	print_map(&distances);

	ArrayList result = list_init(0, STRING);
	create_path(&paths, "D", "F", &result);
	print_list(&result);

	clear_map(&paths);
	clear_map(&distances);
	free_graph(&graph);
	return 0;
}

void test_array() {
	printf("**********************************\n");
	printf("List\n");
	ArrayList list1 = list_init(0, STRING);
	list_append(&list1, "Hello");
	list_append(&list1, "World");
	list_append(&list1, "How");
	list_append(&list1, "Are");
	list_append(&list1, "You?");
	print_list(&list1);

	list_insert(&list1, 0, "Popular");
	print_list(&list1); 

	ArrayList list2 = list_init(0, INT);
	int n = 8;
	list_append(&list2, &n);
	n = 95;
	list_append(&list2, &n);
	n = 72;
	list_append(&list2, &n);
	print_list(&list2); 
	int val = 8;
	printf("(Binary Search) looking for value (%d) %s\n", val, binary_search(&list2, &val) ? "True" : "False");

	float r = 8;
	ArrayList list3 = list_init(0, FLOAT);
	for (float fl = 0.02; fl < 1.2; fl += 0.02) {
		list_append(&list3, &fl);	
	}
	print_list(&list3); 
	
	list_clear(&list1);
	list_clear(&list2);
	list_clear(&list3);
	printf("**********************************\n");
}

void test_stack() {
	printf("**********************************\n");
	printf("Stack\n");
	Node* stack = NULL;
	push(&stack, "Hello", STRING);
	push(&stack, "World", STRING);
	push(&stack, "Bless", STRING);
	print_nodes(stack);

	Node* node = pop(&stack);
	printf("Popped: ");
	print_nodes(node);
	free(node);

	printf("Peeking Stack: ");
	print_value(peek(stack), node->type);
	printf("\n");
	
	print_nodes(stack);
	free_nodes(stack);
	printf("**********************************\n");
}

void test_queue() {
	printf("**********************************\n");
	printf("Queue\n");
	Node* queue = NULL;
	enqueue(&queue, "Hello", STRING);
	enqueue(&queue, "World", STRING);
	enqueue(&queue, "Bless", STRING);
	print_nodes(queue);

	Node* node = dequeue(&queue);
	printf("Dequeued: ");
	print_nodes(node);
	free(node);

	printf("Viewing Queue: ");
	print_value(view(queue), node->type);
	printf("\n");
	
	print_nodes(queue);
	free_nodes(queue);
	printf("**********************************\n");
}

void test_map() {
	Hashmap hmap = init_map(7);
	update_map(&hmap, "add", "BB-GUN", STRING);
	update_map(&hmap, "bob", "Archer", STRING);
	update_map(&hmap, "pic", "Art", STRING);
	update_map(&hmap, "gig", "Storage", STRING);

	int x = 808;
	update_map(&hmap, "arch", &x, INT);

	float y = 1e-4;
	update_map(&hmap, "body", &y, FLOAT);

	print_map(&hmap);

	Node* node = get_map(&hmap, "bob");
	printf("Get bob: ");
	print_value(node->value, node->type);
	printf("\n");

	node = get_map(&hmap, "pic");
	printf("Get pic: ");
	print_value(node->value, node->type);
	printf("\n");

	node = get_map(&hmap, "unknown");
	if (node != NULL) {
		printf("Get unknown: ");
		print_value(node->value, node->type);
		printf("\n");
	}

	delete_map(&hmap, "add");
	print_map(&hmap);
	print_map_layout(&hmap);

	clear_map(&hmap);
}

void test_graph() {
	Graph graph = init_graph();
	make_connection(&graph, "Start", "Plus", STRING, 2);
	make_connection(&graph, "Plus", "Minus", STRING, 3);
	make_connection(&graph, "Plus", "Process", STRING, 4);
	make_two_way_connection(&graph, "End", "Sequence", STRING, 1);
	make_two_way_connection(&graph, "Process", "Sequence", STRING, 6);
	make_two_way_connection(&graph, "Process", "Start", STRING, 8);
	print_graph_items(&graph);
	print_graph(&graph);
	free_graph(&graph);
}
