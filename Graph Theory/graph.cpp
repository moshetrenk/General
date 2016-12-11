#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> cycle;

bool cycle_contains(int num){
	for (int i = 0; i < cycle.size(); i++){
		if (cycle.at(i) == num)
			return true;
	}

	return false;
}

struct node {
	int vertex;
	node * next;
};


class Graph{
public:
	bool * visited = new bool[numVertices];
	vector<int> orderVisited;
	int numVertices; // number of vertices
	int e; // number of edges
	node * headnodes;
	
	Graph(int nodes) // construtor
	{
		numVertices = nodes;
		headnodes = new node[numVertices]; // headnodes is an array of nodes.
		for (int i = 0; i < numVertices; i++)
		{
			headnodes[i].vertex = i;
			headnodes[i].next = nullptr;

			//this is unrelated to the above portion of the loop
			//might as well use the loop to set each value of the visited array to false
			visited[i] = false;
		}
		visited[0] = true;

		create();
	}

	void create(){
		int numConnected = 0;
		int * connections;
		for (int i = 0; i < numVertices; i++){
		cout << "How many vertices are connected to vertex #" << i << "?" << endl;
		cin >> numConnected;
		connections = new int[numConnected];
		cout << "Enter the number of each vertex connected to vertex #" << i << endl;
		for (int j = 0; j < numConnected; j++){
		cin >> connections[j];
		}

		node * nodes = new node[numConnected];
		for (int k = 0; k < numConnected; k++){
		nodes[k].vertex = connections[k];
		if (k != numConnected - 1)
		nodes[k].next = &nodes[k + 1];
		else
		nodes[k].next = nullptr;
		}
		headnodes[i].next = &nodes[0];
		}
	}

	void output(){
		for (int i = 0; i < numVertices; i++){
			for (node * a = &headnodes[i]; a != nullptr; a = a->next){
				cout << a->vertex << ", ";
			}
			cout << endl;
		}
	}

	int allVisited(){
		for (int i = 0; i < numVertices; i++){
			if (!visited[i])
				return i;
		}

		return -1;
	}

	void dfs(int parent, int child){
		if (!cycle_contains(child) && components == 1){
			cycle.push_back(child);
		}

		visited[child] = true;

		if (allVisited() == -1){
			return;
		}

		int nextToVisit = -1;

		node * n = &headnodes[child];

		while (n->next != nullptr){
			if (!visited[n->next->vertex]){
				nextToVisit = n->next->vertex;
				break;
			}
			n = n->next;
		}
		n->next = nullptr;
		n = nullptr;

		if (nextToVisit == -1)
			return;
		else
			dfs(child, nextToVisit);
	}
	int components = 1;
};



int main(){
	int numVertices;
	cout << "Enter the number of vertices" << endl;
	cin >> numVertices;
	Graph graph(numVertices);
	cycle.push_back(0);
	graph.dfs(0, 1);

	while (graph.allVisited() > -1){
		graph.components++;
		graph.dfs(graph.allVisited(), graph.headnodes[graph.allVisited() + 1].vertex);
	}

	cout << "components = " << graph.components << endl;
	
	for (int i = 0; i < cycle.size(); i++){
		if (i == cycle.size() - 1)
			cout << cycle.at(i) << endl;
		else
			cout << cycle.at(i) << "->";
	}

	return 0;
}
