/** 
*@file Q2.c
*@brief this header file will contain all required 
*definitions and basic utilities functions.
*
*@author Radhika
*/
#include <bits/stdc++.h>
#include <time.h>
using namespace std;
#define ll long long int
#define mod 1000000007
#define pb push_back

/*
*Structure Of Linked List
*	   node ---right---> node
*   	|
* 	    |
* 	  next
*	    |
*	 	|
*  	   \./
*     node
*/

struct node
{
	node *right,*next;
	int value;
};

clock_t clk;

/**
*This method print the whole Linked Linkedlist
*/

void print();

/**
*This method find max value of linked list
*return the max value of list
*@param f reads the root node of list
*/
int findMax(node *f);

/**
*This method insert totalxor till ith index and in 
*vertical increasing order and then insert i in
*linked list respective to that node  
*@param totalxor is the xor of all numbers till ith index
*@param i is the index of array
*/
node * insert1(int totalxor,int i);

node *xorlist;

void print(){

	node* temp1 = xorlist,*temp2;
	cout << endl << "Print Linkedlist" << endl;
	while(temp1!=NULL){
		cout << temp1->value << " -> ";
		temp2 = temp1->right;
		while(temp2!=NULL){
			cout << temp2->value << " ";
			temp2 = temp2->right;
		}
		temp1 = temp1->next;
		cout << endl;
	}
}

node * insert1(int totalxor,int i){

	node *temp1=xorlist,*snode;
	while(temp1!=NULL){
		if (temp1->value == totalxor)
		{
			snode=temp1;
			break;
		}

		if (temp1->next ==NULL)
		{
			temp1->next = new node();
			temp1 = temp1->next;
			temp1->value = totalxor;
			snode = temp1;
			break;
		}

		if (temp1->next->value > totalxor)
		{
			node *temp = new node();
			temp->value = totalxor;
			temp->next = temp1->next;
			temp1->next = temp;
			snode = temp;
			break;
		}
		temp1 = temp1->next;
	}

	node *lst = snode;

	while(lst->right != NULL)
		lst = lst->right;

	lst->right = new node();
	lst = lst->right;
	lst->value = i;
	return snode;
}

int findMax(node *f){

	int val = f->value;

	while(f!=NULL){
		val = max(val,f->value);
		f = f->right;
	}
	return val;
}

int main(){

	ll n;
	cout << "Enter size of Array : ";
	cin >> n;
	ll totalxor = 0;
	
	node *v,*cv;
	v = new node();
	cv = v;	

/**
*insert 0 as node in vertical list and -1 as index in list respective to 0.
*because totalxor before 0th index is 0.
*/

	xorlist = new node();
	xorlist->value = 0;
	xorlist->right = new node();
	xorlist->right->value = -1;

/**
*This stores the node of totalxor of all indexs for lexographical order.
*/
	node * snodes[n];
	cout << "Enter " << n << " numbers : ";
	for (ll i = 0; i < n; ++i)
	{
		ll p;
		cin >> p;
		totalxor = totalxor^p;
		cv->value = p;
		cv->next = new node();
		cv = cv->next;
		snodes[i] = insert1(totalxor,i);
	}	

	ll answer = 0;

/**
*This calculate the number of possible triplets.
*/
	clk = clock();
	node* temp1 = xorlist,*temp2;
	while(temp1!=NULL){
		temp2 = temp1->right;
		ll sum1 = temp2->value;
		temp2 = temp2->right;
		ll j=1;
		while(temp2!=NULL){
			answer += (  (temp2->value)*j - sum1 - j);
			sum1 += temp2->value;
			temp2 = temp2->right;
			j++;
		}
		temp1 = temp1->next;
	}
	cout << "Number of triplets : " << answer << endl;
	clk=clock()-clk;
	cout << "Time: " << 1000000*((double)clk)/CLOCKS_PER_SEC << " microsec\n" << endl;

/**
*This print all triplets in lexographical order
*/
	clk = clock();
	temp1 = xorlist;
	temp2 = temp1->right;
	temp1->right = temp2->right;
	node * temp3=temp2->right;
	ll maxno,ff,ll1;
	if (temp3!=NULL)
	{
		maxno = findMax(temp3);
		ff = temp2->value+1,ll1 = temp3->value;
		for (int i1 = ff+1; i1 <= maxno; ++i1)
		{
			temp3 = temp2->right;
			while(temp3!=NULL){
				if (temp3->value >= i1)
				{
					cout << "(" << ff+1 << "," << i1+1 << "," << temp3->value+1 << ")" << endl;
				}
				temp3=temp3->right;
			} 
		}
	}

	for (ll i = 0; i < n; ++i)
	{
		temp1 = snodes[i];
		temp2 = temp1->right;
		temp1->right = temp2->right;
		temp3 = temp2->right;

		if (temp3==NULL)
		{
			continue;
		}

		ll maxno = findMax(temp3);
		ll ff = temp2->value+1,ll1 = temp3->value;
		for (int i1 = ff+1; i1 <= maxno; ++i1)
		{
			temp3 = temp2->right;
			while(temp3!=NULL){
				if (temp3->value >= i1)
				{
					cout << "(" << ff+1 << "," << i1+1 << "," << temp3->value+1 << ")" << endl;
				}
				temp3=temp3->right;
			} 
		}
	}


	clk=clock()-clk;
	cout << "Time: " << 1000000*((double)clk)/CLOCKS_PER_SEC << " microsec\n" << endl;

	return 0;
}