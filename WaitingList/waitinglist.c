// Christian Quintero
// COEN11L 
// FILE: waitlist.c
//
// This program simulates a waiting list management system, utilizing a linked list, threads,
// recursion, and opening/reading data from a file, as well as writing to the file.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <pthread.h>
#define Node   struct node

struct node//creates struct node which contains char array, int and node pointer
{
	char partyname[20];
	int partysize;
	Node *next;	
};

struct ptr
{
	Node *head;
	Node *tail;
};

struct ptr arrayofptr[4];

void *loopThread(void *arg);
pthread_mutex_t mutex;

void reverse (char *);
void freenodes(Node * , FILE * );

/*
 * Function:  add
 *
 * --------------------
 * Precondition:  sizeofparty > 0
 *
 * --------------------
 * Postcondition:  allocates memory for a new node to be added to the appropriate
 *                 linked list according to the party size, or does nothing if there 
 *                 is no available memory to be allocated
 *
 * --------------------
 * returns:  nothing
 */
void add(char *nameofparty, int sizeofparty)
{
	int t;
	Node *temp, *p;
	temp=(Node *)malloc(sizeof(Node));//create new node
	if (temp==NULL)//no memory was able to be allocated
	{
		return;
	}
	switch (sizeofparty)
	{
		case 1:
		case 2:
			t=0;
			strcpy(temp->partyname,nameofparty);
			temp->partysize=sizeofparty;
			break;
		case 3:
		case 4:
			t=1;
			strcpy(temp->partyname,nameofparty);
			temp->partysize=sizeofparty;
			break;
		case 5:
		case 6:
			t=2;
			strcpy(temp->partyname,nameofparty);
			temp->partysize=sizeofparty;
			break;
		default:
			t=3;
			strcpy(temp->partyname,nameofparty);
			temp->partysize=sizeofparty;
			break;
	}
	if (arrayofptr[t].head==NULL)//first node in list
	{	
		pthread_mutex_lock (&mutex);
		arrayofptr[t].head=temp;//this will make head the first node
		arrayofptr[t].tail=temp;
		arrayofptr[t].head->next=NULL;
		pthread_mutex_unlock (&mutex);
	}	
	else//any node after
	{
		pthread_mutex_lock (&mutex);
		arrayofptr[t].tail->next=temp;//link previous tail to new tail
		arrayofptr[t].tail=temp;//make tail last
		arrayofptr[t].tail->next=NULL;
		pthread_mutex_unlock (&mutex);
	}
	return;
}

/*
 * Function:  seat_available
 *
 * --------------------
 * Precondition:  none
 *
 * --------------------
 * Postcondition:  removes a node from linked list if a party size fits the
 *                 available table, otherwise prints out message to stdout
 *
 * --------------------
 * returns:  nothing
 */
void seat_available()
{
	int f=0;
	int i;
	Node *p, *q;
	int table;
	printf("How big is the available table?\n");
	scanf("%d",&table);
	switch (table)
	{
		case 1:
		case 2: 
			i=0;
		case 3:
		case 4:
			i=1;
		case 5:
		case 6:
			i=2;
		default:
			i=3;
	}
	for ( ;i>=0;i--)
	{
		if (arrayofptr[i].head!=NULL)
		{
			p=arrayofptr[i].head;
			while (p!=NULL)
			{
				if (p->partysize<=table)
				{
					f=1;
					break;
				}
				p=p->next;
			}
			if (f==1)
			{
				break;
			}
		}
	}
	if (i==-1)
	{
		printf("No party fits table\n");
		return;
	}
	p=q=arrayofptr[i].head;//set pointers to beginning of linked list
	while (p!=NULL)//traverse through list
	{
		if (p->partysize<=table)//fits table
		{
			break;
		}
		q=p;//sets a pointer for the current position
		p=p->next;//sets pointer to next position
	}
	if (p==NULL)//did not find table that fits
	{
		printf("No party fits\n");
		return;
	}
	else if (p==arrayofptr[i].head && p->next!=NULL)//first table fits
	{
		pthread_mutex_lock (&mutex);
		arrayofptr[i].head=p->next;//moves head to next node
		p->next=NULL;//
		pthread_mutex_unlock (&mutex);
	}
	else if (p==arrayofptr[i].head && p==arrayofptr[i].tail)//if only one node is here
	{
		pthread_mutex_lock (&mutex);
		arrayofptr[i].head=NULL;
		arrayofptr[i].tail=NULL;
		p->next=NULL;
		pthread_mutex_unlock (&mutex);
	}
	else if (p==arrayofptr[i].tail)//last node fits
	{
		pthread_mutex_lock (&mutex);
		arrayofptr[i].tail=q;//makes tail previous node
		q->next=NULL;	
		pthread_mutex_unlock (&mutex);
	}
	else//node in middle 
	{
		pthread_mutex_lock (&mutex);
		q->next=p->next;
		p->next=NULL;
		pthread_mutex_unlock (&mutex);
	}
	free(p);//deletes unlinked nodes and frees space
	return;
}

/*
 * Function:  show_list
 *
 * --------------------
 * Precondition:  none
 *
 * --------------------
 * Postcondition:  traverses through linked lists and prints out partyname
 *                 and partysize for each node in list.
 *
 * --------------------
 * returns:  nothing
 */
void show_list()//show waitlist
{
	int i;
	Node *p;
	for (i=0;i<4;i++)
	{
		p=arrayofptr[i].head;
		while(p!=NULL)//traverse list
		{
			printf("%s , %d \n",p->partyname, p->partysize);
			p=p->next;
		}	
	}
	return;
}

/*
 * Function:  occurence
 *
 * --------------------
 * Precondition:  none
 *
 * --------------------
 * Postcondition:  traverses through linked lists and prints out the number of times
 *                 a character, which the user enters, occurs within each node's partyname   
 *
 * --------------------
 * returns:  nothing
 */
void occurence()
{
	int counter=0;
	char letter;
	char *l;
	Node *p;
	int i;
	printf("Enter the letter you want to check the occurence of\n");
	__fpurge(stdin);
	scanf("%c",&letter);
	for (i=0;i<4;i++)//loop to check names in lists
	{
		p=arrayofptr[i].head;
		while (p!=NULL)
		{	
			l=p->partyname;
			while (*l!='\0')
			{
				if (*l==letter)//letter is same
				{
					counter++;
				}
				l++;
			}
			p=p->next;
		}
	}
	printf("%d\n",counter);
	return;
}

/*
 * Function:  recur
 *
 * --------------------
 * Precondition:  none
 *
 * --------------------
 * Postcondition:  traverses through linked lists and calls reverse function 
 *                 to print partyname of nodes backwards
 *
 * --------------------
 * returns:  nothing
 */
void recur()
{
	Node *p=NULL;
	int i;
	for (i=0;i<4;i++)
	{
		p=arrayofptr[i].head;
		while (p!=NULL)
		{
			reverse(p->partyname);//call recursion
			printf("\n");
			p=p->next;
		}
	}	
}

/*
 * Function:  reverse
 *
 * --------------------
 * Precondition:  *p points to partyname
 *
 * --------------------
 * Postcondition:  uses recursion to reach end of string and prints
 *                 string backwards
 *
 * --------------------
 * returns:  nothing
 */
void reverse(char *p)
{
	if (*p=='\0')
	{
		return;
	}
	reverse(p+1);//traverse list
	printf("%c",*p);//print backwards after end is reached
	return;
}

/*
 * Function:  save_data
 *
 * --------------------
 * Precondition:  *data points to data file
 *
 * --------------------
 * Postcondition:  writes linked list data into file pointed by parameter
 *
 * --------------------
 * returns:  nothing
 */
void save_data(char *data)
{
	int i;
	FILE *fp;
	Node *p;
	pthread_mutex_lock (&mutex);//lock since function is going to save data
	fp=fopen(data,"w");//open file for writing
	if (fp==NULL)//no data
	{
		printf("fp was NULL\n");
		return;

	}
	fprintf(fp,"Name\tGroup Size\n\n");//print header into file
	for (i=0;i<4;i++)
	{
		p=arrayofptr[i].head;
		{
			freenodes(p, fp);
		}
	}
	fclose(fp);
	pthread_mutex_unlock (&mutex);//unlock after saving
	return;
}

/*
 * Function:  freenodes
 *
 * --------------------
 * Precondition:  *p points to list head and *fp points to file
 *
 * --------------------
 * Postcondition:  writes data from received Node into FILE pointed by parameter, 
 *                 then frees up the memory used by Node.
 *
 * --------------------
 * returns:  nothing
 */
void freenodes(Node *p, FILE *fp)
{
	if (p==NULL)
	{
		return;
	}
	fprintf(fp,"%s\t%d\n",p->partyname, p->partysize);//print info into text
	freenodes(p=p->next, fp);//recursive function to keep printing info into text file until end is reached
	free(p);//will go back through recursive function to free all nodes
	return;
}

/*
 * Function:  read_data
 *
 * --------------------
 * Precondition:  *data points to data file
 *
 * --------------------
 * Postcondition:  opens file pointed by parameter for reading and calls the
 *                 add function if file is not empty, otherwise it sets head
 *                 and tail pointers of linked lists to NULL
 *
 * --------------------
 * returns:  nothing
 */
void read_data(char *data)
{
	int i;
	int number;
	char name[20];
	FILE *fp;
	fp=fopen(data,"r");//open file for reading
	if (fp==NULL)//no file
	{
		printf("file empty\n");
		for (i=0;i<4;i++)
		{
			arrayofptr[i].head=NULL;
			arrayofptr[i].tail=NULL;
		}
		return;
	}
	else
	{
		printf("open successfully\n");
	}
	fseek(fp,17,SEEK_SET);//start scanning data after header
	while (fscanf(fp,"%s %d",name, &number)==2)
	{
		add(name,number);
	}
	fclose(fp);
	return;
}

/*
 * Function:  loopThread
 *
 * --------------------
 * Precondition: 
 *
 * --------------------
 * Postcondition:  creates infinite thread loop to autosave data from linked lists into
 *                 binary file every 5 seconds
 *
 * --------------------
 * returns:  nothing
 */
void *loopThread (void *arg)
{
	char *binfile = (char*) arg;//set pointer to file
	while(1)//infinite loop to contine to autosave
	{	
		int i;
		Node *p;
		FILE *fp;
		pthread_mutex_lock (&mutex);//lock before opening file
		fp=fopen(binfile, "wb");//open file for writing
		if (fp==NULL)
		{
			printf("fp was NULL\n");		
			return;
		}
		for (i=0;i<4;i++)
		{
			p=arrayofptr[i].head;
			while(p!=NULL)
			{
				fwrite(p,sizeof(Node),1,fp);//write into binary file
				p=p->next;
			}
		}
		fclose(fp);
		pthread_mutex_unlock (&mutex);
		sleep(5);//sleep for 5 seconds before autosaving again
	}
}

/*
 * Function:  see_bin
 *
 * --------------------
 * Precondition:  *arg points to binary file
 *
 * --------------------
 * Postcondition:  Prints out partyname and partysize data from nodes saved
 *                 in binary file, unless empty.
 *
 * --------------------
 * returns:  nothing
 */
void see_bin(char *arg)
{
	char *binfile = (char*) arg;
	int i;
	FILE *fp;
	Node *temp;
	pthread_mutex_lock (&mutex);
	fp=fopen(binfile, "rb");//open bin file for reading
	if (fp==NULL)
	{
		printf("file empty\n");
		return;
	}
	for (i=0;i<40;i++)//loop to create temp nodes for bin file being read
	{
		temp=(Node *)malloc(sizeof(Node));
		if(fread(temp,sizeof(Node),1,fp))//if node is found
		{
			printf("%s   %d\n",temp->partyname,temp->partysize);
		}
			else//no more nodes
		{
			break;
		}
	}
	fclose(fp);
	pthread_mutex_unlock (&mutex);
	return;
}

int main(int argc, char *argv[ ])
{
	int sizeofparty;
	int i;
	int f=0;
	int action;
	Node *p;
	char nameofparty[20];
	pthread_t thr;
	if (argc==1)//file is missing
	{
		printf("The name of the file is missing!\n");
		return 1;
	}
	else
	{
		read_data(argv[1]);//open data file for reading
	}
	pthread_create(&thr,NULL,loopThread,(void *) argv[2]);//create thread
        while(1)//infinite loop to carry out switch functions
        {
                printf(" To add name to the waiting list please enter 1\n To assign table please enter 2\n If you would like to see the waitinglist please enter 3\n To count occurence of a letter enter 4\n To show all names backwards enter 5\n To see autosave bin file enter 6\n To save data and exit  enter 7\n");
                scanf("%d",&action);
                switch (action)
                {
					case 1:
						f=0;
						printf("What is the party name?\n");
						{
							scanf("%s", nameofparty);
						}
						for (i=0;i<4;i++)
						{
							p=arrayofptr[i].head;
							while (p!=NULL)
							{
								if (strcmp(nameofparty,p->partyname)==0)//check for repeating names
								{
									printf("Sorry the name is taken.\n");
									f=1;
									break;
								}
								p=p->next;
							}
							if (f==1)//break out of for loop
							{
								break;
							}
	                    }
						if (f==1)
						{
							break;
						}
						printf("What is the size of the party?\n");
	        			scanf("%d",&sizeofparty);
						add(nameofparty, sizeofparty);
	                    break;
                    case 2:
                            seat_available();
                            break;
                    case 3:
                            show_list();
                            break;
					case 4:
						occurence();
						break;
					case 5:
						recur();
						break;
					case 6:
						see_bin(argv[2]);
						break;
					case 7:
						save_data(argv[1]);
                        return 0;
                }
        }
}
         
