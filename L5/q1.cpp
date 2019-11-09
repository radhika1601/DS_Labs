#include <bits/stdc++.h>
using namespace std;
clock_t clk;
map<int,int> a1,a2,addmap,mult;

void add() {
	
	addmap = a1;
	for(auto i:a2){
		addmap[i.first] += i.second;
	}
	
}

void multiply() {
	
	for(auto i:a1){
		for(auto j:a2){
			mult[(i.first) + (j.first)] += (i.second)*(j.second);
		}
	}
	
}

void printmap(map<int,int> a){
	
	cout << "Coefficient Power" << endl;
	for(auto i:a){
		cout << i.second << "\t" << i.first << endl;
	}
	cout << endl << endl;
}

int main() {

	int n1, n2;
	cout << "Number of terms in expression 1 :" ;
	cin >> n1;
	
	cout << "Coefficient Power" << endl;
	int a,b;
	for (int i = n1-1; i >= 0; --i)
	{
		cin >> a >> b;
		a1[b]=a;
	}

	cout << "Number of terms in expression 2 :" ;
	cin >> n2;
	cout << "Coefficient Power" << endl;
	for (int i = n2-1; i >= 0; --i)
	{
		cin >> a >> b;
		a2[b]=a;
	}

	// add();
	// multiply();

	int x;
	while(1){
		cout << "Enter 1 to add and 2 to multiply"<< endl;
		cin >> x;
		clk = clock();
		if(x == 1) {
			add();
			printmap(addmap);
		}
		else {
			multiply();
			printmap(mult);
		}
		clk=clock()-clk;
		cout << "Time: " << 1000000*((double)clk)/CLOCKS_PER_SEC << " microsec\n" << endl;

	}
	
	return 0;
}
