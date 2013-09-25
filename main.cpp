#include <DatabasManager.h>
#include <iostream>

//this funciton is done, used to initialize the menu and program
//a function will be made for each menu and sub menu to keep the main function clean and the program easier to debug
void showMainMenu(){
  int option = 0;
  while (option != 5){
    cout << "POINT OF SALE MENU: \n  1)Display  \n  2)Create  \n  3)Update  \n  4)Search  \n  5)Delete  \n  6)EXIT \n";
    cin >> option;
    switch(option){
    case 1:
      showDisplayMenu();
      break;
    case 2:
      showCreateMenu();
      break;
    case 3:
      showUpdateMenu();
      break;
    case 4:
      showSearchMenu();
      break;
    case 5:
      showDeleteMenu();
      break;
    }
  }
  cout << "GOOD BYE";
}

//need input from prof before continuing further
void showDisplayMenu(){
  int option = 0;
  string  
  while (option != 3){
    cout << "DISPLAY MENU:  \n  1)Customer/Product/Transaction        ";
       
    
}

int main(){
  showMainMenu();
  
}
  
