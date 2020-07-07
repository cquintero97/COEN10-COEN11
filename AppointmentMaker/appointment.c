// Christian Quintero
// COEN 10L 
// FILE: appointment.c
//
// This program simulates an appointment scheduling system, giving the user the option
// to manually schedule, cancel, and list appointments using the console input.

#include <stdio.h>
#include <stdlib.h>

int appointment[6];//Array that will contain 6 integers.

int main()
{
	int i;
	int counter=0;
	int action;
	int appnum;
	int ID;
	for (i=0; i<6; i++)//This will set every variable in the array to equal 0
	{
		appointment[i]=0;
	}
	while(1)//Never-ending loop until exiting manually
	{
		printf("To schedule an appointment enter(1); To cancel an appointment enter(2); To list all appointment hours enter (3); To exit enter any other number\n");
		scanf("%d",&action);
		if (action==1)//Confirming user enters option to make an appointment.
		{
			for (i=0;i<6;i++)//Sets the loop for assigning an appointment
			{
				if (counter==6)//outputs that all appointments are full since there are 6 appointments scheduled
				{
					printf("There are currently no available appointments\n");
					break;
				}
				if (appointment[i]==0)//searches for available position in array where appointment can be set and adds appointment to size of counter
				{
					appointment[i]=1;
					counter++;
					printf("You will be appointment number:%d at %d p.m.\n",i+1,i+1);
					break;
				}
			}
		}
		else if (action==2)//sets condition for when 2 is entered in order to cancel an appointment
		{
			printf("please enter the appointment number that you want to cancel.\n");
			scanf("%d",&appnum);
			if (appointment[appnum-1]==1)//check to see if appointment number is valid and will cancel the appointment and set the element in that position back to 0	
			{
				appointment[appnum-1]=0;
				printf("Your appointment has been cancelled.\n");
				counter--;
			}
			else if (appointment[appnum-1]==0)//checks condition of appointment number and if there is no appointment scheduled it will read back no appointment
			{
				printf("There is no scheduled appointment for this number.\n");
			}
		}
		else if (action==3)//sets condition for when 3 is entered in order to see all scheduled appointments
		{
			for (i=0;i<6;i++)//loop to output all elements in array and see which appointments are taken and open
			{
				printf("scheduled appointments at %d p.m. :%d \n",i+1,appointment[i]);
			}
		}
		else//condition for when any other number is entered in order to exit never-ending loop
		{
			return 0;
		}
	}
}
