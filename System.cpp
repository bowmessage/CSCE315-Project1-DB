#include "DatabaseManager.h"
#include "System.h"
#include <iostream>

System::System(){}
System::~System(){}


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
      //write all data to a file and close out 
    }
  }
  cout << "GOOD BYE";
}

void System::showDisplayMenu(){
  int option = 0;
  string  input;
  while (option != 3){
    printf("DISPLAY MENU:\n 1)Single Customer/Product/Transaction\n 2)All\n 3)BACK TO MAIN MENU\n");
    cin >> option;
    switch(option){
    	case 1:
    	  printf("Enter name of Customer/Product/Transaction:");
    	  cin >> input;
	  printf("\nPrinting...\n");
    	  s.dbms.show(getRelationByName(input));
    	  break;
    	case 2:
    	  printf("Printing all...\n")
	  for(int i = 0; i < s.dbms.database.relations.size(); i++){
	    s.dbms.show(s.dbms.database.relations[i]);
	  }
    	  break;
    	case 3:
        showMainMenu();
	  break;
    }
  }
  showMainMenu();
}

void System::showCreateMenu(){
	int option = 0;
	while(option != 4){
		printf("CREATE MENU:\n 1) Create an employee\n 2) Create a product\n 3) New transaction\n 4) BACK\n");
		cin >> option;
	
		switch(option){
			case 1:
				printf("Create a new employee/customer here\n");
				break;
			case 2:
				printf("Create a new product here!\n");
				break;
			case 3:
				printf("Create a new transaction here!\n");
				break;
			case 4:
				printf("Take it on back\n");
				break;
		}
	}
}

void System::showUpdateMenu(){
	int option = 0;
	while(option != ){
	  printf("UPDATE MENU:\n 1)Update an employee/customer\n 2) Update a product\n 3)Update a transaction\n 4) BACK TO MAIN MENU\n");
	  cin >> option;
	  switch(option){
		case 1:
		  printf("");
		  break;
		case 2;
		  printf("");
		  break;
		case 3:
		  printf("");
		  break;
		case 4:
		  showMainMenu();
	  }
	}
	showMainMenu();
}

void showDeleteMenu(){
 	int option = 0;
 	while(option != 4){
 	  printf("DELETE MENU:\n 1)Delete an employee/customer\n 2) Delete a product\n 3)Delete a transaction\n 4) BACK TO MAIN MENU\n");
 	  cin >> option;
 	  switch (option){
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
 	  	  showMainMenu();
 	  }
 	}
 	showMainMenu();
}
