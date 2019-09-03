#include <bits/stdc++.h>
using namespace std;

map<int, int> get_pair_of_indices(int m, int a[], int n) {

	map<int, int> indices;

	int begin = 0;
	int sum = a[0];
	for(int i = 1; i < m; ++i) {
		if(sum == n) {
			indices.insert(pair<int, int>(begin, i-1));
			if(begin >= m) return indices;
			sum = sum-a[begin];
			begin++;
		}
		if(sum <= n) {
			sum += a[i];
		}else {
			sum = sum-a[begin];
			begin++;
		}
	}

	return indices;
}

void get_solution(map<int, int> indices) {
	map<int, int>::iterator itr;
	itr = indices.begin();
	if(indices.empty()) {
		cout << "Not Found" << endl;
		return;
	}
	int i1 = itr->first;
	int i2 = itr->second;
	int min_diff = i2-i1;
	int diff;
	while(itr != indices.end()) {
		diff = itr->second - itr->first;
		if(diff < min_diff) {
			i1 = itr->first;
			i2 = itr->second;
			min_diff = diff;
		}
		itr++;
	}
	cout << "Length of the longest subarray is " << min_diff+1 << endl;
	cout << "Index from " << i1 << " to " << i2 << endl;

}

int main() {
	
	int m;
	cout << "Enter the number of elements in array" << endl;
	cin >> m;

	cout << "Enter the numbers in array : ";
	int a[m];

	for (int i = 0; i < m; ++i){
		cin >> a[i];
	}


	int n;
	cout << "Enter the value of n : ";
	cin >> n;

	map<int, int> indices = get_pair_of_indices(m, a, n);
	get_solution(indices);
}