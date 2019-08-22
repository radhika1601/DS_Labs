/*!
Lab-1 Question 3
Author:
	Name - Radhika Garg
	Roll Number - 18114060
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

u_char **r, **g, **b;
clock_t clk;

/*!
 this function take file path, read that, store in an array, return it
 */

u_char** getArray(char* fname) {
	FILE *f = fopen(fname, "r");
	u_char **array = (u_char **)malloc(953*sizeof(u_char *));

	for (int i = 0; i < 953; ++i) {
		array[i] = (u_char *)malloc(1268*sizeof(u_char));
	}

	for (int i = 0; i < 953; ++i) {
		for(int j = 0; j < 1268; j++) {
			int x;
			if(j == 1267)
				fscanf(f, "%d\n", &x);
			else
				fscanf(f, "%d,", &x);
			array[i][j] = x;
		}
	}
	fclose(f);
	return array;
}

/*!
 read all there files and stores in respective array
 */

void getRGB() {
	r = getArray("/home/radhika/Radhika 18114060 assignment1/2019_CSN-261_L1_Q3_SampleTestcases/Q3_Input/Q3_ip_Red.dat");
	g = getArray("/home/radhika/Radhika 18114060 assignment1/2019_CSN-261_L1_Q3_SampleTestcases/Q3_Input/Q3_ip_Green.dat");
	b = getArray("/home/radhika/Radhika 18114060 assignment1/2019_CSN-261_L1_Q3_SampleTestcases/Q3_Input/Q3_ip_Blue.dat");
}

/*!
 this function stores given array in given file.
*/

void writefile(u_char **c, char *fname) {
	FILE *f = fopen(fname, "w");

	for (int i = 0; i < 953; ++i) {
		for (int j = 0; j < 1267; ++j)
			fprintf(f, "%d,", c[i][j]);
		fprintf(f, "%d\n", c[i][1267]);
	}
	fclose(f);
}

/*!
 this function stores array in respective file.
*/

void saveRGB() {
	writefile(r, "/home/radhika/Radhika 18114060 assignment1/Q3output/red.dat");
	writefile(g, "/home/radhika/Radhika 18114060 assignment1/Q3output/green.dat");
	writefile(b, "/home/radhika/Radhika 18114060 assignment1/Q3output/blue.dat");
}

/*!
 this function checks if the pixelvalue is red and removes if it is red
*/

void remove_Red() {
	for (int i = 0; i < 953; ++i) {
		for (int j = 0; j < 1268; ++j)
		{
			if(r[i][j] > g[i][j] && r[i][j] > b[i][j])
				r[i][j] = (u_char)0;
		}
	}
}


/*!
 this function checks if the pixelvalue is green and removes if it is green
*/
void remove_Green() {
	for (int i = 0; i < 953; ++i) {
		for (int j = 0; j < 1268; ++j)
		{
			if(g[i][j] > r[i][j] && g[i][j] > b[i][j])
				g[i][j] = (u_char)0;
		}
	}
}

/*!
 this function checks if the pixelvalue is blue and removes if it is blue
*/
void remove_Blue() {
	for (int i = 0; i < 953; ++i) {
		for (int j = 0; j < 1268; ++j)
		{
			if(b[i][j] > g[i][j] && b[i][j] > r[i][j])
				b[i][j] = (u_char)0;
		}
	}
}

/*!
 this function preserves all the red colour and removes the green and blue colour 
*/

void red_Only() {
	remove_Blue();
	remove_Green();
}

/*!
 this function preserves all the greeb shade and removes all blue and red colour
*/

void green_Only() {
	remove_Red();
	remove_Blue();
}

/*!
 this function preserves all the blue shade and removes all red and green colour
*/

void blue_Only() {
	remove_Green();
	remove_Red();
}

/*!
 this function gives the RGB value at a particular coordinate or pixel
*/

void pixelValue(int x, int y)
{
	if(x < 1 || y < 1 || x > 953 || y > 1268)
	{
		puts("Enter correct values for x and y coordinates");
	}
	else
	{
		printf("Red: %d\nGreen: %d\nBlue %d\n", r[x-1][y-1], g[x-1][y-1], b[x-1][y-1]);
	}
}

/*!
 this function call every time whenever any operatoin is finished.
*/

void menu() {

	puts("Enter the index to choose from following");
	puts("1.\tRemove all Red shades");
	puts("2.\tRemove all Green shades");
	puts("3.\tRemove all Blue shades");
	puts("4.\tRed Only: Preserve any red shades in the image, but remove all green and blue");
	puts("5.\tGreen Only: Preserve any green shades in the image, but remove all red and blue");
	puts("6.\tBlue Only: Preserve any blue shades in the image, but remove all green and red");
	puts("7.\tPrint the pixel values at a point");

	int a, b;
	int n;
	scanf("%d", &n);
	// clk=clock();
	switch(n) {
		case 1:
			remove_Red();
			break;
		case 2:
			remove_Green();
			break;
		case 3:
			remove_Blue();
			break;
		case 4:
			red_Only();
			break;
		case 5:
			green_Only();
			break;
		case 6:
			blue_Only();
			break;
		case 7:
			printf("Enter x and y coordinates.\n");
			scanf("%d %d", &a, &b);
			pixelValue(a, b);
			break;
		default:
			printf("Please enter a valid choice\n");
	}
}

/*!
 at starting first scan all files and then operations starts...
 and then write all changes value into files.
*/

int main()
{
	getRGB();
	while(1) {
		menu();
		clk=clock()-clk;
		printf("Time: %f microsec\n", 1000000*((double)clk)/CLOCKS_PER_SEC );
	}

	saveRGB();
	return 0;
}