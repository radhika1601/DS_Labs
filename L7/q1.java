import java.util.Scanner;
import java.lang.Math;
import java.io.FileWriter;
import java.io.PrintWriter;
import java.io.IOException;

class Node implements Comparable<Node>
{
	float x,y;
	Node left,right;
	boolean isXaligned;

	boolean isLeaf()
	{
		if (left == null && right == null)
		{
			return true;
		}
		return false;
	}
	Node(float v1, float v2)
	{
		x = v1;
		y = v2;
		left = null;
		right = null;
	}

	public int compareTo(Node n2)
	{
		if (x != n2.x)
		{
			if (x < n2.x)
			{
				return -1;
			}
			else
			{
				return 1;
			}
		}
		else
		{
			if (y < n2.y)
			{
				return -1;
			}
			else if(y > n2.y)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
	}

	@Override
	public String toString()
	{
		return "\""+x + "," + y + "\"";
	}
}




class Polygon
{
	int n;
	Node[] points;
	public Polygon(int sides)
	{
		n = sides;
		if (sides == 1)
		{
			points = new Node[1];
		}
		else if (sides== 1 || sides == 4)
		{
			points = new Node[2];
		}
		else
		{
			points = new Node[sides];
		}
	}

	boolean isInside(Node point)
	{
		if (n == 1)
		{
			return (points[0].x == point.x && points[0].y == point.y); 
		}
		else if (n == 2)
		{
			if (point.x <= points[1].x && point.x >= points[0].x)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else if (n == 4)
		{
			if (point.x >= points[0].x && point.x <= points[1].x && point.y >= points[0].y && point.y <= points[1].y)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			int n1 = this.points.length;
			int i = 0, count = 0;
			do
			{
				int next = (i+1)%n1;
				if (points[i].x == points[next].x) // vertical line
				{
					if (point.x == points[i].x)
					{
						if (point.y >= Math.min(points[i].y,points[next].y) && point.y <= Math.max(points[next].y,points[i].y))
						{
							return true; // on boundary or on line segment
						}
						else
						{
							return false;
						}
					}
					else if(point.x < points[i].x)
					{
						if (point.y >= Math.min(points[i].y,points[next].y) && point.y <= Math.max(points[next].y,points[i].y))
						{
							count++;
						}
					}
				}
				else // horizontal line
				{
					if (point.y == points[i].y)
					{
						if (point.x >= Math.min(points[i].x,points[next].x) && point.x <= Math.max(points[next].x,points[i].x))
						{
							return true; // on boundary or on line segment
						}
						else
						{
							return false;
						}
					}		
				}
				i = next;
			} while(i != 0);

			return (count%2 == 1);
		}
	}

}


class KDTree
{
	Node root;
	public KDTree()
	{
		root = null;
	}

	public KDTree(Node[] arr)
	{
		root = null;
		sortByX(arr);
		makeUtil(arr);
	}

	void insert(Node node)
	{
		if (root == null)
		{
			root = node;
			node.isXaligned = true;
		}
		else 
		{
			insertUtil(root,node);
		}
	}

	void print(Node node, int indent)
	{
		if (node == null)
		{
			return;
		}
		else
		{
			for (int i = 0; i < indent; i++)
			{
				System.out.print("\t");
			}
			System.out.println(node);
			print(node.left,indent+1);
			print(node.right,indent+1);
		}
	}

	private void makeUtil(Node[] arr)
	{
		if (arr.length == 0)
		{
			return;
		}
		if (arr.length == 1)
		{
			this.insert(arr[0]);
			return;
		}
		int low = 0;
		int high = arr.length-1;
		int mid = arr.length/2;
		Node ins = arr[mid];
		this.insert(ins);

		Node[] arr1 = new Node[mid];
		for (int i = 0; i < arr1.length; i++)
		{
			arr1[i] = arr[i];
		}

		Node[] arr2 = new Node[high - mid];
		for (int i = 0; i < arr2.length; i++)
		{
			arr2[i] = arr[mid + 1 + i];
		}

		if (ins.isXaligned)
		{
			sortByY(arr1);
			sortByY(arr2);
			makeUtil(arr1);
			makeUtil(arr2);
		}
		else
		{
			sortByX(arr1);
			sortByX(arr2);
			makeUtil(arr1);
			makeUtil(arr2);
		}
		
	}

	public void writeToFile(String fileName) throws IOException
	{
		FileWriter fileWriter = new FileWriter(fileName);
		PrintWriter printWriter = new PrintWriter(fileWriter);
		printWriter.println("digraph G{\n\tgraph [ dpi = 1200 ];");
		printDot(root,printWriter);

		printWriter.println("}");
		printWriter.close();

	}

	private void printDot(Node node, PrintWriter printWriter) throws IOException
	{
		if (node.left != null)
		{
			printWriter.println("\t"+node.toString()+"->"+node.left.toString()+";");
			printDot(node.left,printWriter);
		}
		if (node.right != null)
		{
			printWriter.println("\t"+node.toString()+"->"+node.right.toString()+";");
			printDot(node.right,printWriter);
		}
	}


	private void sortByX(Node[] arr)
	{
		int n = arr.length;
        for (int i = 0; i < n-1; i++)
            for (int j = 0; j < n-i-1; j++)
                if (arr[j].x > arr[j+1].x)
                {
                    Node temp = arr[j];
                    arr[j] = arr[j+1];
                    arr[j+1] = temp;
                }
	}

	private void sortByY(Node[] arr)
	{
		int n = arr.length;
        for (int i = 0; i < n-1; i++)
            for (int j = 0; j < n-i-1; j++)
                if (arr[j].y > arr[j+1].y)
                {
                    Node temp = arr[j];
                    arr[j] = arr[j+1];
                    arr[j+1] = temp;
                }
	}

	private void insertUtil(Node n1, Node n2)
	{
		if (n1.isXaligned)
		{
			if (n2.x >= n1.x)
			{
				if (n1.right == null)
				{
					n1.right = n2;
					n2.isXaligned = false;
				}
				else
				{
					insertUtil(n1.right,n2);
				}
			}
			else
			{
				if (n1.left == null)
				{
					n1.left = n2;
					n2.isXaligned = false;
				}
				else
				{
					insertUtil(n1.left,n2);
				}
			}
		}
		else
		{
			if (n2.y >= n1.y)
			{
				if (n1.right == null)
				{
					n1.right = n2;
					n2.isXaligned = true;
				}
				else
				{
					insertUtil(n1.right,n2);
				}
			}
			else
			{
				if (n1.left == null)
				{
					n1.left = n2;
					n2.isXaligned = true;
				}
				else
				{
					insertUtil(n1.left,n2);
				}
			}
		}
	}
}



public class q1
{

	

	public static void main(String[] args) throws java.lang.Exception
	{
		Scanner in = new Scanner(System.in);
		System.out.println("Enter the number of points");
		int n = in.nextInt();

		System.out.println("Enter the x and y coordinates of the points separated by a space");

		Node[] points = new Node[n];

		KDTree mytree;

		for (int i = 0; i < n; i++)
		{
			float x = in.nextFloat();
			float y = in.nextFloat();
			points[i] = new Node(x,y);
		}

		// Arrays.sort(points);

		mytree = new KDTree(points);
		Polygon p1,p2;
		int n1;
		System.out.println("Enter details for first polygon");
		System.out.print("Number of sides : ");
		n1 = in.nextInt();
		p1 = new Polygon(n1);
		System.out.println("Points :");
		for (int i = 0; i < p1.points.length; i++)
		{
			float x = in.nextFloat();
			float y = in.nextFloat();
			p1.points[i] = new Node(x,y);
		}

		System.out.println("Enter details for second polygon");
		System.out.print("Number of sides : ");
		n1 = in.nextInt();
		p2 = new Polygon(n1);
		System.out.println("Points :");
		for (int i = 0; i < p2.points.length; i++)
		{
			float x = in.nextFloat();
			float y = in.nextFloat();
			p2.points[i] = new Node(x,y);
		}

		System.out.println("Solution : ");

		for (int i = 0; i < n; i++)
		{
			Node temp = points[i];
			if (p1.isInside(temp)&&p2.isInside(temp))
			{
				System.out.println(temp);
			}
		}
		System.out.println("\n");
		// mytree.print(mytree.root,0);

		mytree.writeToFile("./q1.dot");
	} 
}