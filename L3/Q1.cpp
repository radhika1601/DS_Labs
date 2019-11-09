/** 
*@file Q1.cpp
*@brief this header file will contain all required 
*definitions and basic utilities functions.
*
*@author Radhika
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>
#define RED true
#define BLACK false
using namespace std;
clock_t clk;


template <class T>
void printInorderTree(T* currentNode)
{
	if (currentNode == NULL)
		return;
	else
	{
		printInorderTree(currentNode->left);
		cout << currentNode->val << " ";
		printInorderTree(currentNode->right);
	}
}

class RedBlackNode
{
	public :
		int val;
		bool colour;
		RedBlackNode* parent;
		RedBlackNode* left;
		RedBlackNode* right;

		RedBlackNode(int value)
		{
			this->val = value;
			this->colour = RED;
			this->parent = NULL;
			this->right = NULL;
			this->left = NULL;
		}
};

class RedBlackTree
{
	private:

/**
*This method get node tree height form that node to leaf
*@param node reads the node of redBlackNode
*/
		int getHeightOfNode(RedBlackNode* node)
		{
			if (node ==  NULL)
				return -1;
			else
				return max(getHeightOfNode(node->left)+1,getHeightOfNode(node->right)+1);
		}

/**
*This method print whole tree with indentation
*@param node reads the node of redBlackNode
*@param tabGaps reads int stores level or height form root
*/
		void printTreeIndent(RedBlackNode* node,int tabGaps)
		{
			if (node == NULL)
				return;
			else
			{
				for (int i = 0; i < tabGaps; ++i)
					cout << "\t\t";

				//cout << node->val << "[" << abs(getHeightOfNode(node->right)-getHeightOfNode(node->left)) << "]";
				string str = to_string(node->val)+"["+to_string( abs(getHeightOfNode(node->right)-getHeightOfNode(node->left)) )+"]";
				if (node->colour == BLACK)
					cout << "\033[1;34m" << str << "\033[0m\n";
				else
					cout << "\033[1;31m"<<str<<"\033[0m\n";
				cout << endl;

				printTreeIndent(node->left,tabGaps+1);
				printTreeIndent(node->right,tabGaps+1);
			}
		}

/**
*This method rotate Right side at specific node of tree 
*@param node reads the node of redBlackNode
*/
		void rotateRight(RedBlackNode* node)
		{
			RedBlackNode* ptr = new RedBlackNode(node->val);
			ptr->right = node->right;
			ptr->colour = node->colour;

			if (node->left->right != NULL)
				ptr->left = node->left->right;

			node->val = ptr->left->val;
			node->colour = ptr->left->colour;
			node->right = ptr;

			if (ptr->left != NULL)
				ptr->left->parent = ptr;

			if (ptr->right != NULL)
				ptr->right->parent = ptr;

			ptr->parent = node;

			if (node->left->left != NULL)
				node->left = node->left->left;
			else
				node->left = NULL;

			if (node->left != NULL)
				node->left->parent = node;
		}

/**
*This method rotate Left side at specific node of tree 
*@param node reads the node of redBlackNode
*/
		void rotateLeft(RedBlackNode* node)
		{

            RedBlackNode* ptr = new RedBlackNode(node->val);
            ptr->left = node->left;
            ptr->colour = node->colour;

            if(node->right->left) 
            	ptr->right = node->right->left; 
            
            node->val = node->right->val;
            node->left = ptr;

            if(ptr->left)
            	ptr->left->parent = ptr;

            if(ptr->right)
            	ptr->right->parent = ptr;

            ptr->parent = node;
  
            if(node->right->right)
            	node->right = node->right->right;
            else 
            	node->right = NULL; 
  
            if(node->right)
            	node->right->parent = node;  
		}

	public:
		int size;
		RedBlackNode* root;

		RedBlackTree()
		{
			this->root = NULL;
			this->size = 0;
		}


		void FixTree(RedBlackNode* ptr)
		{
			while(ptr->parent->colour == RED)
			{
				RedBlackNode* grdParent = ptr->parent->parent;
				RedBlackNode* uncle = this->root;

				if (ptr->parent == grdParent->left)
				{
					if (grdParent->right != NULL)
						uncle = grdParent->right;

					if (uncle->colour == RED)
					{
						ptr->parent->colour = BLACK;
						uncle->colour = BLACK;
						grdParent->colour = RED;

						if (grdParent != this->root)
							ptr = grdParent;
						else
							break;
					}
					else if (ptr == grdParent->left->right)
						rotateLeft(ptr->parent);
					else
					{
						ptr->parent->colour = BLACK;
						grdParent->colour = RED;
						rotateRight(grdParent);

						if (grdParent != this->root)
							ptr = grdParent;
						else
							break;
					}
				}

				else
				{
					if (grdParent->left != NULL)
						uncle = grdParent->left;
					
					if (uncle->colour == RED)
					{
						ptr->parent->colour = BLACK;
						uncle->colour = BLACK;
						grdParent->colour = RED;

						if (grdParent != this->root)
							ptr = grdParent;
						else
							break;
					}
					else if (ptr == grdParent->right->left)
						rotateRight(ptr->parent);
					else
					{
						ptr->parent->colour = BLACK;
						grdParent->colour = RED;
						rotateLeft(grdParent);

						if (grdParent != this->root)
							ptr = grdParent;
						else
							break;
					}
				}
			}
			this->root->colour = BLACK;
		}
/**
*This method inser new node in tree 
*@param data is int that stores value of node
*/
		void insertNode(int data)
		{
			if (this->root == NULL)
			{
				root = new RedBlackNode(data);
				root->colour = BLACK;
			}
			else
			{
				RedBlackNode* node = new RedBlackNode(data);
				RedBlackNode* temp = this->root;
				while(temp != NULL)
				{
					if (data > temp->val)
					{
						if (temp->right == NULL)
						{
							temp->right = node;
							temp->right->colour = RED;
							temp->right->parent = temp;
							break;
						}
						else
							temp = temp->right;
					}
					else
					{
						if (temp->left == NULL)
						{
							temp->left = node;
							temp->left->colour = RED;
							temp->left->parent = temp;
							break;
						}
						else
							temp = temp->left;
					}
				}
				this->size++;
				FixTree(node);
			}
		}

/**
*This method print tree with gaps according to height from root 
*/
		void printTreeIndentWise()
		{
			this->printTreeIndent(this->root,0);
		}

/**
*This method print tree in inorder Traversal format
*/
		void printInorderTreeTraversal()
		{
			printInorderTree(this->root);
			cout << endl;
		}
};

class Node
{
	public:
		int val;
		Node* right;
		Node* left; 

		Node(int value)
		{
			this->val = value;
			this->right = NULL;
			this->left = NULL;
		}
};

class BinarySearchTree
{
	private:

/**
*This method get node tree height form that node to leaf
*@param node reads the node of Node
*/
		int getHeightOfNode(Node* node)
		{
			if (node ==  NULL)
				return 0;
			else
				return max(getHeightOfNode(node->left),getHeightOfNode(node->right))+1;
		}

/**
*This method print whole tree with indentation
*@param node reads the node of Node
*@param tabGaps reads int stores level or height form root
*/
		void printTreeIndent(Node* node,int tabGaps)
		{
			if (node == NULL)
				return;
			else
			{
				for (int i = 0; i < tabGaps; ++i)
					cout << "\t\t";
				cout << node->val << "[" << getHeightOfNode(node->right)-getHeightOfNode(node->left) << "]" << endl;
				printTreeIndent(node->left,tabGaps+1);
				printTreeIndent(node->right,tabGaps+1);
			}
		}

/**
*This method delete whole tree 
*@param node reads the node of Node
*/
		void deleteNode(Node* node)
		{
			if (node == NULL)
				return;
			else
			{
				deleteNode(node->left);
				deleteNode(node->right);
				delete node;
			}
		}

	public:
		int size;
		Node* root;

		BinarySearchTree()
		{
			this->size=0;
			this->root = NULL;
		}

		~BinarySearchTree()
		{
			this->deleteNode(this->root);
		}

/**
*This method insert new node in tree 
*@param data is int that stores value of node
*/
		void insertNode(int data)
		{
			if (this->root == NULL)
				this->root = new Node(data);
			else
			{
				Node* curr = this->root;
				Node* parent = this->root;
				while(curr != NULL)
				{
					parent=curr;
					if (data > curr->val)
						curr = curr->right;
					else
						curr = curr->left;
				}
				if (data > parent->val)
					parent->right = new Node(data);
				else
					parent->left = new Node(data);
			}
			this->size++;
		}

/**
*This method print tree with gaps according to height from root 
*/
		void printTreeIndentWise()
		{
			this->printTreeIndent(this->root,0);
		}

/**
*This method print tree in inorder Traversal format
*/
		void printInorderTreeTraversal()
		{
			printInorderTree(this->root);
			cout << endl;
		}
};

BinarySearchTree* bst;
BinarySearchTree* avl;
RedBlackTree* rbt;

/**
*This method insert new node in both tree 
*/

void insert()
{
	cout << "Enter the number to insert" << endl;
	int value = 0;
	cin >> value;
	bst->insertNode(value);
	rbt->insertNode(value);
}

void BSTtraverse(int* arr,int &counter,Node* node)
{
	if (node == NULL)
		return;
	else
	{
		BSTtraverse(arr,counter,node->left);
		arr[counter++] = node->val;
		BSTtraverse(arr,counter,node->right);
	}
}

/**
*This method get node tree height form that node to leaf
*@param root reads the node of Node
*/

static int getHeightOfNode (  Node * root ){
   if(!root)
        return 0;
    return max(getHeightOfNode(root->left)+1,getHeightOfNode(root->right)+1);
} 

/**
*This method get Balance or difference of height of left and right child
*@param N reads the node of redBlackNode
*/

int getBalanceOfNode(Node *N)  {  
    if (N == NULL)  
        return 0;  
    return getHeightOfNode(N->left) - getHeightOfNode(N->right);  
}

/**
*This method rotate Left side at specific node of tree
*@param node reads the node of Node
*/

static Node *leftRotation( Node *temp)  {  
     Node *temp1 = temp->right;  
     Node *T2 = temp1->left;  
  
    // Perform rotation  
    temp1->left = temp;  
    temp->right = T2;  

    return temp1;  
} 

/**
*This method rotate Right side at specific node of tree 
*@param node reads the node of redBlackNode
*/

static Node *rightRotation( Node *temp1) {  
     Node *temp = temp1->left;  
     Node *T2 = temp->right;  
  
    // Perform rotation  
    temp->right = temp1;  
    temp1->left = T2;  
  
    return temp;  
}

/**
*This method insert new node in AVL tree 
*@param node reads the node of Node
*@param data as int stores value of node
*/

Node* insertInAvlTree(Node* node, int data) {  
    if (node == NULL)  
        return(new Node(data));  
  
    if (data < node->val)  
        node->left = insertInAvlTree(node->left, data);  
    else if (data > node->val)  
        node->right = insertInAvlTree(node->right, data);  
    else 
        return node;  
  
    int balance = getBalanceOfNode(node);  
  
    if (balance > 1 && data < node->left->val)  
        return rightRotation(node);  
  
    if (balance < -1 && data > node->right->val)  
        return leftRotation(node);  
  
    if (balance > 1 && data > node->left->val)  
    {  
        node->left = leftRotation(node->left);  
        return rightRotation(node);  
    }  
  
    if (balance < -1 && data < node->right->val)  
    {  
        node->right = rightRotation(node->right);  
        return leftRotation(node);  
    }  
  
    return node;  
}

void createAVLHandler()
{
	if (avl != NULL)
	{
		delete avl;
		avl = new BinarySearchTree();
	}
	else
		avl = new BinarySearchTree();

	int counter=0;
	int* traversal = new int[bst->size];
	BSTtraverse(traversal,counter,bst->root);
	for(int i = 0; i < bst->size; i++) 
		avl->root = insertInAvlTree(avl->root, traversal[i]);
}

/**
*This method print all three tree in inorder traversal
*/

void print()
{
	cout << endl;
	cout << "The inorder traversal for the BST is" << endl;
	bst->printInorderTreeTraversal();

	if(avl == NULL)
		cout << "The AVL tree hasn't been created yet" << endl;
	else
	{
		cout << "The inorder traversal for the AVL tree is " << endl;
		avl->printInorderTreeTraversal();
	}

	cout << "The inorder traversal for the Red-Black Tree is" << endl;
	rbt->printInorderTreeTraversal();
	
}

template <class T>
void printAllPaths(T* node,vector<int> vec)
{
	if (node == NULL)
		return;
	vec.push_back(node->val);
	if (node->right == NULL && node->left == NULL)
	{
		for(auto it = vec.begin(); it != vec.end(); it++)
		{
			if (it == vec.begin())
				cout << *it;
			else
				cout << "->" << *it;
		}
		cout << endl;
	}
	else
	{
		printAllPaths(node->left,vec);
		printAllPaths(node->right,vec);
	}
}

template <class T>
void printAllPathsHelper(T* node)
{
	if (node == NULL)
	{
		return;
	}
	vector<int> vec;
	printAllPaths(node,vec);
	printAllPathsHelper(node->left);
	printAllPathsHelper(node->right);
}

void printAllPathsHandler()
{
	cout << "For BST : " << endl;
	printAllPathsHelper(bst->root);

	cout << "For AVL Tree : " << endl;
	printAllPathsHelper(avl->root);

	cout << "For Red-Black Tree : " << endl;
	printAllPathsHelper(rbt->root);
}

void printTreeIndentHandler()
{
	cout << "For BST : " << endl;
	bst->printTreeIndentWise();

	cout << "For AVL Tree : " << endl;
	avl->printTreeIndentWise();

	cout << "For Red-Black Tree : " << endl;
	rbt->printTreeIndentWise();
}


void menuBar()
{
	cout << endl;
	cout << "1.Insert a node in Both tree" << endl;
	cout << "2.Create AVL from BST" << endl;
	cout << "3.Print Inorder traversal of Both tree" << endl;
	cout << "4.Display all paths in Both tree" << endl;
	cout << "5.Print Both Tree using level-wise Indentation" << endl;
	cout << "6.Exit this program" << endl;

	int option=0;
	cin >> option;
	clk = clock();
	switch(option)
	{
		case 1:
			insert();
			break;

		case 2:
			createAVLHandler();
			break;

		case 3:
			print();
			break;

		case 4:
			printAllPathsHandler();
			break;

		case 5:
			printTreeIndentHandler();
			break;

		case 6:
			exit(0);

		default:
			cout << "Enter a correct option" << endl;
			break;
	}
	clk=clock()-clk;
	cout << "Time: " << 1000000*((double)clk)/CLOCKS_PER_SEC << " microsec\n" << endl;

	cout << endl;
}

int main(void)
{
	bst = new BinarySearchTree();
	rbt = new RedBlackTree();
	while(true)
	{
		menuBar();
	}

	return 0;
}
