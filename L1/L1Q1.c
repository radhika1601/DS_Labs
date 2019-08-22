/*!
Lab-1 Question 1
Author:
	Name - Radhika Garg
	Roll Number - 18114060
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*!
This struct data structure for store details of a particular student
*/

struct student
{
	int roll_no;
	char name[50];
	char dob[20];
	char address[100];
	long long int phone_no;
	struct student *previous, *next;
};

long long int unusedRoll[10000];
int frontRoll,rearRoll;
long long int newAssignRoll = 101;
struct student *head;
clock_t clk;

struct student *createnode(int rollno,char name[],long long int phoneno,char addr[], char dob[]);
void printnode(struct student *s);
int deletefromDL(int rn);
int modify(int rn);
void scanCSV();
void insert();
int search(int rn);
void printList();
int length();
void sortbyname();
void menu();

/*! 
This function push a new roll no in queue which is delete from Double linked list
*/

void enQueue(int rn) {

	unusedRoll[rearRoll]=rn;
	rearRoll++;
}

/*!
This function return -1 whenever queue is empty
either return front value of queue
*/

long long int deQueue() {

	if(frontRoll >= rearRoll)
		return -1;

	long long int rv = unusedRoll[frontRoll];
	frontRoll++;
	return rv;
}

/*!
 this function create a node and set all attibutes of that node and return it.
 */

struct student *createnode(int rollno,char name[],long long int phoneno,char addr[], char dob[])
{
	struct student *temp = (struct student *)malloc(sizeof(struct student));
	temp->roll_no = rollno;
	strcpy(temp->name, name);
	strcpy(temp->dob, dob);
	strcpy(temp->address, addr);
	temp->phone_no = phoneno;
	temp->previous = NULL;
	temp->next = NULL;
	return temp;
}

/*!
this function print a particular node of student.
*/

void printnode(struct student *s){

	printf("\n");
	printf("Roll No.: %d\n",s->roll_no);
	printf("Name: %s\n",s->name);
	printf("Address: %s\n",s->address);
	printf("DOB: %s\n",s->dob);
	printf("Phone Number: %lld\n",s->phone_no);
	printf("\n");
}

/*!
 this function bacislly delete node from double linked list of given roll number and return 1;
 if roll number is not found return 0
 */

int deletefromDL(int rn){
	if (head->roll_no==rn)
	{
		if (head->next==head)
		{
			head=NULL;
		}
		else{
			head->previous->next=head->next;
			head->next->previous=head->previous;
			head=head->next;
		}
		return 1;
	}
	else{
		struct student *temp = head->next;
		while(temp!=head){
			if (temp->roll_no==rn)
			{
				temp->previous->next=temp->next;
				temp->next->previous=temp->previous;	
				return 1;			
			}
			temp= temp->next;
		}
	}
	return 0;
}

/*!
 this function bacislly modify node from double linked list of given roll number and return 1;
 user again write whole details of that student
 if roll number is not found return 0
 */

int modify(int rn){
	if (head->roll_no==rn)
	{
		long long int phoneno;
		char addr[100];
		char dob[20];
		char name[50];
		char tempc;
		printf("Enter Name, address ,dob, phoneno\n");
		scanf("%c",&tempc);
		scanf("%[^\n]",name);
		scanf("%c",&tempc);
		scanf("%[^\n] ",addr);
		scanf("%[^\n] ",dob);
		scanf("%lld",&phoneno);

		// printf("%s %s %s\n",name, addr,dob );

		strcpy(head->name, name);
		strcpy(head->dob, dob);
		strcpy(head->address, addr);
		head->phone_no = phoneno;


		return 1;
	}
	else{
		struct student *temp = head->next;
		while(temp!=head){
			if (temp->roll_no==rn)
			{
				long long int phoneno;
				char addr[100];
				char dob[20];
				char name[50];
				char tempc;

				printf("Enter Name, address ,dob, phoneno\n");
				scanf("%c",&tempc);
				scanf("%[^\n]",name);
				scanf("%c",&tempc);
				scanf("%[^\n] ",addr);
				scanf("%[^\n] ",dob);
				scanf("%lld",&phoneno);

				// printf("%s %s %s\n",name, addr,dob );

				strcpy(temp->name, name);
				strcpy(temp->dob, dob);
				strcpy(temp->address, addr);
				temp->phone_no = phoneno;

				return 1;			
			}
			temp= temp->next;
		}
	}
	return 0;
}

/*!
 these variables stores data from csv file 
 */

char addrs[13][100];
char names[13][50];
char dobs[13][20];
long long int phn[13];

/*!
 this function read csv file and store data into variables
 */

void scanCSV() {
	printf("Hello\n");
	FILE *f = fopen("./StudentData.csv","r");
	if(f != NULL) {
		fscanf(f ,"S.No.;Name;D.O.B.;Address;Phone No\n");
		for(int i = 0; i < 13; i++) {
			int x;
			fscanf(f, "%d;%[^;];%[^;];%[^;];%lld", &x, names[i],dobs[i],addrs[i],&phn[i]);
		}
		// for(int i = 0; i < 13; i++) {
		// 	int x;
		// 	printf("%s || %s || %s || %lld", names[i],dobs[i],addrs[i],phn[i]);
		// 	printf("\n");
		// }
	}
}

/*!
This function insert a new node in double linked list
there are 2 mode of insertion, first custom mode -> user have to write all details, second from csv mode -> user have to write only index from 0 to 12 only.
*/

void insert(){
	printf("Select Mode:\n");
	printf("1. Custom\n");
	printf("2. From CSV File\n");
	int mode;
	scanf("%d",&mode);
	int rollno;
	long long int phoneno;
	char addr[100];
	char dob[20];
	char name[50];
	char temp;

	struct student *ns;

	long long int newRoll = deQueue();

	if(newRoll==-1) {
		rollno = newAssignRoll;
		newAssignRoll++;
	}else {
		rollno = newRoll;
	}

	if (mode==1)
	{
		printf("Enter Name, address ,dob, phoneno\n");
		scanf("%c",&temp);
		scanf("%[^\n]",name);
		scanf("%c",&temp);
		scanf("%[^\n] ",addr);
		scanf("%[^\n] ",dob);
		scanf("%lld",&phoneno);
		ns = createnode(rollno,name,phoneno,addr,dob);
	}
	else{
		// by csv
		printf("Enter the index of student data in excel sheet.\n");
		
		int i;
		scanf("%d", &i);
		ns = createnode(rollno, names[i], phn[i], addrs[i], dobs[i]);
	}


	if (head == NULL)
	{
		head = ns;
		head -> previous =head;
		head -> next = head;
	}
	else{
		if (head->roll_no > ns->roll_no)
		{
			ns->next = head;
			ns->previous = head->previous;
			head->previous->next = ns;
			head->previous=ns;
			head=ns;

			return;
		}
		else
		{
			struct student *temp=head->next, *saveS=head;
			while(temp->roll_no < ns->roll_no && temp!=head){
				saveS = temp;
				temp=temp->next;
			}
			temp=saveS;

			ns->previous=temp;
			ns->next=temp->next;
			temp->next->previous=ns;
			temp->next = ns;
		}
	}
}

/*!
 this function bacislly search node from double linked list of given roll number , print that node and return 1;
 if roll number is not found return 0
 */

int search(int rn){
	if (head->roll_no==rn)
	{
		printnode(head);
		return 1;
	}
	else{
		struct student *temp = head->next;
		while(temp!=head){
			if (temp->roll_no==rn)
			{
				printnode(temp);
				return 1;			
			}
			temp= temp->next;
		}
	}
	return 0;
}

/*!
 this function print whole double linked list 
 */

void printList() {
	struct student *first = head;

	if (first==NULL)
	{
		printf("List is Empty\n");
		return;
	}

	struct student *rem = first;
	printnode(first);
	first = first->next;

	while(rem!=first){
		printnode(first);
		first = first->next;
	}
}

/*!
 this function return the length of double linked list
 */

int length() {
	if(head == NULL)
		return 0; 

	struct student *stu = head;
	int i = 1;
	stu = head->next;
	while(stu != head) {
		i++;
		stu = stu->next;
	}
	return i;
}

/*!
 this function swap the given two node of double inked list
 */

void swapNode(struct student *a, struct student *b)
{
	struct student *ns;
	ns = createnode(a->roll_no,a->name,a->phone_no,a->address,a->dob);

	strcpy(a->name, b->name);
	strcpy(a->address, b->address);
	strcpy(a->dob, b->dob);
	a->phone_no = b->phone_no;
	a->roll_no = b->roll_no;

	strcpy(b->name, ns->name);
	strcpy(b->address, ns->address);
	strcpy(b->dob, ns->dob);
	b->phone_no = ns->phone_no;
	b->roll_no = ns->roll_no;
}

/*!
 this function basiclly sort double linked list by its roll number
 */

void sort()
{
	if(head == NULL)
		printf("There is nothing to sort\n");
	else {
		int count;
		count = -1;
		do {
			count = 0;
			struct student* temp = head;
			while(temp->next != head) {
				if(temp->roll_no > temp->next->roll_no){
					swapNode(temp, temp->next);
					count++;
				}
				temp = temp->next;
			}
		}while(count != 0);

		puts("Sorted");
	}
}

/*!
 this function basiclly sort double linked list by its name
 */

void sortbyname() {
	if(head == NULL)
		printf("There is nothing to sort\n");
	else {
		int count;
		count = -1;
		do {
			count = 0;
			struct student* temp = head;
			while(temp->next != head){
				// printf("%d\n",temp->roll_no );
				if(strcmp(temp->name, temp->next->name) > 0) {
					swapNode(temp, temp->next);
					count++;
				}
				// else{
					temp = temp->next;
				// }
			}
		}while(count != 0);

		puts("Sorted");
		printList();
	}
	sort();
}


/*!
 this function call every time whenever any operatoin is finished.
 */

void menu(){

	printf("1. To insert.\n");
	printf("2. To display the List\n");
	printf("3. To delete a roll number.\n");
	printf("4. To search a roll number.\n");
	printf("5. to modify a student data at particular roll number\n");
	printf("6. to view list of sorted names of students.\n");
	int i;
	scanf("%d",&i);

	clk=clock();
	if (i==1)
	{
		insert();
	}
	else if (i==2)
	{
		printList();
	}
	else if(i==3)
	{
		if(head == NULL) {
			printf("List is empty\n");
			return ;
		}
		int rn;
		scanf("%d",&rn);
		int check= deletefromDL(rn);
		if (check==1){
			enQueue(rn);
		}
		else{
			printf("Not exist\n");
		}
	}
	else if(i==4){
		if(head == NULL) {
			printf("List is empty\n");
			return ;
		}
		int rn;
		scanf("%d",&rn);
		int check= search(rn);
		if(check==0){
			printf("Not exist\n");
		}
	}
	else if(i==5){
		if(head == NULL) {
		printf("List is empty\n");
		return ;
		}
		int rn;
		scanf("%d",&rn);
		int check= modify(rn);
		printf("Modified\n");
		if(check==0)
			printf("Not exist\n");
	}
	else if( i == 6) {
		sortbyname();
	}
	
}

/*!
 at starting first scan the csv file and then operations starts...
 */

int main(){
	frontRoll=0;
	rearRoll=0;
	scanCSV();
	while(1){
		menu();
		clk=clock()-clk;
		printf("Time: %f microsec\n", 1000000*((double)clk)/CLOCKS_PER_SEC );
	}
	
	return 0;
}