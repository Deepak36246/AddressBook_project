/*
Name:Deepak
Date:23/09/2024
Description:AddressBook
*/
#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) 
{
    int num;
    printf("Enter what you want to do\n");
    printf("Enter 1 YES or 2 for NO\n");
    scanf("%d",&num);//asking user to save the contact or not..
    printf("\n");
    if(num==1)//if user entered 1 then contact will be saved
    {
	FILE *fptr=fopen("file.csv","w+");//using w+ mode to read and write from the file...
	if(fptr==NULL)//validating the file//
	{
	    printf("FILE NOT EXIST");
	    return;
	}
	fprintf(fptr,"%d\n",addressBook->contactCount);
	for(int i=0;i<addressBook->contactCount;i++)
	{
	    //using fprintf print the data from fptr file pointer//
	    fprintf(fptr,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
	}
	fclose(fptr);//close the file // 
	printf("Contact successfully saved\n");
    }
    else
    {
         exit(EXIT_SUCCESS);//if user dont want to save..then exit to addressBook menu ...//
    }


}
void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *fptr=fopen("file.csv","r");//we are opening the file in read mode 
    if(fptr==NULL)//doing validation here 
    {
	printf("FILE NOT EXIST");//if file not exist it will give this prompt
	return;
    }
    fscanf(fptr,"%d\n",&addressBook->contactCount);//we are reading from the file upto contact count times 
    for(int i=0;i<addressBook->contactCount;i++)//now store into the contact count addressBook.
    {
	char str[300]; 
	fgets(str,300,fptr);//using fgets we are reading data from file to the string//
	char *token=strtok(str,",");//using strtok we are separating string upto delimetry..//
	if(token!=NULL)
	strcpy(addressBook->contacts[i].name,token);

	token=strtok(NULL,",");
	if(token!=NULL)
	strcpy(addressBook->contacts[i].phone,token);

	token=strtok(NULL,"\n");
	if(token!=NULL)
	strcpy(addressBook->contacts[i].email,token);
    }
    fclose(fptr); //closing the file//
}
