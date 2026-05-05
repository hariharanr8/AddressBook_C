#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<stdbool.h>
#include<ctype.h>
#include "contact.h"
#include "file.h"
int arr[100];
void listContacts(AddressBook *addressBook) 
{
    // Sort contacts based on the chosen criteria
    printf("\n%-6s %-20s %-15s %-30s\n","S.no","Name","Phone","Email");
    for(int i=0;i<(addressBook->contactCount);i++){
        printf("%-6d %-20s %-15s %-30s\n",i+1,addressBook->contacts[i].name,
            addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}

bool name_verify(char *name,int attempt){  //Name validation
    int i=0;
    while(name[i]){
        if(!(isalpha(name[i]) || name[i]==' ')){  
            if(attempt<=3){
                printf("invalid name!\n");
                printf("name only contains alphabet and space...\n");
                printf("%d outof three attempts\n",attempt);
                printf("Re-enter name: ");
                scanf(" %49[^\n]",name);
                attempt++;
                i=-1;
            }
            else{
                return false;
            }
        }
        i++;
    }
    return true;
}

bool phonelen_verify(char *phone){
    int len = strlen(phone);
    if(len == 10){
        return true;
    }
    else{
        printf("Enter 10 numbers only!\n");
        return false;
    }
}

bool phonedigit_verify(char *phone){
    int i=0;
    while(phone[i]){
        if(!isdigit(phone[i])){
            printf("only digits will allowed!\n");
            return false;
        }
        i++;
    }
    return true;
}

bool phonestartas_verify(char *phone){
    if(phone[0]<='9' && phone[0]>='6'){
        return true;
    }
    else{
        printf("first digit is 6-9.\n");
        return false;
    }
}

bool phoneunique_verify(char *phone,AddressBook *addressbook){
    for(int i=0;i<(addressbook->contactCount);i++){
        if(!strcmp(phone,addressbook->contacts[i].phone)){
            printf("number already exists\n");
            return false;
        }
    }
    return true;
}

bool phone_verify(char *phone,int attempt,AddressBook *addressbook,int unique){  
    //phone validation
    if(phonelen_verify(phone) && phonedigit_verify(phone) 
    && phonestartas_verify(phone) && (unique ? phoneunique_verify(phone,addressbook):1)){
        return true;
    }
    else{
        if(attempt<=3){
            printf("%d outof three attempts\n",attempt);
            printf("Re-enter phone: ");
            scanf("%19s",phone);
            attempt++;
            return phone_verify(phone,attempt,addressbook,unique);
        }
        else{
            return false;
        }
    }
}

bool emaillower_verify(char *email){
    int i=0;
    while(email[i]){
        if(isupper(email[i])){
            printf("Uppercase not allowed!\n");
            return false;
        }
        i++;
    }
    return true;
}

bool emailat_verify(char *email){
    int i=0,count=0;
    while(email[i]){
        if(email[i]=='@'){
            count++;
        }
        if(count==2){
            printf("multiple '@' not allowed!\n");
            return false;
        }
        i++;   
    }
    if(count==0){
        printf("mail must contain '@'\n");
        return false;
    }
    return true;
}

bool emailstart_verify(char *email){
    if(isdigit(email[0])){
        printf("Don't start with digit!\n");
        return false;
    }
    return true;
}

bool emailunique_verify(char *email,AddressBook *addressbook){
    for(int i=0;i<(addressbook->contactCount);i++){
        if(!strcmp(email,addressbook->contacts[i].email)){
            printf("email already exists!\n");
            return false;
        }
    }
    return true;
}

bool emailcom_verify(char *email){
    int i=0,count=0;
    char present[3] = "com";
    while(email[i]){
        if(email[i]=='.'){
            i++;
            int j=i,k=0;
            while(present[k]){
                if(email[j]=='\0' || email[j]!=present[k]){
                    break;
                }
                k++;
                j++;
            }
            if(k==3){
                count++;
                i=j;      
            } 
        }
        else{
            i++;
        }
    }
    if(count>1 || count<1){
        printf("Email must contain exactly one '.com'!\n");
        return false; 
    }
    else{
        int len = strlen(email);
        if(len < 4){
            printf("Invalid email format!\n");
            return false;
        }
        if(strcmp(&email[len-4], ".com") != 0){
            printf("Email must end with '.com'\n");
            return false;
        }
        return true;
    }
}

bool email_domain(char *email){
    int i=0,start=-1,end=-1;
    while(email[i]){
        if(email[i]=='@'){
            start=i;
            if(start<3){
                printf("At least 3 characters present before '@'!\n");
                return false;
            }
        }
        if(email[i]=='.' && start != -1){
            end=i;
            break;
        }
        i++;
    }
    if((end-start-1)>=5){
        start +=1;
        while(start<end){
            if(!isalpha(email[start])){
                printf("Domain contain only alphabets!\n");
                return false;
            }
            start++;
        }
        return true;
    }
    else{
        printf("Domain must have at least 5 characters!\n");
        return false;
    }
    
}

bool email_verify(char *email,int attempt,AddressBook *addressbook,int unique){
    //Email validation
    //email_domain call only after the call of emailat_verify and emailcom_verify
    if(emaillower_verify(email) 
    && emailat_verify(email) && emailstart_verify(email)
    && (unique ? emailunique_verify(email,addressbook):1)
    && emailcom_verify(email) && email_domain(email)){
        return true;
    }
    else{                       
        if(attempt<=3){
            printf("%d outof three attempts\n",attempt);
            printf("Re-enter email: ");
            scanf(" %49[^\n]",email);
            attempt++;
            return email_verify(email,attempt,addressbook,unique);
        }
        else{
            return false;
        }
    }
}

void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
    char tempName[50];
    char tempPhone[20];
    char tempEmail[50];
    int attempt = 1;
    printf("Enter name: ");
    scanf(" %49[^\n]",tempName);

    if(name_verify(tempName,attempt)){
        printf("Enter phone number: ");
        scanf("%19s",tempPhone);

        if(phone_verify(tempPhone,attempt,addressBook,1)){
            printf("Enter the Email: ");
            scanf(" %49[^\n]",tempEmail);

            if(email_verify(tempEmail,attempt,addressBook,1)){ 
                //Save contacts to array
                strcpy(addressBook->contacts[addressBook->contactCount].name,tempName);
                strcpy(addressBook->contacts[addressBook->contactCount].phone,tempPhone);
                strcpy(addressBook->contacts[addressBook->contactCount].email,tempEmail);
                addressBook->contactCount++;
            }
            else{
                printf("three attempts over!\n");
            }
        }
        else{
            printf("three attempts over!\n");
        }
    }
    else{
        printf("three attempts over!\n");
    }   
}

void search_name(AddressBook *addressBook){
    char name[50];
    int serial=0,found;
    printf("Enter the name: ");
    scanf(" %49[^\n]",name);
    //validate
    if(name_verify(name,1)){
        found=0;
        printf("\n%-6s %-20s %-15s %-30s\n","S.no","Name","Phone","Email");
        for(int i=0;i<addressBook->contactCount;i++){
            if(!strcmp(name,addressBook->contacts[i].name)){
                printf("%-6d %-20s %-15s %-30s\n",++serial,addressBook->contacts[i].name,
                    addressBook->contacts[i].phone,addressBook->contacts[i].email);
                arr[serial-1]=i;
                found=1;
            }
        }
        if(!found){
            printf("contact not found!\n");
            return;
        }
        return;
    }
    else{
        printf("three attempt finished!\n");
        return;
    }
}
//phone and email unique dont need to verify in search contacts.
void search_phone(AddressBook *addressBook){
    char phone[20];
    int serial=1,found;
    printf("Enter the phone: ");
    scanf(" %19s",phone);
    //validate
    if(phone_verify(phone,1,addressBook,0)){
        found=0;
        printf("\n%-6s %-20s %-15s %-30s\n","S.no","Name","Phone","Email");
        for(int i=0;i<addressBook->contactCount;i++){
            if(!strcmp(phone,addressBook->contacts[i].phone)){
                arr[serial-1]=i;
                printf("%-6d %-20s %-15s %-30s\n",serial++,addressBook->contacts[i].name,
                    addressBook->contacts[i].phone,addressBook->contacts[i].email);
                
                found=1;
            }
        }
        if(!found){
            printf("contact not found!\n");
            return;
        }
        return;
    }
    else{
        printf("three attempt finished!\n");
        return;
    }
    
}

void search_email(AddressBook *addressBook){
    char email[50];
    int serial=1,found;
    printf("Enter the Email: ");
    scanf(" %49[^\n]",email);
    //validate
    if(email_verify(email,1,addressBook,0)){
        found=0;
        printf("\n%-6s %-20s %-15s %-30s\n","S.no","Name","Phone","Email");
        for(int i=0;i<addressBook->contactCount;i++){
            if(!strcmp(email,addressBook->contacts[i].email)){
                arr[serial-1]=i;
                printf("%-6d %-20s %-15s %-30s\n",serial++,addressBook->contacts[i].name,
                    addressBook->contacts[i].phone,addressBook->contacts[i].email);
                found=1;
            }
        }
        if(!found){
            printf("contact not found!\n");
            return;
        }
        return;
    }
    else{
        printf("three attempt finished!\n");
        return;
    }  
}

void searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
    memset(arr, -1, sizeof(arr));
    int opt;
    printf("Choose the field to search\n");
    printf("1.Name\n2.Phone\n3.Email\n4.Exit\n");
    scanf("%d",&opt);
    switch(opt){
        case 1:
            search_name(addressBook);
            break;
        case 2:
            search_phone(addressBook);
            break;
        case 3:
            search_email(addressBook);
            break;
        case 4:
            return;
        default:
            printf("enter 1/2/3 for choose field\n");
    }
}

void edit_name(AddressBook *addressbook,int serial){
    char name[50];
    printf("Enter New Name: ");
    scanf(" %49[^\n]",name);
    if(name_verify(name,1)){
        strcpy(addressbook->contacts[arr[serial-1]].name,name);
        printf("Successfully updated!\n");
    }
    else{
        printf("Three attempts over!try again later\n");
    }  
}

void edit_phone(AddressBook *addressbook,int serial){
    char phone[20];
    printf("Enter New Phone: ");
    scanf("%19[^\n]",phone);
    if(phone_verify(phone,1,addressbook,1)){
        strcpy(addressbook->contacts[arr[serial-1]].phone,phone);
        printf("Successfully updated!\n");
    }
    else{
        printf("Three attempts over!try again later\n");
    }  
}

void edit_email(AddressBook *addressbook,int serial){
    char email[50];
    printf("Enter New Email: ");
    scanf(" %49[^\n]",email);
    if(email_verify(email,1,addressbook,1)){
        strcpy(addressbook->contacts[arr[serial-1]].email,email);
        printf("Successfully updated!\n");
    }
    else{
        printf("Three attempts over!try again later\n");
    }  
}

void editContact(AddressBook *addressBook)
{
    /* Define the logic for Editcontact */
    int serial,opt;
    searchContact(addressBook);
    if(arr[0]==-1){
        return;
    }
    printf("Enter serial number to Edit that contact:\n");
    while(1){
        scanf("%d",&serial);
        if(serial<=0 || serial>100 || arr[serial-1]==-1){
            printf("invalid selection\n");
            printf("Re-enter the serial number:\n");
        }
        else{
            break;
        }
    }
    printf("choose the field to edit:\n");
    printf("1.Edit by name:\n");
    printf("2.Edit by phone:\n");
    printf("3.Edit by email:\n");
    scanf("%d",&opt);
    switch(opt){
        case 1:
            edit_name(addressBook,serial);
            break;
        case 2:
            edit_phone(addressBook,serial);
            break;
        case 3:
            edit_email(addressBook,serial);
            break;
        default:
            printf("enter the field serial number to edit\n");
    }
}

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
    int serial;
    searchContact(addressBook);
    if(arr[0]==-1){
        return;
    }
    printf("Enter serial number to delete that contact:\n");
    while(1){
        scanf("%d",&serial);
        if(serial<=0 || serial>100 || arr[serial-1]==-1){
            printf("invalid selection\n");
            printf("Re-enter the serial number!\n");
        }
        else{
            break;
        }
    }
    for(int i=arr[serial-1];i<(addressBook->contactCount-1);i++){
        addressBook->contacts[i]=addressBook->contacts[i+1];
    }
    addressBook->contactCount--;
    printf("successfully Deleted the %d contact!",serial);
}