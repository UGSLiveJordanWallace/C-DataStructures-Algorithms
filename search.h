#ifndef search
#define search

#include "ds.h"
#include "stdio.h"
#include "limits.h"

int binary_search(ArrayList* arr, void* value);

int dfs(GraphNode* node, ArrayList* set);
int bfs(GraphNode* node, Node** queue);

void dijkstras_shortest_path(Graph* graph, void* value, Hashmap* distances, Hashmap* paths);
void create_path(Hashmap* path, const char* start, const char* end, ArrayList* result);

#endif
