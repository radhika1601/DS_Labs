/** 
*@file q1.c
*@brief this header file will contain all required 
*definitions and basic utilities functions.
*
*@author Radhika
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**
*This method reads the string in the file
*@param fname is the name of the file to be read
*@param s_ reads the file line by line 
*@param s is the complete text in the file
*/
char* get_string(const char* fname);


/**
*This method writes the string in the file
*@param fname is the name of file in which string is to be written
*@param s is the string to be written
*/
void put_string(const char* fname, char* s);


/**
*This method encrypts the string using given n, a, b
*@param l is the length of the string
*@param l$ is the length of the encrypted string that is a multiple of n
*/
char* transpose(char* s, int n, int a, int b);


/**
*This method decrypts the string using given n, a, b
*@param l is the length of encrypted string
*@param decrypted is the decrypted string
*/
char* inverseTranspose(char* s, int n, int a, int b);


/**
*This method compares the text of the file with the text in output file
*@param s1 is the string in the inputFile
*@param s2 is the string in the decryptedOutput File
*/
void compare_files(const char* fname);

clock_t clk;
int final_length;

char* transpose(char* s, int n, int a, int b) {
	
	clk = clock();
	int l = strlen(s);
	int l$ = l;
	final_length = l$;
	if(l%n != 0) {
		l$ = l+ (n - l%n);
	}
	char* encrypted = malloc(l$);

	for(int x = 0; x < l$/n; x++) {
		for(int y = 0; y < n; y++) {
			int i = x*n+y;
			int j = x*n + (a*i+b)%n;

			if(j < l)
				encrypted[i] = s[j];
			else 
				encrypted[i] = '\0';
		}
	}
	printf("%s\n", encrypted);
	clk=clock()-clk;
	printf("Time: %f microsec\n", 1000000*((double)clk)/CLOCKS_PER_SEC );

	return encrypted;
}

char* inverseTranspose(char* s, int n, int a, int b) {
	
	clk = clock();
	int l = strlen(s);

	l = l + (n - l%n);

	char* decrypted = malloc(l);

	for(int x = 0; x < l/n; x++) {
		for(int y = 0; y < n; y++) {
			int i = x*n + y;
			int j = x*n + (a*i+b)%n;

			decrypted[j] = s[i];
		}
	}
	printf("%s\n", decrypted);
	clk=clock()-clk;
	printf("Time: %f microsec\n", 1000000*((double)clk)/CLOCKS_PER_SEC );
	return decrypted;
}

char* get_string(const char* fname) {
	FILE *f = fopen(fname, "r");
	char* s = malloc(1000);
	char* s_ = malloc(100);
	while(fgets(s_, 100, f) != NULL)
		strcat(s, s_);
	fclose(f);
	free(s_);
	return s;

}

void put_string(const char* fname, char* s) {
	
	FILE *f = fopen(fname, "w");

	fprintf(f, "%s", s);

	fclose(f);
}

void compare_files(const char* fname) {
	clk = clock();
	char *s1 = get_string(fname);
	char* s2 = get_string("decryptedOutputfile.txt");

	int x = strcmp(s1, s2);
	if(x == 0)
		printf("Both files are equivalent.\n");
	else
		printf("Files have different texts.\n");
	clk = clock()-clk;
	printf("Time: %f microsec\n", 1000000*((double)clk)/CLOCKS_PER_SEC );
}

int main(int argc, char const *argv[]) {

 	if(argc < 5)
 		exit(1);
 	int n = atoi(argv[1]);
 	int a = atoi(argv[2]);
 	int b = atoi(argv[3]);
 	char const *fname = argv[4];

	if(n < 1)
 		exit(2);

 	char* s = get_string(fname);
 	s = transpose(s, n, a, b);
 	put_string("outputfile.txt", s);
 	s = inverseTranspose(s, n, a, b);
 	put_string("decryptedOutputfile.txt", s);
 	compare_files(fname);

 	return 0;
}