#include <bits/stdc++.h>
using namespace std;

vector<int> adj[26];

class Queue{
	int front = 0, rear = 0;
	int q[26];
	public:
		void enQueue(int rn);
		int deQueue();
		bool is_empty();
};

bool Queue:: is_empty(){
	if(front >= rear)
		return true;
	return false;
}

void Queue:: enQueue(int rn) {

	q[rear]=rn;
	rear++;
}

int Queue:: deQueue() {

	if(front >= rear)
		return -1;

	int rv = q[front];
	front++;
	return rv;
}


struct  node
{
	int data;
	node *link;
};

class Stack{
	public:
		node *top;

		Stack() {
			top = NULL;
		}

		void push(int x) {
			node *tmp = new node;
			tmp->data = x;
			tmp->link = NULL;
			if(top == NULL) {
				top = tmp;
			}
			else {
				tmp->link = top;
				top = tmp;
			}
		}

		int pop() {
			int x;
			x = top->data;
			top = top->link;
			return x;
		}

		void print(){
			node *tmp = top;

			while(tmp) {
				cout << tmp->data << " " ;
				tmp = tmp->link;
			}
			cout << endl;
		}
};


void insert_edge(){
	char a, b;
	cin >> a >> b;
	int u, v;
	u = a - 'A';
	v = b - 'A';
	adj[u].push_back(v);
	adj[v].push_back(u);
	sort(adj[u].begin(), adj[u].end());
	sort(adj[v].begin(),adj[v].end());
}

bool is_visited(vector<int> visited,int x) {
	vector<int>::iterator ptr;
	for (ptr = visited.begin(); ptr < visited.end(); ptr++)
	{
		if(*ptr == x)
			return true;
	}
	return false;
}

void bfs(){
	Queue *queue = new Queue();
	queue->enQueue(0);
	vector<int> visited;
	while(!queue->is_empty()) {
		int u = queue->deQueue();
		if(u == -1)
			return;
		if(is_visited(visited, u))
			continue;
		else {
			vector<int>::iterator ptr;
			for (ptr = adj[u].begin(); ptr < adj[u].end(); ptr++) {
				queue->enQueue(*ptr);
			}
			cout << (char)(u+'A')<< " ";
			visited.push_back(u);
		}
	}
	cout << endl;
}

void dfs() {
	Stack *stack = new Stack();
	stack->push(0);
	vector<int> visited;
	while(stack->top != NULL) {
		int u = stack->pop();
		if(u == -1)
			return;
		if (is_visited(visited, u))
			continue;
		vector<int>::iterator ptr;
		for(ptr = adj[u].end()-1; ptr >= adj[u].begin(); ptr--)
			stack->push(*ptr);
		cout << (char)(u+'A')<< " ";
		visited.push_back(u);
	}
	cout << endl;
}

void menu(){
	cout << "1 Insert"<< endl;
	cout << "2 BFS" << endl;
	cout << "3 DFS" << endl;
	int x;
	cin >> x;
	switch(x){
		case 1:
			insert_edge();
			break;
		case 2:
			bfs();
			break;
		case 3:
			dfs();
			break;
		default:
			break;
	}
}

int main(int argc, char const *argv[])
{
	while(1){
		menu();
	}
	return 0;
}