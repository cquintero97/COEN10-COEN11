// Christian Quintero
// COEN10L 
// FILE: appointment.c
//
// This program simulates an appointment scheduling system, giving the user the option
// to manually schedule, cancel, and list appointments using the console input.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int i;
int counter=0;
char names[6][20];

/*
 * Function:  check
 *
 * --------------------
 * Precondition:  none
 *
 * --------------------
 * Postcondition:  Prints out the occurence of a letter, that the user enters, throughout
 *                 the entire names array.
 *
 * --------------------
 * returns:  nothing
 */
void check()
{
	int lcounter=0;
	char *l;
	char letter;
	printf("please enter the letter that you want to count.\n");
	scanf (" %c", &letter);//letter that will be checked
	for(i=0;i<6;i++)//go through entire array
	{
		l=names[i];//set the pointer
		while(*l!='\0')
		{
			if(*l==letter)
			{
				lcounter++;
			}
			l++;
		}
	}
	printf("The letter %c appeared %d times\n", letter, lcounter++);//prints number of occurrences
	return;	
}

/*
 * Function:  emergency
 *
 * --------------------
 * Precondition:  none
 *
 * --------------------
 * Postcondition:  Adds new appointment to beginning of array and shifts other appointments down.
 *                 If array is full, removes last appointment in array and shifts the rest over.
 *
 * --------------------
 * returns:  nothing
 */
void emergency()
{
	int k;
	char emerg[20];
	printf("Please enter the name of the individual that has an emergency.\n");
	scanf("%s",emerg);//name for emergency
	for (i=0;i<6;i++)//to check the array
	{
		if (strcmp(names[i],emerg)==0)//check for repeating names
		{
			printf("This name is already taken. Please use another name next time.\n");
			return;
		}
	}
	if (counter==6)//If all slots are taken up
	{
		printf("To make this appointment we will have to cancel someone else's appointment.\n");
		names[6][0]='\0';//last string in array gets erased to make room for emergency	
	}
	for (k=5;k>0;k--)//move strings down in array
	{
		strcpy(names[k],names[k-1]);
	}
	printf("Your emergency appointment has been scheduled for 1p.m.\n");
	strcpy(names[0],emerg);//set emergency as first appointment
	if (counter!=6)
	{
		counter++;
	}
	return;
}

/*
 * Function:  make
 *
 * --------------------
 * Precondition:  none
 *
 * --------------------
 * Postcondition:  Adds new appointment to names array and increments counter.
 *                 If array is full, does not create new appointment.
 *
 * --------------------
 * returns:  nothing
 */
void make ()
{
        char enter[20];
        if (counter==6)//This checks to see if slots are full
        {
                printf("there are currently no available appointments.\n");
        }
        else//Will enter name into appointment
        {
                printf("Please enter your name to schedule an appointment.\n");
                scanf("%s",enter);
                for (i=0;i<6;i++)//To check for repeating names
                {
                        if (strcmp(names[i],enter)==0)//If name entered already exists
                        {
                                printf("Sorry that name is already taken. Please use another name next time.\n");
                                break;
                        }
                }
                if (i==6)//If there are no repeating names
                {
                        printf("Your appointment will be at %d pm\n", counter+1);
                        strcpy(names[counter],enter);
                        counter++;
                }
        }
        return;
}

/*
 * Function:  delete
 *
 * --------------------
 * Precondition:  none
 *
 * --------------------
 * Postcondition:  Removes appointment in names array with matching name that user
 *                 enters and decrements counter, unless no match is found.
 *
 * --------------------
 * returns:  nothing
 */
void delete()
{
        char cancel[20];
        int j;
        if (counter==0)//No appointments 
        {
                printf("There are no scheduled appointments.\n");
        }
        else//Cancel appointment
        {
                printf("To cancel your appointment please enter your name\n");
                scanf("%s",cancel);
                for (i=0;i<6;i++)//To go through array looking for name
                {

                        if (strcmp(names[i],cancel)==0)//if name matches
                        {
                                if (i==5)//To empty last name in array
                                {
                                        names[i][0]='\0';
                                }
                                printf("Your appointment has been cancelled.\n");
                                for (j=i+1;j<6;j++)//To move all other appointments down
                                {
                                        strcpy(names[j-1],names[j]);
                                        names[j][0]='\0';
                                }
                                counter--;
                                break;
                        }
                }
                if (i==6)//did not find name
                {
                        printf("There is no appointment scheduled under that name.\n");
                }
        }
        return;
}

/*
 * Function:  view
 *
 * --------------------
 * Precondition:  none
 *
 * --------------------
 * Postcondition:  prints out names of appointments in array with corresponding 
 *                 appointment times.
 * --------------------
 * returns:  nothing
 */
void view()
{
        if (counter==0)//no appointments scheduled
        {
                printf("There are no appointments scheduled\n");
        }
        else
        {
                for (i=0;i<6;i++)//To show all scheduled appointments in array
                {
                        printf("Scheduled appointments at %d p.m.   :%s \n",i+1,names[i]);
                }
        }
        return;
}

int main()
{
        int action;
        for (i=0;i<6;i++)//Empty out each string in array
        {
                names[i][0]='\0';
        }
        while(1)
        {
                printf("To schedule an appointment enter (1), To cancel an appointment enter (2), To list all appointments enter (3), If you have an emergency and need to schedule an appointment right away enter (4), To check how many times a letter reoccurs in an appointment's name enter (5), To exit enter (6)\n");

                scanf("%d",&action);
                switch (action)
                {
                        case 1:
                                make();
                                break;
                        case 2:
                                delete();
                                break;
                        case 3:
                                view();
                                break;
			case 4:
				emergency();
				break;
			case 5:
				check();
				break;
                        default:
                                return 0;//To exit              
                }
        }
}


