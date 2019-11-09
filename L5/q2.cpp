#include <bits/stdc++.h>
using namespace std;
clock_t clk;

struct edge {
	int u, v, w;
};

FILE * output = fopen("kruskal_graph.dot", "w");

edge* make_edge(char s, char d, int w) {
	edge* e = new edge();
	e->u = s - 'A';
	e->v = d - 'A';
	e->w = w;
	return e;
}

bool compare_w(edge* e1, edge* e2) {
	return (e1->w < e2->w);
}

struct graph {
	int V=26, E=100;
	vector <edge*> e;
};

graph* g = new graph();

void make_set(int parent[],int rank[]) {
	for(int i = 0; i < g->V; ++i) {
		rank[i] = 0;
		parent[i] = i;
	}
}

int find_set(int x, int parent[]) {
	if(x != parent[x])
		return find_set(parent[x], parent);
	return x;
}

void link(int x, int y, int parent[], int rank[]) {
	if(rank[x] > rank[y])
		parent[y] = x;
	else
		parent[x] = y;
	if(rank[x] == rank[y])
		rank[y]++;
}

void union_set(int x, int y, int parent[], int rank[]){
	link(find_set(x, parent), find_set(y, parent), parent, rank);
}

void kruskal(int parent[], int rank[]) {
	clk = clock();
	make_set(parent, rank);
	sort(g->e.begin(), g->e.end(), compare_w);

	for(auto x: g->e) {
		if(find_set(x->u, parent) != find_set(x->v, parent)) {
			int src = x->u + 'A';
			int dst = x->v + 'A';
			fprintf(output,"\t%c -- %c [label=\"%d\"]\n",src,dst,x->w);
			cout << char(src) << "," << char(dst) << "," << x->w <<endl;
			union_set(x->u, x->v, parent, rank);
		}
	}
	clk=clock()-clk;
	cout << "Time: " << 1000000*((double)clk)/CLOCKS_PER_SEC << " microsec\n" << endl;
}

int main(int argc, char const *argv[])
{
	FILE * f = fopen(argv[1],"r");

	int parent[g->E+1];
	int rank[g->E+1];

	g->E=0;
	for(int i=0;i<100;i++)
	{
		char a,b;
		int x;
		fscanf(f,"%c,%c,%d\n",&a,&b,&x);
		g->e.push_back(make_edge(a,b,x));
		g->E++;
	}

	fprintf(output,"graph foo{\n");

	kruskal(parent, rank);
	fprintf(output,"}\n");
	fclose(output);
	return 0;
}

// dot -Tps kruskal_graph.dot -o kruskal_image.ps 