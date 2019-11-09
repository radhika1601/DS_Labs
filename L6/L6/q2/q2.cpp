#include <bits/stdc++.h>
using namespace std;

FILE * output = fopen("graph.dot", "w");

struct node
{
	int key;
	int degree;
	node *leftmost;
	node *next;
};

node *create(int k,int d){				// create node

	node *temp=new node;
	temp->key=k;
	temp->degree=d;
	temp->leftmost=temp->next=NULL;
	return temp;
}

node *child(node *x){						// return leftmost
	if (x==NULL || x->leftmost == NULL)
		return NULL;

	return x->leftmost;	
}

node *sibling(node *x){					// return next
	if (x==NULL || x->next == NULL)
		return NULL;

	return x->next;
}

node *merging(node *h1,node *h2){		// merge	

	node *h=NULL,*last=NULL,*temp;

	if (h1==NULL)					// if any one is null return aonther
		return h2;

	if (h2==NULL)
		return h1;

	while(h1!=NULL && h2!=NULL){

		if (h1->degree > h2->degree){		// degree of h2 is small then temp points to h2 and h2 shift to its next

			temp=h2;
			h2=h2->next;
		}

		else{							// degree of h2 is small then temp points to h2 and h2 shift to its next
			temp=h1;
			h1=h1->next;
		}

		if (h==NULL){				// if new heap is null
			h=temp;
			last=temp;
		}

		else{						// else add at last
			last->next=temp;
			last=last->next;
		}
	}

	if (h1!=NULL){					// if any heap is remaining then attach as it is
		last->next=h1;
		h1=NULL;
	}

	if (h2!=NULL){
		last->next=h2;
		h2=NULL;
	}
	
	return h;						// reutrn new heap 
}

node *perv(node **head,node *x){ 			// find prev node of given node

	if (x==(*head))	
		return NULL;

	node *temp=*head;

	while(temp->next!=x)
		temp=temp->next;
	
	return temp;
}

node *last_one(node *x){			// find last node of given node 

	if (x==NULL)
		return NULL;

	while(x->next!=NULL)
		x=x->next;

	return x;
}

node *call(node **head,node *x){	//this function for shifting node for samr degree		

	node *x1;
	x1=x->next;

	if (x->key > x1->key)		// if key of x1 is less
	{
		(x1->degree)++;			// degree is increase by 1

		if (perv(head,x)==NULL)		//next of perv of x  points x1 
			(*head)=x1;
		
		else
			perv(head,x)->next=x1;

			x->next=x1->leftmost;		
			x1->leftmost=x;

			return x1;			// return x1
	}
	else{

		(x->degree)++;			// degree is increase by 1
		x->next=x1->next;		//perv of x1 is x and  next of x points x1 
		x1->next=x->leftmost;	
		x->leftmost=x1;			
		return x;				
	}	
}

void Union (node **head ) {

	node *x=(*head),*x1=NULL;

	if (x==NULL || x->next==NULL)		// if no node or only one node then return
		return;


	while(sibling(x)!=NULL){			// if atleast two node

		x1=sibling(x);

		if (x->degree != x1->degree)		// if degree is not equal then x shift by one
			x=x1;

		else{

			if (sibling(x1)==NULL)			// if degree are same and no node after that or degree of next of next of x is not equal to x then call call
				x=call(head,x);

			else if (sibling(sibling(x))->degree!=x->degree) 		
				x=call(head,x);

			else						// else shift by one
				x=x1;
		}
	}
	return;
}

void INSERT(node **head,int d){

	node *temp;
	temp=create(d,0);				// insert new node
	(*head)=merging(*head,temp);	// merge new node with head
	Union(head);

	return;
}

void childShow(node *head,int parent){
	fprintf(output,"\t%d -- %d\n",parent,head->key);
	cout << " " << head->key ;
	if ( child(head) != NULL ){
		// showHeap( child(head), depth + 1 );
		childShow(child(head),head->key);
	}

	if (head->next!=NULL)
	{
		childShow(head->next,parent);
	}
}

void showHeap( node *head,int depth ){ 			// given in ques
	cout << "Degree - " << head->degree << " : ";
	cout << head->key;

	if (head->degree==0)
	{
		fprintf(output,"\t%d \n",head->key);
	}
	if ( child(head) != NULL ){
		// showHeap( child(head), depth + 1 );
		childShow(child(head),head->key);
	}
	cout << endl;
	if ( head->next != NULL )
		showHeap( head ->next, depth );

	return;
}

void showBinomialHeap(node *head){
	
	if ( head == NULL )
		printf("Empty heap\n");

	else {
		showHeap( head, 0 );
	}
	return;
}

int main()
{
	int numberOfNodes;
	cin >> numberOfNodes;
	node *head=NULL;
	node *temp;
	int d;
	for (int i = 0; i < numberOfNodes; ++i)
	{
		cin >> d;
		INSERT(&head,d);
	}
	
	fprintf(output,"graph foo{\n");

	showBinomialHeap(head);
	fprintf(output,"}\n");
	fclose(output);

	return 0;
}