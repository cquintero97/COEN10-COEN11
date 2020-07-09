// Christian Quintero
// COEN10L 
// FILE: lab10.c
//
// This program allows a user to enter up to 10 strings into a two-dimensional array and manipulate
// the array in various ways, such as reversing the array, converting all lower case characters to 
// upper case, and also output information about the array. 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
int i=0;
int counter=0; //keeps track of array size
char words[10][20]; //no more than 10 strings with max length of 20 characters each string

/*
 * Function:  input
 *
 * --------------------
 * Precondition:  none
 *
 * --------------------
 * Postcondition:  Adds string entered by user into array and prints out current array.
 *                 If array is full, does nothing.
 *
 * --------------------
 * returns:  nothing
 */
void input()
{
        int j;
        char temp[20];
        char enter[20];
        if (counter==10)//array is full
        {
                printf("Sorry, the array is already filled.\n");
        }
        else//array has space for string
        {
                printf("Please enter in a word.\n");
                scanf("%s",enter);
                if (counter==0)//empty array so no need to alphabetize
                {
                        strcpy(words[0],enter);//string becomes first in array
                        counter++;
                }
                else//if there is already an existing string(s) in the array
                {       strcpy(words[counter],enter);//add entered word after last string
                        counter++;
                        for (i=0;i<counter;i++)//To help swap strings in array
                        {
                                for (j=i+1;j<counter;j++)//nested to help with swapping
                                {
                                        if (strcmp(words[i],words[j])> 0)//Check where string belongs and move it to correct location
                                        {
                                                strcpy(temp,words[i]);
                                                strcpy(words[i],words[j]);
                                                strcpy(words[j],temp);
                                        }
                                }
                        }
                }
                printf("Thank you. The array now reads: \n");
                for (i=0;i<10;i++)//print out array
                {
                        printf("%s ",words[i]);
                }
                printf(" \n");
        }
        return;
}

/*
 * Function:  reverse
 *
 * --------------------
 * Precondition:  none
 *
 * --------------------
 * Postcondition:  Reverses order of strings in array and prints out reversed array.
 *
 * --------------------
 * returns:  nothing
 */
void reverse()
{
		int k=counter-1;
        char t[10][20];
        for (i=0;i<10;i++)// empty temp array
        {
                t[i][0]='\0';
        }
        for (i=0;i<counter;i++)//copy array to temp array reversed
        {
                strcpy(t[i],words[k]);
                k--;
        }
        for (i=0;i<counter;i++)//to set original array as new reversed array
        {
                strcpy(words[i],t[i]);
        }
        printf("the array now reads: \n");
        for (i=0;i<10;i++)//print reversed array
        {
                printf("%s ",words[i]);
        }
        return;
}

/*
 * Function:  convert
 *
 * --------------------
 * Precondition:  none
 *
 * --------------------
 * Postcondition:  Traverses through array and converts all lower case chars to upper case,
 *                 then prints out array.
 *
 * --------------------
 * returns:  nothing
 */
void convert()
{
        for (i=0;i<10;i++)//transverse through strings in array looking for lowercase letters
        {
                char *p=words[i];//sets pointer to beginning of string
                while (*p!='\0')//pointer continues through string until it reaches '\0'
                {
                        if (*p>='a' && *p<='z')//if the pointer reads a lower case value
                        {
                                *p=('A' + *p - 'a');//converts lowercase to uppercase
                        }
                        p++;
                }
                printf("%s  \n", words[i]);
        }
        return;
}

/*
 * Function:  show
 *
 * --------------------
 * Precondition:  none
 *
 * --------------------
 * Postcondition:  Prints out fun facts about the array such as avg len, shortest string, etc.
 *
 * --------------------
 * returns:  nothing
 */
void show()
{
        int counter2=0;
        float average;
        int longest=0;
        int l=0;
        int shortest=20;
		int s=0;
        if (counter==0)//empty array
        {
                printf("There are no words in the array\n");
        }
        if (counter==1)//only one string in array so no need to show other information
        {
                printf("The shortest and longest string is %s since it is the only word in the array \n", words[0]);
        }
        if (counter>1)//more than one string in array
        {
                for (i=0;i<counter;i++)//transverse through array looking for longest string
                {
                        if(strlen(words[i])>longest)
                        {
                                longest=strlen(words[i]);//longest string becomes the new longest
                                l=i;//holds the position of the string
                        }
                }
                printf("The longest string was %s \n", words[l]);
                for (i=0;i<counter;i++)//transverse through array looking for shortest string
                {
                        if(strlen(words[i])<shortest)
                        {
                                shortest=strlen(words[i]);//string becomes the new shortest
                                s=i;//holds position of shortest string
                        }
                }
                printf("The shortest string was %s \n", words[s]);
        }
        for (i=0;i<counter;i++)
        {
                counter2=counter2+strlen(words[i]);//sum up the total lenghts of all the words in the array
        }
        if(counter>0)//ensure that this information only displays when counter is greater than 0
        {
                printf("the average length of the words in the array is %f \n",average = (float)counter2/counter);//calculates and prints out average
                printf("The following are words that do not begin with a letter:  \n");
                for (i=0;i<counter;i++)// go through array looking for strings that do not begin with a letter
                {
                        if ((words[i][0]>='a' && words[i][0]<='z') || (words[i][0]>='A' && words[i][0]<='Z'))
                        {
                        }
                        else//prints out the strings
                        {
                                printf("%s  \n",words[i]);
                        }
                }
        }
      return;
}

int main()
{
        int action;
        for (i=0;i<10;i++)//emptys out the array
        {
                words[i][0]='\0';
        }
        while(1)//forever loop
        {
                printf("To enter words into array enter(1), To reverse the array enter(2), Toconvert all lowercase letters to uppercase letters enter(3), To show more info on words enter(4)\n");

                scanf("%d",&action);
                switch (action)
                {
                        case 1:
                                input();
                                break;
                        case 2:
                                reverse();
                                break;
                        case 3:
                                convert();
                                break;
                        case 4:
                                show();
                                break;
                        default:
                                return 0;//To exit
                }
        }
}       