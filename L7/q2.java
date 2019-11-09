import java.util.Scanner;
import java.lang.Math;
import java.lang.Integer;

class tree_node
{
	int least;
	int most;
	int min;
	int max;
	int sum;
	tree_node left;
	tree_node right;
	tree_node(int least, int most)
	{
		this.least = least;
		this.most = most;
		this.left = null;
		this.right = null;
	}
}

class segment_tree
{
	tree_node root;
	int tree_nodes;

	segment_tree(int[] arr)
	{
		this.root = new tree_node(0,arr.length -1);
		create_utility(arr,root);
		this.tree_nodes = arr.length;
	}

	int max(int least, int most)
	{
		if (least < 0 || most >= tree_nodes)
		{
			System.out.println("Please Enter valid indices");
			return -1;
		}
		else
		{
			return get_maximum(root,most,least);
		}
	}

	int min(int least,int most)
	{
		if (least < 0 || most >= tree_nodes)
		{
			System.out.println("Please Enter valid indices");
			return -1;
		}
		else
		{
			return get_minimum(root,most,least);
		}
	}

	int sum(int least, int most)
	{
		if (least < 0 || most >= tree_nodes)
		{
			System.out.println("Please Enter valid indices");
			return -1;
		}
		else
		{
			return retr_sum(root,most,least);
		}	
	}

	void add4(int least, int most)
	{
		if (least < 0 || most >= tree_nodes)
		{
			System.out.println("Please Enter valid indices");
		}
		else
		{
			add_4(root,least,most);
		}
	}

	private void create_utility(int[] arr, tree_node tree_node)
	{
		if (tree_node.least == tree_node.most)
		{
			tree_node.min = tree_node.max = tree_node.sum = arr[tree_node.least];
		}
		else
		{
			tree_node.left = new tree_node(tree_node.least,(tree_node.least+tree_node.most)/2);
			tree_node.right = new tree_node(((tree_node.least+tree_node.most)/2) + 1,tree_node.most);
			create_utility(arr,tree_node.left);
			create_utility(arr,tree_node.right);
			tree_node.sum = tree_node.left.sum + tree_node.right.sum;
			tree_node.min = Math.min(tree_node.left.min,tree_node.right.min);
			tree_node.max = Math.max(tree_node.left.max,tree_node.right.max);
		}
	}

	private int get_minimum(tree_node tree_node, int most, int least)
	{
		if (tree_node.least >= least && tree_node.most <= most)
		{
			return tree_node.min;
		}
		else if (tree_node.most < least || tree_node.least > most)
		{
			return Integer.MAX_VALUE;
		}
		else
		{
			return Math.min(get_minimum(tree_node.left,most,least),get_minimum(tree_node.right,most,least));
		}
	}

	private int get_maximum(tree_node tree_node, int most, int least)
	{
		if (tree_node.least >= least && tree_node.most <= most)
		{
			return tree_node.max;
		}
		else if (tree_node.most < least || tree_node.least > most)
		{
			return Integer.MIN_VALUE;
		}
		else
		{
			return Math.max(get_maximum(tree_node.left,most,least),get_maximum(tree_node.right,most,least));
		}
	}

	private int retr_sum(tree_node tree_node, int most, int least)
	{
		if (tree_node.least >= least && tree_node.most <= most)
		{
			return tree_node.sum;
		}
		else if (tree_node.most < least || tree_node.least > most)
		{
			return 0;
		}
		else
		{
			return retr_sum(tree_node.left,most,least) + retr_sum(tree_node.right,most,least);
		}
	}

	private void add_4(tree_node tree_node, int least, int most)
	{
		if (least == most)
		{
			tree_node.sum += 4;
			tree_node.min += 4;
			tree_node.max += 4;		
		}
		else if (tree_node.most < least || tree_node.least > most)
		{
			return;
		}
		else
		{
			add_4(tree_node.left,least,(least+most)/2);
			add_4(tree_node.right,((least+most)/2 + 1),most);
			tree_node.min = Math.min(tree_node.left.min,tree_node.right.min);
			tree_node.max = Math.max(tree_node.left.max,tree_node.right.max);
			tree_node.sum = tree_node.left.sum + tree_node.right.sum;
		}
	}
}


public class q2
{
	public static void main(String[] args)
	{
		Scanner inp = new Scanner(System.in);
		System.out.println("Enter the number of elements");
		int n = inp.nextInt();
		int[] arr = new int[n];
		System.out.println("Enter the numbers");
		for (int i = 0; i < n; i++)
		{
			arr[i] = inp.nextInt();
		}
		segment_tree mytree = new segment_tree(arr);

		while(true)
		{
			menu();
			int opt = inp.nextInt();
			int least,most,val;			
			switch(opt)
			{
				case 1:
					System.out.println("Enter indices");
					least = inp.nextInt();
					most = inp.nextInt();
					val = mytree.min(least,most);
					if (val != -1)
					{
						System.out.println(val);
					}
					break;

				case 2:
					System.out.println("Enter indices");
					least = inp.nextInt();
					most = inp.nextInt();
					val = mytree.max(least,most);
					if (val != -1)
					{
						System.out.println(val);
					}
					break;

				case 3:
					System.out.println("Enter indices");
					least = inp.nextInt();
					most = inp.nextInt();
					val = mytree.sum(least,most);
					if (val != -1)
					{
						System.out.println(val);
					}
					break;

				case 4:
					System.out.println("Enter indices");
					least = inp.nextInt();
					most = inp.nextInt();
					mytree.add4(least,most);
					break;

				case 5:
					System.exit(0);
			}
		}
		
	}
	public static void menu()
	{
		System.out.println("Enter One of These Options to get some results:");
		System.out.println("1.Find Min value inp a range");
		System.out.println("2.Find Max value inp a range");
		System.out.println("3.Find The Sum ");
		System.out.println("4.Add 4 with each element");
	}
}