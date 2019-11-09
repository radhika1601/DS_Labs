#include "fibonacci_heap.h"
using namespace std;
clock_t clk;
map<pair<int,int>, int> myMap;

struct AdjListNode { 
    int dest; 
    int weight; 
    struct AdjListNode* next; 
}; 
  
struct AdjList {
    struct AdjListNode* head=NULL; 
};

struct AdjListNode* newAdjListNode(int dest, int weight) 
{ 
    struct AdjListNode* newNode = (struct AdjListNode*)malloc(sizeof(struct AdjListNode)); 
    newNode->dest = dest; 
    newNode->weight = weight; 
    newNode->next = NULL; 
    return newNode; 
}  
  
struct Graph {
    int V;
    int E;
    void create_edge(int src, int dest, int weight);
    void getVertices(); 
    vector<AdjList> array; 
};

void create_graph(Graph *graph){
    graph->E=0;
    for(int i=0;i<10000;i++){
        AdjList a;
        a.head = NULL;
        graph->array.push_back(a);
    }
}
  
void create_edge(Graph *graph,int src, int dest, int weight) { 
    struct AdjListNode* newNode = newAdjListNode(dest, weight); 
    newNode->next = (graph->array.at(src)).head; 
    (graph->array.at(src)).head = newNode; 
  
    newNode = newAdjListNode(src, weight); 
    newNode->next = (graph->array.at(dest)).head; 
    (graph->array.at(dest)).head = newNode;
    graph->E++;
}

void print_mst(int arr[], int n) 
{
    int weight = 0;
    for (int i = 1; i < n; ++i){
        if(myMap[make_pair(arr[i],i)]){
            weight = myMap[make_pair(arr[i],i)];
        }
        else
            weight = myMap[make_pair(i,arr[i])];
        cout<<(char)(arr[i]+65)<<"  "<<(char)(i+65)<<"    "<<weight<<endl;
    }
}

void newnew_wick(vector<string>** new_wick,Graph* graph, int* parent,char v)
{
    for (int i=0; i < graph->V; ++i)
    {
        if ((char)(parent[i]+65) == v)
        {
            newnew_wick(new_wick,graph,parent,(char)(i+65));
            string s = "";
            if (!new_wick[i]->empty())
            {

                s += "(";
                for (auto it = new_wick[i]->begin(); it != new_wick[i]->end(); ++it)
                {
                    s += *it;
                    if (*it != new_wick[i]->back())
                    {
                        s+= ",";
                    }
                }
                s+= ")";
            }
            s+= (char)(i+65);
            s+= ':';
            int weight;
            if(myMap[std::make_pair(parent[i],i)]){
                weight = myMap[std::make_pair(parent[i],i)];
            } 
            else 
                weight = myMap[std::make_pair(i,parent[i])];
            s+= to_string(weight);

            new_wick[v%65]->push_back(s);
        }
    }
}

void PrimMST(Graph* graph) 
{ 
    int V = graph->V; // Get the number of vertices in graph 
    int parent[V]; // Array to store constructed MST 
    int key[V]; // Key values used to pick minimum weight edge in cut

    int *arr = new int[V*sizeof(int)];  
   
  
    for (int v = 0; v < V; ++v) { 
        parent[v] = -1; 
        key[v] = INT_MAX;
        if(v==0)
            key[v] = 0;
        insertion(v,key[v]);
    } 
  
        while(mini!=NULL){

        struct node *p = Extract_min();
        int u = p->v; 
        arr[u]=1;
  
        struct AdjListNode* pCrawl = graph->array.at(u).head; 
        while (pCrawl != NULL) { 
            int v = pCrawl->dest; 

            if (!arr[v] && pCrawl->weight < key[v]) {   
                parent[v] = u; 
                Find(mini, v , pCrawl->weight);
                key[v] = pCrawl->weight; 
            } 
            pCrawl = pCrawl->next; 
        } 
    }

    vector<string>** new_wick = new vector<string>*[graph->V];
    for (int i = 0; i < graph->V; ++i)
    {
        new_wick[i] = new vector<string>();
    }
    newnew_wick(new_wick,graph,parent,'A');
    string s = "";
    if (!new_wick[0]->empty())
    {
        s += "(";
        for (auto it = new_wick[0]->begin(); it != new_wick[0]->end(); ++it)
        {
            s += *it;
            if (*it != new_wick[0]->back())
            {
                s+= ",";
            }
        }
        s+= ")";
    }
    s+="A;";
    fstream output;
    output.open("./new_wick.nh", ios::out);
    output << s << endl;
    output.close();

    print_mst(parent, V); 
} 

int main(int argc, char const *argv[])
{ 
    Graph *graph = new Graph();
    create_graph(graph);
    if(argc < 2) {
    	cout << "Enter file name in arguments." << endl;
    	exit(1);
    }

    ifstream file(argv[1]);
    string value;
    set<int> vertices;
    while ( file.good() ){ 
        getline ( file, value, '\n' );
        if(value == "")
            break;
        string delimiter = ",";
        int pos = value.find(delimiter);
        string src_string = value.substr(0,pos);
        string remaining = value.substr(pos+1,value.length());
        pos = remaining.find(delimiter);
        string des_string = remaining.substr(0,pos);
        string weight = remaining.substr(pos+1,remaining.length());
        int src = int(src_string.at(0))-65;
        int des = int(des_string.at(0))-65;
        
        int w = stoi(weight);
        myMap[make_pair(src,des)] = w;
        vertices.insert(src);
        vertices.insert(des);
        create_edge(graph,src,des,w);
    }
    graph->V=vertices.size();
    clk = clock();
    PrimMST(graph);
    clk=clock()-clk;
    cout << "Time: " << 1000000*((double)clk)/CLOCKS_PER_SEC << " microsec\n" << endl;
    return 0;
}