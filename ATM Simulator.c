/*
In order to perform the different functions, the user must enter a card number mentioned in the csv file.
If the user wants to add a new card number or delete an existing card number, then he must do it manually in the ATM_Data.csv file.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
	char card_no[17];
	int pin;
	float balance;
}details;

int withdraw_money(details users[], int l);
int deposit_money(details users[], int l);
int view_balance(details users[], int l);
int change_pin(details users[], int l);
int write_csv(details users[], int n);

int main()
{
	details users[100];
	FILE *data;
	data = fopen("ATM_Data.csv","r");
	if(data == NULL)
	{
		printf("Can't open file.\n");
		getch();
		return -1;
	}
	char line[100];
	int i = 0;
	while(fgets(line,sizeof(line),data))
	{
		char* token = strtok(line,",");
		strcpy(users[i].card_no,token);
		token = strtok(NULL,",");
		users[i].pin = atoi(token);
		token = strtok(NULL,",");
		users[i].balance = atof(token);
		token = strtok(NULL,",");
		i++;
	}
	fclose(data);
	int n = i;
	printf("Welcome to ATM Machine!\n");
	printf("Enter the card number: ");
	char cardno[17];
	scanf("%s", &cardno);
	int k = 0;
	for(i = 0; i < n; i++)
	{
		if(strcmp(cardno,users[i].card_no) == 0)
		{
			k = 1;
			break;
		}
	}
	if(k == 0)
	{
		printf("Invalid Card Number!");
		getch();
		return 0;
	}
	printf("Enter the 4-digit PIN: ");
	int pin;
	scanf("%d", &pin);
	if(users[i].pin != pin)
	{
		printf("Incorrect PIN!");
		getch();
		return 0;
	}
	printf("1. Withdraw Money\n");
	printf("2. Deposit Money\n");
	printf("3. View Balance\n");
	printf("4. Change PIN\n");
	printf("Enter your choice: ");
	int choice;
	scanf("%d", &choice);
	switch(choice)
	{
		case 1:
			withdraw_money(users, i);
			write_csv(users, n);
			printf("Thank you for using the ATM machine.\n");
			break;
		case 2:
			deposit_money(users, i);
			write_csv(users, n);
			printf("Thank you for using the ATM machine.\n");
			break;
		case 3:
			view_balance(users, i);
			printf("Thank you for using the ATM machine.\n");
			break;
		case 4:
			change_pin(users, i);
			write_csv(users, n);
			printf("Thank you for using the ATM machine.\n");
			break;
		default:
			printf("Invalid choice!\n");
	}
	getch();
	return 1;
}

int withdraw_money(details users[], int l)
{
	printf("Enter the amount to be withdrawn: ");
	float wcash;
	scanf("%f", &wcash);
	if (wcash > users[l].balance)
	{
		printf("Insufficient Balance!\n");
		getch();
		return 0;
	}
	else
	{
		users[l].balance -= wcash;
		printf("Balance = Rs. %.2f\n",users[l].balance);
	}
	return 1;
}

int deposit_money(details users[], int l)
{
	printf("Enter the amount to be deposited: ");
	float dcash;
	scanf("%f", &dcash);
	users[l].balance += dcash;
	printf("Balance = Rs. %.2f\n",users[l].balance);
	return 1;
}

int view_balance(details users[], int l)
{
	printf("Balance = Rs. %.2f\n",users[l].balance);
	return 1;
}

int change_pin(details users[], int l)
{
	printf("Enter the new 4-digit PIN: ");
	int new_pin;
	scanf("%d", &new_pin);
	users[l].pin = new_pin;
	printf("New PIN set!\n");
	return 1;
}

int write_csv(details users[], int n)
{
	FILE *data=fopen("ATM_Data.csv","w");
	if(data == NULL)
	{
		printf("Can't open file.\n");
		return -1;
	}
	int i;
	for(i = 0; i < n; i++)
	{
		fprintf(data,"%s,%d,%.2f\n", users[i].card_no, users[i].pin, users[i].balance);
	}
	fclose(data);
	return 1;
}
