#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
int mobile_validation(char *mobile_num)
{
   int i,count=0;
   for(i=0;mobile_num[i]!='\0';i++)
   {
    if(mobile_num[i]>='0' && mobile_num[i]<='9')
    {
           count++;
    }
    else
    {
	printf("Entered invalid phone number!!\n");
    }
   }
   if(count!=10)
   return 0;
   else
   return 1;
}
int mail_validation(char *email)
{
    char *ret1 = strchr(email, '@');
    char *ret2 = strstr(email,  ".com");
    if (ret1 == NULL || ret2 == NULL)
        return 0;
    else
        return 1; // Valid email
}
void initialize(AddressBook *addressBook)
{
    addressBook->contactCount = 0;
    populateAddressBook(addressBook);

    // Load contacts from file during initialization (After files)
     loadContactsFromFile(addressBook);
}
void listContacts(AddressBook *addressBook)
{
    int i;
    for(i=0;i<addressBook->contactCount;i++)
    {
    printf("Name:%s",addressBook->contacts[i].name);
    printf("Phone:%s",addressBook->contacts[i].phone);
    printf("mail:%s",addressBook->contacts[i].email);
    printf("\n");
    }

}
void createContact(AddressBook *addressBook)
{
    char name[50];//temporarily creating variable for name
    printf("Enter the Name:\n");
    getchar();
    scanf("%[^\n]",name);
    getchar();
    char mobile[11];//temporarily creating variable for phone
    enter_again:
    printf("Enter mobile number:\n");
    scanf("%[^\n]",mobile);
    getchar();
    int valid_mobile=mobile_validation(mobile);
    if(valid_mobile!=0)
    {
    int k;
    for(k=0;k<=addressBook->contactCount;k++)
    {
    int ph=strcmp(addressBook->contacts[k].phone,mobile);
    if(ph==0)
    {
        printf("This Contact is Already saved,Please Enter 10 digit number (0-9):");
        goto enter_again;
    }
    }
    }
    else
    {
       // printf("Enter 10 digit '0'-'9' mobile number:");
        goto enter_again;
    }
    //creating temporory variable for g_mail
    char temp_gmail[100];
    printf("Enter the Email : ");
    retry_email:
    scanf("%[^\n]",temp_gmail);
    getchar();
    int valid_email=mail_validation(temp_gmail);
    if(valid_email==0)
    {
      printf("Enter a valid mail : ");
      goto retry_email;
    }

    //copying
    strcpy(addressBook->contacts[addressBook->contactCount].name,name);
    strcpy(addressBook->contacts[addressBook->contactCount].phone,mobile);
    strcpy(addressBook->contacts[addressBook->contactCount].email,temp_gmail);
    addressBook->contactCount++;
}
void searchContact(AddressBook *addressBook)
{
    int search;
    label:
    printf("1. Name\n");
    printf("2. Mobile number\n");
    printf("3. E-mail id\n");
    printf("What do you want to search:\n");
    scanf("%d",&search);
    getchar();
    if (search >= 1 && search <= 3)
    {
    if (search == 1)//name
    {
        char str2[20];
        printf("Enter the name to search for: ");
        scanf("%[^\n]", str2);
    getchar();
        int found = 0;
        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(addressBook->contacts[i].name, str2) == 0)
            {
                printf("Name: %s\n", addressBook->contacts[i].name);
                printf("Phone: %s\n", addressBook->contacts[i].phone);
                printf("E-mail: %s\n", addressBook->contacts[i].email);
                found = 1;
                break;
            }
        }
        if (found==0)
        {
            printf("No contact with the name exists in the address book.\n");
        }
    }
    else if (search == 2)//mobile_number
    {
        char str2[20];
        enter_again:
        printf("Enter the mobile number to search for: ");
        scanf("%[^\n]", str2);
    getchar();
        int validate_mobile=mobile_validation(str2);
        if(validate_mobile!=0)
        {
        int found = 0;
        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(addressBook->contacts[i].phone,str2)==0)
            {
                printf("Name: %s\n", addressBook->contacts[i].name);
                printf("Phone: %s\n", addressBook->contacts[i].phone);
                printf("E-mail: %s\n", addressBook->contacts[i].email);
                found = 1;
                break;
            }
        }
        if (found==0)
        {
            printf("No contact with the mobile number exists in the address book.\n");
        }
        }
        else
        {
            printf("Enter 10 digit number from 0-9:");
            goto enter_again;
        }
    }

    else if (search == 3)//mail
    {
        char str2[30];
        re_enter:
        printf("Enter the e-mail to search for: ");
        scanf("%[^\n]", str2);
    getchar();
        int mail_validate=mail_validation(str2);
        if(mail_validate!=0)
        {
        int found = 0;
        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(addressBook->contacts[i].email, str2) == 0)
            {
                printf("Name: %s\n", addressBook->contacts[i].name);
                printf("Phone: %s\n", addressBook->contacts[i].phone);
                printf("E-mail: %s\n", addressBook->contacts[i].email);
                found = 1;
                break;
            }
        }
        if (!found)
        {
            printf("No contact with the e-mail exists in the address book.\n");
        }
        }
        else
        {
            printf("Please Enter Valid email ");
            goto re_enter;
        }
    }
    }
    else
    {
        printf("Please Enter digits only betwnn 1 to 3:");
        goto label;
    }
}
void editContact(AddressBook *addressBook)
{
    int num;
    printf("1.Name:\n");
    printf("2.mail:\n");
    printf("3.phone:\n");
    printf("Enter which want you search:\n");
    scanf("%d",&num);
    getchar();
    if(num>=1&&num<=3)
    {
    if(num==1)
    {
        char str[20];
        printf("Enter the name what you want to replace:");
        scanf("%[^\n]",str);
        int i;
        int found=0;
        for(i=0;i<addressBook->contactCount;i++)
        {
           if(strcmp(addressBook->contacts[i].name,str)==0)
           {
               char edit_name[20];
               printf("Enter the name you want to edit:");
               scanf("%s",edit_name);
               strcpy(addressBook->contacts[i].name,edit_name);
               found=1;
               break;
           }
        }
        if(found==0)
        printf("User entered name is not found");
    }
    else if(num==2)
    {
        char str[20];
        again:
        printf("Enter the mail what you want to replace:");
        scanf("%[^\n]",str);
        int i;
        int ret=mail_validation(str);
        if(ret!=0)
        {
        int found=0;
        for(i=0;i<addressBook->contactCount;i++)
        {
           if(strcmp(addressBook->contacts[i].email,str)==0)
           {
              char mail[100];
               re_enter:
               printf("Enter the mail you want to edit:");
               scanf("%s",mail);
               int ret33=mail_validation(mail);
               if(ret33!=0)
               {
                strcpy(addressBook->contacts[i].email,mail);
               }
               found=1;
           }
        }
        if(found==0)
        printf("User entered mail is not found");
        }
        else
        {
            printf("Please Enter valid mail to search");
            goto again;
        }
    }
    else if(num==3)
    {
        char str[20];
        repeat:
        printf("Enter the mobile_number what you want to replace:");
        scanf("%[^\n]",str);
        int i;
        int ret=mobile_validation(str);
        if(ret!=0)
        {
        int found=0;
        for(i=0;i<addressBook->contactCount;i++)
        {
           if(strcmp(addressBook->contacts[i].phone,str)==0)
           {
              char mobile[20];
               re_enter1:
               printf("Enter the mail you want to edit:");
               scanf("%s",mobile);
               int res=mail_validation(mobile);
               if(res!=0)
               {
                strcpy(addressBook->contacts[i].phone,mobile);
                printf("Mobile Number updated Succesfully");
               }
               else
               {
                printf("Invalid mobile_number");
                   goto re_enter1;
               }
               found=1;
               break;
           }
        }
        if(found==0)
        printf("User entered mobile_number is not found");
        }
        else
        {
            printf("Please Enter valid mail to search");
            goto repeat;
        }

    }
    }
    else
    {
	printf("Enter number between 1 - 3 ");
    }
}
void deleteContact(AddressBook *addressBook)
{
    printf("1.Name:\n");
    printf("2.mobile:\n");
    printf("3.mail:\n");
    printf("Enter which want you delete:\n");
    int num;
    scanf("%d",&num);
    getchar();
    int i,j;
    int found=0;
    if(num>=1&&num<=3)
    {
    if(num==1)
    {
        char str4[15];
        printf("Enter the name:\n");
        scanf("%[^\n]",str4);
    for(i=0;i<addressBook->contactCount;i++)
    {
        if(strcmp(addressBook->contacts[i].name,str4)==0)
        {
            for(j=i;j<addressBook->contactCount-1;j++)
            {
                addressBook->contacts[j]=addressBook->contacts[j+1];
            }
            addressBook->contactCount--;
            found=1;
            break;
        }
    }
    if(found==0)
    printf("Contact not found");
    }
    if(num==2)
    {
        char mobile[20];
        printf("Enter the number:");
        scanf("%[^\n]",mobile);
        int ret=mobile_validation(str4);
        if(ret!=0)
        {
        for(i=0;i<addressBook->contactCount;i++)
        {
          if(strcmp(addressBook->contacts[i].phone,mobile)==0)
          {
          for(j=i;j<addressBook->contactCount-1;j++)
          {
            addressBook->contacts[j]=addressBook->contacts[j+1];
          }
          addressBook->contactCount--;
            found=1;
            break;
           }
        }
         if(found==0)
          printf("Contact not found");
      }
    else
    printf("Enter a 10 digit mobile number from 0-9");
    }
    if(num==3)
    {
        char gm[50];
        printf("Enter the mail:");
        scanf("%[^\n]",gm);
        int ret=mail_validation(gm);
        if(ret!=0)
        {
        for(i=0;i<addressBook->contactCount;i++)
        {
          if(strcmp(addressBook->contacts[i].email,gm)==0)
          {
          for(j=i;j<addressBook->contactCount-1;j++)
          {
            addressBook->contacts[j]=addressBook->contacts[j+1];
          }
          addressBook->contactCount--;
            found=1;
            break;
           }
        }
         if(found==0)
          printf("email not found");
        }
        else
        printf("Enter valid mail ");
    }
    }
    else
    {
    printf("Enter the number from 1 to upto 3");
    }
}
void saveAndExit(AddressBook *addressBook)
{
    exit(EXIT_SUCCESS);
}
