/** 
*@file MAT.c
*@brief this header file will contain all required 
*definitions and basic utilities functions.
*
*@author Radhika
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

/// structure for the nodes in QuadTree
struct qnode {
	//pointer to north-west quadrant
	struct qnode *nw;
	///pointer to north-east quadrant
	struct qnode *ne;
	///pointer to south-west quadrant
	struct qnode *sw;
	///pointer to south-east quadrant
	struct qnode *se;
	/// size of the block that it reprsents
	int size;
	///-1 grey, 0 white, 1 black
	int color;
	/// number assigned to the leaf-nodes else 0
	int num;
};

///global variable to assign numbers to the leaf nodes
int number = 1;

/**
*This helper method will be used to create 2-d dynamic array
*@param n is the order of the 2-d array to be returned  
*/
int** newArray(int n);

/**
*This helper method given the order of the 2-d matrix given in the File
*@param fname is the name of the Input file
*@param s and @param s_ are used to get the number of bits in the first line of given file to get n
*/
int get_n(const char* fname);

/**
*This helper method gives the 2-d matrix in the matrix
*@param fname is the name of the Input file
*@param n is the order of the matrix given in 
*/
int** get_file_matrix(const char* fname, int n);

/**
*This helper method gives the next power of 2
*@param n is the order of matrix given in the file 
*/
int nextPowerof2(int n);

/**
*This method maps the given matrix to the bottom right corner of given matrix in file
*@param a is the given matrix in file
*@param na is the size of the matrix given in file
*@param n is the size of the new matrix eg. 8 if na=6
*/
int** get_matrix(int** a, int n, int na);

/**
*This method maps the QuadTree in a maximal array
*@param node is the qnode that is going be created
*@param a is the matrix of bits that is to be mapped in the quadNode
*@param a1 is the north-west partition of a
*@param a2 is the north-east partition of a
*@param a3 is the south-west partition of a
*@param a4 is the south-east partition of a
*/
struct qnode* quad(struct qnode *node, int** a);


/**
*This method maps the QuadTree in a maximal array
*@param node is the node to be checked/mapped
*@param a is the matrix of the maximal array corresponding to the QuadNode
*@param a1 is the north-west partition of a
*@param a2 is the north-east partition of a
*@param a3 is the south-west partition of a
*@param a4 is the south-east partition of a
*/
int** quadArray(struct qnode* node);

/**
*This helper method gives log(n) to the base 2
*/
unsigned int Log2n(int n);

/**
*This helper method gives the level of the node(considering root to be level 0)
*@param node is the QuadNode whose level is to be returned
*@param n is the the size of the whole matrix
*/
int getLevel(struct qnode* node, int n);

/**
*This method prints the Maximal array that we get from the method QuadArray
*/
void printQuad(struct qnode* root);

/**
*This method prints the QuadTree as given in the Question all the leaf nodes with their number, color, level
*/
void printQuadTree(struct qnode* root, int n);

/// to measure time
clock_t clk;

int** newArray(int n) {
	int **a = (int **)malloc(sizeof(int*)*n);
	for (int i = 0; i < n; ++i)
		a[i] = (int *)malloc(sizeof(int)*n);

	return a;
}


int get_n(const char* fname) {
	FILE *f = fopen(fname, "r");
	char* s = malloc(100);
	if(f == NULL) {
		printf("File does not exist.\n");
		exit(1);
	}
	fgets(s, 100, f);

	char * s_ = malloc(100);
	s_ = strtok(s, " ");

	int i = 0;
	while(s_ != NULL) {
		i++;
		s_ = strtok(NULL, " ");
	}

	fclose(f);
	free(s);
	free(s_);
	return i;
}

int** get_file_matrix(const char* fname, int n) {

	if(n < 1) {
		printf("Error: Empty File\n");
		exit(1);
	}
	FILE *f = fopen(fname, "r");
	
	if(f == NULL)
		exit(1);

	int** a = newArray(n);

	char* s = malloc(100);
		char* s_ = malloc(100);

	for(int x = 0; x < n; ++x) {
		fgets(s, 100, f);
		s_ = strtok(s, " ");
		for(int y = 0; y < n; ++y) {
			a[x][y] = atoi(s_);
			s_ = strtok(NULL, " ");
		}
	}
	fclose(f);

	return a;
}

int nextPowerof2(int n) {
	unsigned count = 0;
	if (n && !(n & (n - 1))) 
    return n; 
  
	while( n != 0) 
	{ 
	    n >>= 1; 
	    count += 1; 
	} 
	  
	return 1 << count; 
}

int** get_matrix(int** a, int n, int na) {
	
	if(n == na)
		return a;
	int m = n - na;
	int** matrix = newArray(n);
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < n; ++j) {
			if(i < m || j < m)
				matrix[i][j] = 0;
			else
				matrix[i][j] = a[i-m][j-m];
		}
	}

	return matrix;	
}


struct qnode* quad(struct qnode *node, int** a) {
	int n = node->size;

	if(n == 1) {
		node->color = a[0][0];
		node->num = number;
		node->nw = node->ne = node->se = node->sw = NULL;
		number++;
		return node;
	}
	int x = a[0][0];
	bool b = true;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if(x != a[i][j]) {
				b = false;
				break;
			}
		}
		if(b == false)
			break;
	}

	if(b == true) {
		node->nw = node->ne = node->se = node->sw = NULL;
		node->color = a[0][0];
		node->num = number;
		number++;
		return node;
	}
	else {

		node->num = 0;
		int** a1 = newArray(n/2);
		int** a2 = newArray(n/2);
		int** a3 = newArray(n/2);
		int** a4 = newArray(n/2);
		node->color = -1;

		for (int i = 0; i < n/2; ++i) {
			for (int j = 0; j < n/2; ++j) {
				a1[i][j] = a[i][j];
				a2[i][j] = a[i][n/2+j];
				a3[i][j] = a[i+n/2][j];
				a4[i][j] = a[n/2+i][n/2+j];
			}
		}

		node->nw = (struct qnode *)malloc(sizeof(struct qnode));
		node->ne = (struct qnode *)malloc(sizeof(struct qnode));
		node->sw = (struct qnode *)malloc(sizeof(struct qnode));
		node->se = (struct qnode *)malloc(sizeof(struct qnode));

		node->nw->size = node->ne->size = node->sw->size = node->se->size = n/2;

		node->nw = quad(node->nw, a1);
		node->ne = quad(node->ne, a2);
		node->sw = quad(node->sw, a3);
		node->se = quad(node->se, a4);
		for(int i = 0; i < n/2; ++i) 
			free(a1[i]);
		free(a1);
		for(int i = 0; i < n/2; ++i) 
			free(a2[i]);
		free(a2);
		for(int i = 0; i < n/2; ++i) 
			free(a3[i]);
		free(a3);
		for(int i = 0; i < n/2; ++i) 
			free(a4[i]);
		free(a4);
	}

	return node;
}

int** quadArray(struct qnode* node) {

	int n = node->size;
	int** a = newArray(n);
	if(node->color != -1) {
		for(int i = 0; i < n; ++i) {
			for(int j = 0; j < n; ++j){
				a[i][j] = node->num;
			}
		}
	}else {

		int** a1 = newArray(n/2);
		int** a2 = newArray(n/2);
		int** a3 = newArray(n/2);
		int** a4 = newArray(n/2);
		a1 = quadArray(node->nw);
		a2 = quadArray(node->ne);
		a3 = quadArray(node->sw);
		a4 = quadArray(node->se);

		for (int i = 0; i < n/2; ++i) {
			for (int j = 0; j < n/2; ++j) {
				a[i][j] = a1[i][j];
				a[i][n/2+j] = a2[i][j];
				a[n/2+i][j] = a3[i][j];
				a[n/2+i][n/2+j] = a4[i][j];
			}
		}

		for(int i = 0; i < n/2; ++i) 
			free(a1[i]);
		free(a1);
		for(int i = 0; i < n/2; ++i) 
			free(a2[i]);
		free(a2);
		for(int i = 0; i < n/2; ++i) 
			free(a3[i]);
		free(a3);
		for(int i = 0; i < n/2; ++i) 
			free(a4[i]);
		free(a4);

	}	
	return a;
}

unsigned int Log2n(int n) {
	return n>1 ? 1+Log2n(n/2) : 0;
}

int getLevel(struct qnode* node, int n) {
	int x = Log2n(n);
	return x-Log2n(node->size);
}

void printQuad(struct qnode* root) {
	
	int n = root->size;

	int** a = quadArray(root);

	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < n; ++j) {
			printf("%d ", a[i][j]);
		}
		printf("\n");
	}

	for(int i = 0; i < n; ++i) 
		free(a[i]);
	free(a);

}

void printQuadTree(struct qnode* root, int n) {

	clk = clock();
	struct qnode* node = root;

	if(node->color != -1) {
		int level = getLevel(node, n);
		printf("(%d,%d,%d)\n", node->num, node->color, level);
	}else {
		printQuadTree(node->nw, n);
		printQuadTree(node->ne, n);
		printQuadTree(node->sw, n);
		printQuadTree(node->se, n);
	}

	if(getLevel(root, n) == 0) {
		clk = clock()-clk;
		printf("Time: %f microsec\n", 1000000*((double)clk)/CLOCKS_PER_SEC );

	}
	
}

int main(int argc, char const *argv[])
{

	struct qnode *root = (struct qnode *)malloc(sizeof(struct qnode));

	const char* fname = "inputQ2.txt";

	int na = get_n(fname);
	int** a = get_file_matrix(fname, na);
	int n = nextPowerof2(na);
	int** matrix = get_matrix(a, n, na);

	root->size = n;
	clk = clock();
	root = quad(root, matrix);
	printf("The matrix:\n");
	printQuad(root);
	clk = clock()-clk;
	printf("Time: %f microsec\n", 1000000*((double)clk)/CLOCKS_PER_SEC );
	printf("\nThe QuadTree\n");
	printQuadTree(root, n);

	return 0;
}