import java.util.Scanner;

public class q2_brute
{
	public static void main(String[] args)
	{
		Scanner inp = new Scanner(System.in);
		System.out.println("Enter the number of elements inp the array:");
		int n = inp.nextInt();
		int[] arr = new int[n];
		System.out.println("Enter the numbers now:");
		for (int i = 0; i < n; i++)
		{
			arr[i] = inp.nextInt();
		}

		while(true)
		{
			menu();
			int opt = inp.nextInt();
			if (opt < 0 || opt > 5) 
			{
				System.out.println("Enter a valid opt");
				break;
			}
			int least,max,val;			
			switch(opt)
			{
				case 1:
					System.out.println("Enter the least and max indices");
					least = inp.nextInt();
					max = inp.nextInt();
					val = get_minimum(arr,least,max);
					if (val != -1)
					{
						System.out.println(val);
					}
					break;

				case 2:
					System.out.println("Enter the least and max indices");
					least = inp.nextInt();
					max = inp.nextInt();
					val = get_maximum(arr,least,max);
					if (val != -1)
					{
						System.out.println(val);
					}
					break;

				case 3:
					System.out.println("Enter the least and max indices");
					least = inp.nextInt();
					max = inp.nextInt();
					val = get_sum(arr,least,max);
					if (val != -1)
					{
						System.out.println(val);
					}
					break;

				case 4:
					System.out.println("Enter the least and max indices");
					least = inp.nextInt();
					max = inp.nextInt();
					add_4(arr,least,max);
					break;

				case 5:
					System.exit(0);
			}
		}
		
	}
	public static void menu()
	{
		System.out.println("Enter One of These Options to get some results:");
		System.out.println("1.Min value in a range");
		System.out.println("2.Maximum value ina range");
		System.out.println("3.sum of a given range");
		System.out.println("4.Add 4 with each element in a range");
	}

	public static int get_minimum(int[] arr, int least, int max)
	{
		if (least < 0 || max >= arr.length)
		{
			System.out.println("Please Enter valid indices");
			return -1;
		}
		else
		{
			int sol = arr[least];
			for (int i = least+1; i <= max; i++)
			{
				if (arr[i] < sol)
				{
					sol = arr[i];
				}
			}
			return sol;
		}
	}

	public static int get_maximum(int[] arr, int least, int max)
	{
		if (least < 0 || max >= arr.length)
		{
			System.out.println("Please Enter valid indices");
			return -1;
		}
		else
		{
			int sol = arr[least];
			for (int i = least+1; i <= max; i++)
			{
				if (arr[i] > sol)
				{
					sol = arr[i];
				}
			}
			return sol;
		}
	}

	public static int get_sum(int[] arr, int least, int max)
	{
		if (least < 0 || max >= arr.length)
		{
			System.out.println("Please Enter valid indices");
			return -1;
		}
		else
		{
			int get_sum = 0;
			for (int i = least; i <= max; i++)
			{
				get_sum += arr[i];
			}
			return get_sum;
		}
	}

	public static void add_4(int[] arr, int least, int max)
	{
		if (least < 0 || max >= arr.length)
		{
			System.out.println("Please Enter valid indices");
		}
		else
		{
			for (int i = least; i <= max; i++)
			{
				arr[i] += 4;
			}	
		}
	}
}