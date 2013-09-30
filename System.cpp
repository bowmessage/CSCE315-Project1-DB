#include "Lexer.h"
#include "System.h"
#include <fstream>
#include <iostream>

Lexer lex;

System::System(){}
System::~System(){}



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
	printf("Please enter the quantity of the new product:");
	cin >> quant;
	
	ofstream file;
	file.open("Products", std::ios_base::app);
	if(file.is_open()){
		file << "INSERT INTO Products VALUES FROM (\"" + name + "\", \"" + id + "\", \"" + price + "\", \"" + quant + "\");\n";
		file.close();
	}
	else{
		printf("Cannot open file \"Products\"\n");
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
      //System::showUpdateMenu();
      break;
    case 4:
      //System::showDeleteMenu();
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
				printf("Create a new transaction here!\n");
				break;
			case 5:
				printf("Take it on back\n");
				break;
		}
	}
}

void System::showUpdateMenu(){
	int option = 0;
	while(option != 4){
	  printf("UPDATE MENU:\n 1)Update an employee/customer\n 2) Update a product\n 3)Update a transaction\n 4) BACK TO MAIN MENU\n");
	  cin >> option;
	  switch(option){
		case 1:
		  printf("");
		  break;
		case 2:
		  printf("");
		  break;
		case 3:
		  printf("");
		  break;
		case 4:
			break;
	  }
	}
}

void showDeleteMenu(){
 	int option = 0;
	string input;
 	while(option != 4){
 	  printf("DELETE MENU:\n 1)Delete an employee/customer\n 2) Delete a product\n 3)Delete a transaction\n 4) BACK TO MAIN MENU\n");
 	  cin >> option;
 	  switch(option){
 	  	case 1:
    		  printf("Enter name of Customer/Employee to be deleted:");
    	   	  cin >> input;
	  	  printf("\nDeleting...\n");
    	  	  (lex.p.man)->deleteTable(input);
    	  	  printf("\nDeleted.\n");
    		  break;
 	  	case 2:
 	  	  printf("Enter name of Product to be deleted:");
    	   	  cin >> input;
	  	  printf("\nDeleting...\n");
    	  	  (lex.p.man)->deleteTable(input);
    	  	  printf("\nDeleted.\n");
    		  break;
 	  	case 3:
 	  	  printf("Enter name of Transaction to be deleted:");
    	   	  cin >> input;
	  	  printf("\nDeleting...\n");
    	  	  (lex.p.man)->deleteTable(input);
    	  	  printf("\nDeleted.\n");
    		  break;
 	  	case 4:
		  break;
 	  }
 	}
}
