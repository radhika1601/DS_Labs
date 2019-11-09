#include <bits/stdc++.h>
using namespace std;

struct node{
	int data;
	node *next=NULL;
};

vector<node *> adj(26);
vector<int> colour(26);
vector<int> present(26);
bool isCyclePresent;
int diameter=0;

void insertEdge(){
	char c1,c2;
	cout << "Enter first Node Letter and press ENTER : ";
	cin >> c1;
	cout <<"Enter second Node Letter and press ENTER : ";
	cin >> c2;
	cout << endl;
	int firstNumber = c1-'A';
	int secondNumber = c2-'A';

	if (!( firstNumber>=0 && firstNumber<26 && secondNumber>=0 && secondNumber<26 ))
	{
		cout << "Enter correct Details";
		exit(1);
	}

	present[firstNumber]++;
	present[secondNumber]++;

	node *fNode = new node();
	fNode->data = firstNumber;

	node *sNode = new node();
	sNode->data = secondNumber;

	sNode->next = adj[firstNumber]->next;
	adj[firstNumber]->next = sNode;

	fNode->next = adj[secondNumber]->next;
	adj[secondNumber]->next = fNode;

	return;
}	

void BFStraversal(){

	for (int i = 0; i < 26; ++i)
		colour[i] = 0;

	vector<node *> que;
	int index = 0;

	for (int i = 0; i < 26; ++i)
	{
		if(colour[i]==0 && present[i]>0)
		{
			colour[i] =1;
			printf("%c ",i+65);
			que.push_back(adj[i]);
		}

		while(index!=que.size()){
			node *temp = que[index]->next;

			while(temp!=NULL){

				int d = temp->data;

				if(colour[d]==0){
					colour[d] = 1;
					printf("%c ",d+65);
					que.push_back(adj[d]);
				}

				temp = temp->next;
			}
			index++;
		}
	}

}

void callDFS(int i){

	colour[i] = 1;

	node *temp = adj[i]->next;

	while(temp!=NULL){

		int d = temp->data;

		if(colour[d]==0){
			printf("%c ",d+65);
			callDFS(d);
		}
		temp = temp->next;
	}

	colour[i] = 2;
}

void DFStraversal(){
	
	for (int i = 0; i < 26; ++i)
		colour[i] = 0;

	for (int i = 0; i < 26; ++i)
	{
		if(colour[i]==0 && present[i]>0)
		{
			printf("%c ",i+65);
			callDFS(i);
		}
	}
}

void findCycle(int i){
	colour[i] = 1;

	node *temp = adj[i]->next;

	while(temp!=NULL){

		int d = temp->data;

		if(colour[d]==0){
			findCycle(d);
		}
		else if (colour[d]==2)
		{
			isCyclePresent = true;
		}
		temp = temp->next;
	}
	colour[i] = 2;
}

void checkCycle(){
	
	for (int i = 0; i < 26; ++i)
		colour[i] = 0;

	isCyclePresent=false;

	for (int i = 0; i < 26; ++i)
	{
		if(colour[i]==0 && present[i]>0)
		{
			findCycle(i);
		}
	}

	if (isCyclePresent)
		cout << "Yes" << endl;
	else
		cout << "No" << endl;

	return;
}

void findDiameter(){
	
	for (int i = 0; i < 26; ++i)
		colour[i] = 0;
	diameter = 0;

	vector<node *> que;
	int index = 0;
	int numberOfSCC = 0;

	for (int i = 0; i < 26; ++i)
	{
		index=0;
		que.empty();
		if(colour[i]==0 && present[i]>0)
		{
			numberOfSCC++;
			colour[i] =1;
			que.push_back(adj[i]);
		}

		while(index!=que.size()){
			node *temp = que[index]->next;

			while(temp!=NULL){
				int d = temp->data;
				if(colour[d]==0){
					colour[d] = 1;
					que.push_back(adj[d]);
				}
				temp = temp->next;
			}
			index++;
		}
	}

	if (numberOfSCC>1)
	{
		cout << "Infinite" << endl;
		return;
	}

	for (int i = 0; i < 26; ++i)
	{
		for (int j = 0; j < 26; ++j)
			colour[j]=0;

		vector<pair<node*,int>>pairQueue;
		node *t = adj[i]->next;
		pairQueue.push_back({adj[i],0});
		index=0;
		colour[i] = 1;

		while(index!=pairQueue.size()){
			node *temp = pairQueue[index].first->next;
			int len = pairQueue[index].second + 1;

			while(temp!=NULL){
				int d = temp->data;
				if(colour[d]==0){
					colour[d] = 1;
					pairQueue.push_back({adj[d],len});
					diameter = max(diameter,len);
				}
				temp = temp->next;
			}
			index++;
		}
	}
	cout << diameter << endl;
}



void menu(){
	cout << endl << endl;
	cout << "1. Inset edge" << endl;
	cout << "2. BFS traversal" << endl;
	cout << "3. DFS traversal" << endl;
	cout << "4. Cycle finding in the graph" << endl;
	cout << "5. Calculate diameter of the graph "<< endl;
	
	int x;
	cin >> x;
	switch(x){
		case 1:
			insertEdge();
			break;
		case 2:
			BFStraversal();
			break;
		case 3:
			DFStraversal();
			break;
		case 4:
			checkCycle();
			break;
		case 5:
			findDiameter();
			break;
		default:
			break;
	}
}

int main(int argc, char const *argv[])
{
	for (int i = 0; i < 26; ++i)
	{
		adj[i] = new node();
		adj[i]->data= i;
		adj[i]->next = NULL;
		present[i]=0;
	}
	while(1){
		menu();
	}
	return 0;
}