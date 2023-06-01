#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>
#include<stdlib.h>
using namespace std;
struct bank
{
double account_no;
string name, city, state;
int zip;
char telephone[15];
double account_balance;
string last_payment;
};
int menu(); //This function display a menu and ask user that what he wants to perfome
int new_record(fstream &,bank);//This function enter a new record in the file
double same_account_no( double , bank); //If user enter account no which is already taken
 //then this fucntion stops the user
int display_record(fstream &, bank); //Display Records that is present in the file
int delete_record(bank); //Delete a record From the file
void display_specific_rec( bank,double); //Display any account from the file
int update_record(bank); //Update any record from the file
void deposit_amount(bank,double,double); //This function deposit amount to the account
void withdraw_amount(bank,double,double); //This function withdraw amount from the account
int balance_inquiry(fstream&, bank); //Show the balance for any customer
int transfer_amount(bank);//transfer amount from one account to another
int go_back();//to go to main menu
double negative_balance(double);//If user enter negative balance then this function ask user to input again
int not_find(bank , double );//If account.no not found then this function tell the user that account does not exist
int main()
{
	fstream record;
	bank customer;
	int y, acount_no = 0;
	double x, account_no;
	cout << "\n\t\t\t\t ***WELCOME TO OUR BANK***" << endl << endl;
	system("pause");
	y = menu();
	while (y != 10) //If user press 10 then this loop terminate andprogram end
	{
	system("CLS");
	switch (y)
{
case 1:
{
y = new_record(record, customer);
break;
}
case 2:
{
y = display_record(record, customer);
 break;
}
case 3:
{
y = delete_record(customer);
break;
}
case 4:
{ 	
	cout << "\n\t Which record do you want to see" <<endl;
 	cout << "\n\t Enter Account number" << endl;
 	cin >> account_no;
	display_specific_rec(customer,account_no);
y = go_back();
break;
}
case 5:
{
y = update_record(customer);
break;
}
case 6:
{
y = balance_inquiry(record, customer);
break;
}
case 7:
{
cout << "\n\t Enter Account number in which you want to deposit amount" << endl;
cin >> account_no;
cout << "\n\t Enter the amount you want to deposit" << endl;
cin >> x;
deposit_amount(customer, account_no, x);
y = go_back();
break;
}
case 8:
{
cout << "\n\t Enter Account number from which you want to withdraw amount" << endl;
cin >> account_no;
cout << "\n\t Enter the amount you want to withdraw" << endl;
cin >> x;
withdraw_amount(customer, account_no, x);
y = go_back();
break;
}
case 9:
{
y = transfer_amount(customer);
break;
}
default:
{
cout << "Invalid input" << endl;
break;
}
}
}
cout << "\n\t\t\t\t ** THANKS FOR COMING TO OUR BANK**" << endl;
system("pause");
}
int menu()
{
int choice;
cout << "\n \t Which option do you want to perfome" << endl;
cout << "\n \t Press-1 for enter a new record" << endl;
cout << "\n \t Press-2 for displaying a records" << endl;
cout << "\n\t Press-3 to delete a record" << endl;
cout << "\n\t Press-4 to display a specific record" << endl;
cout << "\n\t Press-5 to update a record" << endl;
cout << "\n\t Press-6 for Balance Inquiry" << endl;
cout << "\n\t Press-7 to deposit amount " << endl;
cout << "\n\t Press-8 to withdraw amount " << endl;
cout << "\n\t Press-9 to transfer amount " << endl;
cout << "\n\t Press-10 to exit " << endl;
cin >> choice;
return choice;
}
int new_record(fstream &file,bank customers) //Enter a new record in the file
{
loop:
file.open("rec.txt", ios::out | ios::app);
char again;
int y;
double num;
cout << "Enter Account number" << endl;
cin >> customers.account_no;
customers.account_no=same_account_no(customers.account_no,
customers); //Function call
 //If user enter account no which is already taken
 //then this fucntion stops the user
cout << "Enter Name" << endl;
cin.ignore();
getline(cin, customers.name);
if (customers.name == "") //If user did not enter data then this if statement will ask user to input again
{
cout << "\tYou can not left this field. Input again!" << endl;
cin >> customers.name;
}
cout << "Enter City" << endl;
cin.ignore();
getline(cin, customers.city);
if (customers.city == "")//If user did not enter data then this if statement will ask user to input again
{
cout << "\tYou can not left this field. Input again!" << endl;
cin >> customers.city;
}
cout << "Enter State" << endl;
getline(cin, customers.state);
cin.ignore();
if (customers.state== "")//If user did not enter data then this if statement will ask user to input again
{
cout << "\tYou can not left this field. Input again!" << endl;
cin >> customers.state;
}
cout << "Enter Zip Code" << endl;
cin >> customers.zip;
cout << "Enter Telephone number" << endl;
cin >> customers.telephone;
cout << "Enter your Total Balance" << endl;
cin >> customers.account_balance;
customers.account_balance=negative_balance(customers.account_balance); //If user enter negative account balance then this fuction
 //will stop the userfrom doing this
cout << "Enter the Date of Last Payment" << endl;
cin.ignore();
getline(cin ,customers.last_payment);
if (customers.last_payment == "")//If user did not enter data then this if statement will ask user to input again
{
cout << "\tYou can not left this field. Input again!" << endl;
cin >> customers.last_payment;
}
file << customers.account_no << endl;
file << customers.name << endl;
file << customers.city << endl;
file << customers.state << endl;
file << customers.zip << endl; //writing data to a file
file << customers.telephone << endl;
file << customers.account_balance << endl;
file << customers.last_payment << endl;
file.close();
cout << "Do you want to enter again a new record? (y/n)" << endl;
cin >> again; //if user want to enter a new record again
 //then this if statement will work
if(again=='y')
{
goto loop;
}
else
{
y= go_back(); //To go back to main menu
}
return y;
}
double same_account_no(double number,bank same) //If user enter account no which is already taken
 //then this fucntion stops the user
{
fstream x;
x.open("rec.txt", ios::in);
x >> same.account_no;
x.get();
getline(x, same.name);
getline(x, same.city);
getline(x, same.state);
x >> same.zip;
x >> same.telephone;
x >> same.account_balance;
x.get();
getline(x, same.last_payment);
while (!x.eof())
{
while (number==same.account_no)
{
cout << "\n\tThis Account number is already taken" << endl << endl;
cout << "\n\tInput customer Account number again" << endl;
cin >> number;
}
x >> same.account_no;
x.get();
getline(x, same.name);
getline(x, same.city);
getline(x, same.state);
x >> same.zip;
x >> same.telephone;
x>> same.account_balance;
x.get();
getline(x, same.last_payment);
 }
x.close();
return number;
}
int display_record( fstream &file,bank persons) //Display Records that is present in the file
{
int y;
cout <<"*******************************************************************************************************"<<"*********************" << endl;
file.open("rec.txt", ios::in);
file >> persons.account_no;
file.get();
getline(file, persons.name);
getline(file, persons.city);
getline(file, persons.state);
file >> persons.zip;
file >> persons.telephone;
file >> persons.account_balance;
file.get();
getline(file, persons.last_payment);
cout << " Account ID" << setw(10);
cout << " Name" << setw(12);
cout << " City" << setw(18);
cout << " State" << setw(12);
cout << " Zip Code" << setw(18);
cout << " Telephone number" <<setw(15);
cout << " Account Balance" << setw(15);
cout << "Last Payment" << endl;
while (!file.eof())
{
cout<<" " <<persons.account_no << setw(19);
cout<<persons.name << setw(15);
cout<<persons.city << setw(15);
cout<<persons.state << setw(8);
cout<<persons.zip << setw(18);
cout<<persons.telephone <<setw(15);
cout<<persons.account_balance << setw(15);
cout<<persons.last_payment << endl;
file >> persons.account_no;
file.get();
getline(file, persons.name);
getline(file, persons.city);
getline(file, persons.state);
file >> persons.zip;
file >> persons.telephone;
file >> persons.account_balance;
file.get();
getline(file, persons.last_payment);
}
file.close();
y=go_back(); //To go back to main menu
return y;
}
int delete_record(bank data) //Delete a record From the file
{
int y;
double num;
cout << "Enter account number which you want to delete" << endl;
cin >> num;
not_find(data, num); //If user enter account no which is not present then this fuction tell the user
ifstream read("rec.txt");
ofstream write("new.txt");
read >> data.account_no;
read.get();
getline(read, data.name);
getline(read, data.city);
 //READ data from the existing file
getline(read, data.state);
read >> data.zip;
read >> data.telephone;
read >> data.account_balance;
read.get();
getline(read, data.last_payment);
while (!read.eof())
{
if (data.account_no != num)
{
write << data.account_no << endl;
write << data.name << endl;
write << data.city << endl;
write << data.state << endl;
write << data.zip << endl; //WRITE data to the new file IF account.no not found
write << data.telephone << endl;
write << data.account_balance << endl;
write << data.last_payment << endl;
}
else
{
cout << "\n\t Record Deleted" << endl; //Did not write data when account.no found
}
read >> data.account_no;
read.get();
getline(read, data.name);
getline(read, data.city);
getline(read, data.state);
read >> data.zip;
read >> data.telephone;
read >> data.account_balance;
read.get();
getline(read, data.last_payment);
}
write.close();
read.close();
remove("rec.txt"); //Remove previous file
rename("new.txt", "rec.txt"); //Rename file name to the previous file name
y = go_back();
return y;
}
void display_specific_rec(bank e,double y) //Display any account from the file
{
fstream file;
int x;
file.open("rec.txt", ios::in);
not_find( e,y); //If user enter account no which is not present then this fuction tell the user
file >> e.account_no;
file.get();
getline(file, e.name);
getline(file, e.city);
getline(file, e.state);
file >> e.zip;
file >> e.telephone;
file >> e.account_balance;
file.get();
getline(file, e.last_payment);
while (!file.eof())
{
if (e.account_no == y)
{
cout << "\n\t Customer Account number is:" << e.account_no << endl;
cout << "\n\t Customer Name is:" << e.name <<endl;
cout << "\n\t Customer City is:" << e.city <<endl;
cout << "\n\t Customer State is:" << e.state <<endl;
cout << "\n\t Customer Zip Code is:" << e.zip <<endl;
cout << "\n\t Customer Telephone number is:" <<e.telephone << endl;
cout << "\n\t Customer Account Balance is:" <<e.account_balance << endl;
cout << "\n\t Date of Last Payment in Customer Account is:" << e.last_payment << endl;
}
file >> e.account_no;
file.get();
getline(file, e.name);
getline(file, e.city);
getline(file, e.state);
file >> e.zip;
file >> e.telephone;
file >> e.account_balance;
file.get();
getline(file, e.last_payment);
}
file.close();
}
int update_record( bank update) //Update any record from the file
{
int y;
double num;
ifstream read("rec.txt");
ofstream write("new.txt");
cout << "Enter account number which you want to update" <<endl; //ask user to enter account.no which he want to update
cin >> num;
cout << "\n\t Customer details are:" << endl;
display_specific_rec( update, num); //Display a record which user want to update
cout << endl << endl;
read >> update.account_no;
read.get();
getline(read, update.name);
getline(read, update.city);
getline(read, update.state); //Read data
read >> update.zip;
read >> update.telephone;
read >> update.account_balance;
read.get();
getline(read, update.last_payment);
while (!read.eof())
{
if (update.account_no != num)
{
write << update.account_no << endl;
write << update.name << endl;
write << update.city << endl;
write << update.state << endl; //Write data in the new file if account.no not found
write << update.zip << endl;
write << update.telephone << endl;
write << update.account_balance << endl;
write << update.last_payment << endl;
}
else //If account.no found then program ask user to enternew data except account.no
{
cout << "Enter Name" << endl;
cin.ignore();
getline(cin, update.name);
cout << "Enter City" << endl;
cin.ignore();
getline(cin, update.city);
if (update.city == "") //If user did not enter data thenthis if statement will ask user to input again
{
cout << "\tYou can not left this field. Input again!" << endl;
cin >> update.city;
}
cout << "Enter State" << endl;
cin.ignore();
getline(cin, update.state);
if (update.state == "")//If user did not enter data then this if statement will ask user to input again
{
cout << "\tYou can not left this field. Input again!" << endl;
cin >> update.state;
}
cout << "Enter Zip Code" << endl;
cin >> update.zip;
cout << "Enter Telephone number" << endl;
cin >> update.telephone;
cout << "Enter your Total Balance" << endl;
cin >> update.account_balance;
update.account_balance=negative_balance(update.account_balance
);
cout << "Enter the Date of Last Payment" << endl;
cin.ignore();
getline(cin, update.last_payment);
write << update.account_no << endl;
write << update.name << endl;
write << update.city << endl;
write << update.state << endl;
write << update.zip << endl; //Write new data to the new file
write << update.telephone << endl;
write << update.account_balance << endl;
write << update.last_payment << endl;
}
read >> update.account_no;
read.get();
getline(read, update.name);
getline(read, update.city);
getline(read, update.state);
read >> update.zip;
read >> update.telephone;
read >> update.account_balance;
read.get();
getline(read, update.last_payment);
}
write.close();
read.close();
remove("rec.txt"); //remove previous file
rename("new.txt", "rec.txt"); //rename filename
y = go_back();
return y;
}
void deposit_amount(bank deposit,double num,double amount) //This function deposit amount
{
ifstream read("rec.txt");
ofstream write("new.txt");
not_find(deposit, num); //If user enter account no which is not present then this fuction tell the user
read >> deposit.account_no;
read.get();
getline(read, deposit.name);
getline(read, deposit.city);
getline(read, deposit.state); //read data
read >> deposit.zip;
read >> deposit.telephone;
read >> deposit.account_balance;
read.get();
getline(read, deposit.last_payment);
while (!read.eof())
{
if (deposit.account_no != num) //write data to the new file
{
write << deposit.account_no << endl;
write << deposit.name << endl;
write << deposit.city << endl;
write << deposit.state << endl;
write << deposit.zip << endl;
write << deposit.telephone << endl;
write << deposit.account_balance << endl;
write << deposit.last_payment << endl;
}
else //write new balance in the new file if account.no found
{
deposit.account_balance = deposit.account_balance +
amount;
write << deposit.account_no << endl;
write << deposit.name << endl;
write << deposit.city << endl;
write << deposit.state << endl;
write << deposit.zip << endl;
write << deposit.telephone << endl;
write << deposit.account_balance << endl;
write << deposit.last_payment << endl;
cout << "\n\t The updated balance of account no"<<" "<<deposit.account_no << " " <<"is:"<<" " << deposit.account_balance <<endl;
//Show updated Balance


}
read >> deposit.account_no;
read.get();
getline(read, deposit.name);
getline(read, deposit.city);
getline(read, deposit.state);
read >> deposit.zip;
read >> deposit.telephone;
read >> deposit.account_balance;
read.get();
getline(read, deposit.last_payment);
}
write.close();
read.close();
remove("rec.txt"); //Remove file
rename("new.txt", "rec.txt"); //rename filename
}
void withdraw_amount(bank withdraw,double acc,double amount)
//This function withdraw amount from the account
{
ifstream read("rec.txt");
ofstream write("new.txt");
not_find(withdraw, acc); //If user enter account no which is not present then this fuction tell the user
read >> withdraw.account_no;
read.get();
getline(read, withdraw.name);
getline(read, withdraw.city);
getline(read, withdraw.state); //read data
read >> withdraw.zip;
read >> withdraw.telephone;
read >> withdraw.account_balance;
read.get();
getline(read, withdraw.last_payment);
while (!read.eof())
{
if (withdraw.account_no != acc) //write data to the new file
{
write << withdraw.account_no << endl;
write << withdraw.name << endl;
write << withdraw.city << endl;
write << withdraw.state << endl;
write << withdraw.zip << endl;
write << withdraw.telephone << endl;
write << withdraw.account_balance << endl;
write << withdraw.last_payment << endl;
}
else //write new balance in the new file if account.no found
{
while(withdraw.account_balance < amount)
{
cout << "\n \t You have not sufficient balance in your account" << endl;
cout << "\n\t Enter the amount you want to withdraw" << endl;
cin >> amount;
}
withdraw.account_balance = withdraw.account_balance
- amount;
write << withdraw.account_no << endl;
write << withdraw.name << endl;
write << withdraw.city << endl;
write << withdraw.state << endl;
write << withdraw.zip << endl;
write << withdraw.telephone << endl;
write << withdraw.account_balance << endl;
write << withdraw.last_payment << endl;
cout << "\n\t The updated balance of account number"<<" "<<withdraw.account_no<<" "<<"is:"<<" " << withdraw.account_balance <<
endl;
}
read >> withdraw.account_no;
read.get();
getline(read, withdraw.name);
getline(read, withdraw.city);
getline(read, withdraw.state);
read >> withdraw.zip;
read >> withdraw.telephone;
read >> withdraw.account_balance;
read.get();
getline(read, withdraw.last_payment);
}
write.close();
read.close();
remove("rec.txt"); //remove file
rename("new.txt", "rec.txt"); //rename filename
}
int balance_inquiry(fstream& file, bank balance)//Show the balance for any customer
{
int y;
double no;
cout << "\n\t Enter Account number of which you want to see a balance" << endl;
cin >> no;
not_find(balance, no);//THis function tell user if account.no did not exist
file.open("rec.txt", ios::in);
file >> balance.account_no;
file.get();
getline(file, balance.name);
getline(file, balance.city);
getline(file, balance.state); //read data
file >> balance.zip;
file >> balance.telephone;
file >> balance.account_balance;
file.get();
getline(file, balance.last_payment);
while (!file.eof())
{
if (balance.account_no == no) //If account.no found then display the balance
{
cout << "\t Balance in account no \t" << balance.account_no << " " << "is :\t" << balance.account_balance <<endl;
}
file >> balance.account_no;
file.get();
getline(file, balance.name);
getline(file, balance.city);
getline(file, balance.state);
file >> balance.zip;
file >> balance.telephone; //read data till end of file
file >> balance.account_balance;
file.get();
getline(file, balance.last_payment);
}
file.close();
y = go_back();
return y;
}
int transfer_amount(bank transfer) //transfer amount from one account to another
{
int y, a, b;
double acc1, acc2, amount;
cout << "\t Enter the account no from which you want to withdraw amount" << endl;
cin >> acc1;
a=not_find(transfer, acc1); //if account.no not found then thisfunction tell user
if (a == 1)
{
goto end;
}
cout << "\t Enter the account no in which you want deposit amount" << endl;
cin >> acc2;
b = not_find(transfer, acc2);//if account.no not found then this function tell user
if (b== 1)
{
goto end;
}
cout << "\t How much amount do you want to transfer" << endl;
cin >> amount;
withdraw_amount(transfer, acc1, amount); //This function withdraw amount from the customer who transfer amount
deposit_amount(transfer, acc2, amount); //This function add amount to the coustomer in which amounts add
cout << "\n\t Amount transfer successfuly" << endl;
end:
y = go_back(); //to go to the main menu
return y;
}
int go_back() //to go to main menu
{
int k, n;
cout << "\n\tTo go back to the main menu Press-0" << endl;
cin >> k;
while (k != 0) //If user enter other than 0 then this loop ask user to input again
{
cout << "\t Invalid Input" << endl;
cout << "\n\tTo go back to the main menu Press -0" << endl;
cin >> k;
}
if (k == 0) //If user press 0 then main menu will display
{
system("CLS");
return menu();
}
}
double negative_balance(double number) //If user enter negative balance then this function ask user to input again
{
while (number < 0)
{
cout << "\n\t Balance can't be a nagative number " << endl;
cout << "\tInput Again" << endl;
cin >> number;
}
return number;
}
int not_find(bank find, double num)//If account.no not found then this function tell the user
{
int flag = 0;
fstream file;
file.open("rec.txt", ios::in);
file >> find.account_no;
file.get();
getline(file, find.name);
getline(file, find.city);
getline(file, find.state); //read data
file >> find.zip;
file >> find.telephone;
file >> find.account_balance;
file.get();
getline(file, find.last_payment);
while (!file.eof())
{
if (find.account_no == num) 
{
flag = 1; //IF account.no found then flag will become 1
}
file >> find.account_no;
file.get();
getline(file, find.name);
getline(file, find.city);
getline(file, find.state);
file >> find.zip;
file >> find.telephone; //read data till the end of file
file >> find.account_balance;
file.get();
getline(file, find.last_payment);
}
if (flag == 0)
{
cout << "\n\t **Account not found**" << endl;
return 1;
}
file.close();
}