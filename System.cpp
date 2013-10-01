#include "Lexer.h"
#include "System.h"
#include <fstream>
#include <iostream>

Lexer lex;

System::System(){}
System::~System(){}

void removeCustomer(string name){
	ofstream file;
	file.open("Customers", std::ios_base::app);
	if(file.is_open()){
		file << "DELETE FROM Customers WHERE Name == " + name + ";\n";
		file.close();
	}
	else{
		printf("Cannot open file \"Products\"\n");
	}
}

void removeTransaction(string name){
	ofstream file;
	file.open("Transactions", std::ios_base::app);
	if(file.is_open()){
		file << "DELETE FROM Transactions WHERE ID == " + name + ";\n";
		file.close();
	}
	else{
		printf("Cannot open file \"Products\"\n");
	}
}

void removeProduct(string name){
	ofstream file;
	file.open("Products", std::ios_base::app);
	if(file.is_open()){
		file << "DELETE FROM Products WHERE Name == " + name + ";\n";
		file.close();
	}
	else{
		printf("Cannot open file \"Products\"\n");
	}
}

void removeEmployee(string name){
	ofstream file;
	file.open("Employees", std::ios_base::app);
	if(file.is_open()){
		file << "DELETE FROM Employees WHERE name == " + name + ";\n";
		file.close();
	}
	else{
		printf("Cannot open file \"Employees\"\n");
	}
}

void addEmployee(){
	string name, id, position;
	printf("Please enter the new employee's name:\n");
	cin >> name;
	printf("Please enter the new employee's ID number:\n");
	cin >> id;
	printf("Please enter the new employee's position:\n");
	cin >> position;
	
	ofstream file;
	file.open("Employees", std::ios_base::app);
	if(file.is_open()){
		file << "INSERT INTO Employees VALUES FROM (\"" + name + "\", \"" + id + "\", \"" + position + "\");\n";
		file.close();
	}
	else{
		printf("Cannot open file \"Employees\"\n");
	}
}

void addCustomer(){
	string name, id, level;
	printf("Please enter the new customer's name:\n");
	cin >> name;
	printf("Please enter the new customer's ID number:\n");
	cin >> id;
	printf("Please enter the new customer's level:\n");
	cin >> level;
	
	ofstream file;
	file.open("Customers", std::ios_base::app);
	if(file.is_open()){
		file << "INSERT INTO Customers VALUES FROM (\"" + name + "\", \"" + id + "\", \"" + level + "\");\n";
		file.close();
	}
	else{
		printf("Cannot open file \"Customers\"\n");
	}
}

void addProduct(){
	string name, id;
	int price, quant;
	printf("Please enter the new product's name:\n");
	cin >> name;
	printf("Please enter the new product's UPC number:\n");
	cin >> id;
	printf("Please enter the new product's price:\n");
	cin >> price;
	printf("Please enter the quantity of the new product:\n");
	cin >> quant;
	
	ofstream file;
	file.open("Products", std::ios_base::app);
	if(file.is_open()){
		file << "INSERT INTO Products VALUES FROM (\"" + name + "\", \"" + id + "\", \"" << price << "\", \"" << quant << "\");\n";
		file.close();
	}
	else{
		printf("Cannot open file \"Products\"\n");
	}
}

void addTransaction(){
	string id, date, time;
	int rev;
	printf("Please enter the date (MM\\DD\\YYYY):\n");
	cin >> date;
	printf("Please enter the time (HH:MM):\n");
	cin >> time;
	printf("Please enter the new transaction's ID number:\n");
	cin >> id;
	printf("Please enter the net revenue for the transaction:\n");
	cin >> rev;
	
	ofstream file;
	file.open("Transactions", std::ios_base::app);
	if(file.is_open()){
		file << "INSERT INTO Transactions VALUES FROM (\"" + date + "\", \"" + time + "\", \"" + id + "\", \"" << rev << "\");\n";
		file.close();
	}
	else{
		printf("Cannot open file \"Transactions\"\n");
	}
}

void updateEmployee(){
	string attr;
	printf("Which employee attribute do you wish to update?:\n");
	cin >> attr;
	printf("What is the current value of the attribute you wish to update?:\n");
	string old;
	cin >> old;
	printf("What do you want to change that attribute to?\n:");
	string changed;
	cin >> changed;
	
	ofstream file;
	file.open("Employees", std::ios_base::app);
	if(file.is_open()){
		file << "UPDATE Employees SET" << attr << " = " << changed << "WHERE " << attr << " == " << old << ";";
		file.close();
	}
	else{
		printf("Cannot open file \"Employees\"\n");
	}
}

void updateCustomer(){
	string attr;
	printf("Which customer attribute do you wish to update?:");
	cin >> attr;
	printf("What is the current value of the attribute you wish to update?:\n");
	string old;
	cin >> old;
	printf("What do you want to change that attribute to?:\n");
	string changed;
	cin >> changed;
	
	ofstream file;
	file.open("Customers", std::ios_base::app);
	if(file.is_open()){
		file << "UPDATE Customers SET" << attr << " = " << changed << "WHERE " << attr << " == " << old << ";";
		file.close();
	}
	else{
		printf("Cannot open file \"Customers\"\n");
	}
}

void updateProduct(){
	string attr;
	printf("Which product attribute do you wish to update?:");
	cin >> attr;
	printf("What is the current value of the attribute you wish to update?:\n");
	string old;
	cin >> old;
	printf("What do you want to change that attribute to?:");
	string changed;
	cin >> changed;
	
	ofstream file;
	file.open("Products", std::ios_base::app);
	if(file.is_open()){
		file << "UPDATE Products SET" << attr << " = " << changed << "WHERE " << attr << " == " << old << ";";
		file.close();
	}
	else{
		printf("Cannot open file \"Products\"\n");
	}
}

void updateTransaction(){
	string attr;
	printf("Which transaction attribute do you wish to update?:");
	cin >> attr;
	printf("What is the current value of the attribute you wish to update?:\n");
	string old;
	cin >> old;
	printf("What do you want to change that attribute to?:\n");
	string changed;
	cin >> changed;
	
	ofstream file;
	file.open("Transactions", std::ios_base::app);
	if(file.is_open()){
		file << "UPDATE Transactions SET" << attr << " = " << changed << "WHERE " << attr << " == " << old << ";";
		file.close();
	}
	else{
		printf("Cannot open file \"Transactions\"\n");
	}
}

void System::showMainMenu(){
  int option = 0;
  while (option != 5){
    printf("POINT OF SALE MENU: \n  1)Display  \n  2)Create  \n  3)Update  \n  4)Delete  \n  5)EXIT \n");
    cin >> option;
    switch(option){
    case 1:
      System::showDisplayMenu();
      break;
    case 2:
      System::showCreateMenu();
      break;
    case 3:
      System::showUpdateMenu();
      break;
    case 4:
      System::showDeleteMenu();
      break;
    case 5:
      break;
      //write all data to a file and close out 
    }
  }
  cout << "GOOD BYE";
}

void System::showDisplayMenu(){
  int option = 0;
  
  lex.readFile("Employees");
  lex.readFile("Products");
  lex.readFile("Customers");
  lex.readFile("Transactions");
  
  string  input;
  while (option != 3){
    printf("DISPLAY MENU:\n 1)Single Customer/Product/Transaction\n 2)All\n 3)BACK TO MAIN MENU\n");
    cin >> option;
    switch(option){
    	case 1:
    	  printf("Enter name of Customer/Product/Transaction:");
    	  cin >> input;
	      printf("\nPrinting...\n");
    	  (lex.p.man)->show(input);
    	  break;
    	case 2:
    	  printf("Printing all...\n");
	  for(int i = 0; i < (lex.p.man)->database.relations.size(); i++){
	    (lex.p.man)->show(&(lex.p.man)->database.relations[i]);
	  }
    	  break;
    	case 3:
			break;
    }
  }
}

void System::showCreateMenu(){
	int option = 0;
	while(option != 4){
		printf("CREATE MENU:\n 1) Create an employee\n 2) Create a customer\n 3) Create a product\n 4) New transaction\n 5) BACK\n");
		cin >> option;
	
		switch(option){
			case 1:
				addEmployee();
				break;
			case 2:
				addCustomer();
				break;
			case 3:
				addProduct();
				break;
			case 4:
				addTransaction();
				break;
			case 5:
				break;
		}
	}
}

void System::showUpdateMenu(){
	int option = 0;
	while(option != 4){
	  printf("UPDATE MENU:\n 1)Update an employee\n 2)Update a customer\n 3) Update a product\n 4)Update a transaction\n 5) BACK TO MAIN MENU\n");
	  cin >> option;
	  switch(option){
		case 1:
		  updateEmployee();
		  break;
		case 2:
		  updateCustomer();
		  break;
		case 3:
		  updateProduct();
		  break;
		case 4:
		  updateTransaction();
		  break;
		case 5:
		  break;
	  }
	}
}

void System::showDeleteMenu(){
 	int option = 0;
	string input;
 	while(option != 5){
 	  printf("DELETE MENU:\n  1)Delete an employee\n  2) Delete a product\n  3)Delete a transaction\n  4) Delete a customer\n  5) BACK TO MAIN MENU\n");
 	  cin >> option;
 	  switch(option){
 	  	case 1:
    		  printf("Enter name of Employee to be deleted: \n");
    	   	  cin >> input;
	  	  printf("\nDeleting...\n");
    	  	  removeEmployee(input);
    	  	  printf("\nDeleted.\n");
    		  break;
 	  	case 2:
 	  	  printf("Enter name of Product to be deleted: \n");
    	   	  cin >> input;
	  	  printf("\nDeleting...\n");
    	  	  removeProduct(input);
    	  	  printf("\nDeleted.\n");
    		  break;
 	  	case 3:
 	  	  printf("Enter ID of Transaction to be deleted: \n");
    	   	  cin >> input;
	  	  printf("\nDeleting...\n");
    	  	  removeTransaction(input);
    	  	  printf("\nDeleted.\n");
    		  break;
		case 4:
			printf("Enter the name of Customer to be deleted: \n");
			cin >> input;
			printf("\nDeleting...\n");
			removeCustomer(input);
			break;
 	  	case 5:
			break;
 	  }
 	}
}
