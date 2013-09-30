#include "DatabaseManager.h"
#include "System.h"
#include <iostream>

System::System(){}
System::~System(){}


//this funciton is done, used to initialize the menu and program
//a function will be made for each menu and sub menu to keep the main function clean and the program easier to debug
void System::showMainMenu(){
  int option = 0;
  while (option != 6){
    printf("POINT OF SALE MENU: \n  1)Display  \n  2)Create  \n  3)Update  \n  4)Search  \n  5)Delete  \n  6)EXIT \n");
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
      //System::showSearchMenu();
      break;
    case 5:
      //System::showDeleteMenu();
      break;
    }
  }
  cout << "GOOD BYE";
}

//need input from prof before continuing further
/*void System::showDisplayMenu(){
  int option = 0;
  string  input;
  while (option != 3){
    printf("DISPLAY MENU:  \n  1)Single Customer/Product/Transaction  \n  2)All  \n  3)BACK TO MAIN MENU  \n ");
    cin >> option;
    switch(option){
    	case 1:
    		printf("Enter name of Customer/Product/Transaction:");
    		cin >> input;
    		s.dbms.show(getRelationByName(input));
    		break;
    	case 2:
    		printf("")
    	
    	case 3:
    }
    
	}
}*/ 

void System::showCreateMenu(){
	int option = 0;
	while(option != 4){
		printf("CREATE MENU: \n  1) Create an employee \n  2) Create a product \n  3) New transaction \n  4) BACK \n");
		cin >> option;
	
		switch(option){
			case 1:
				printf("Create a new employee here!\n");
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
