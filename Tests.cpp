#include <iostream>
#include "DatabaseManager.h"
#include "Lexer.h"

int main(){

  Lexer l;

  while(true){
    l.getString();
  }






  /*
  stringstream x("asdfasdfasfd asdf sadf asd as dsss");
  //l.buffer = x;
  l.getToken();*/




  /*while(true){
    stringstream addToBuffer;
    cout << "Enter a command: ";
    while(addToBuffer << cin){
    }
    l.buffer << addToBuffer.str();
    cout << "\n\n";
    l.getToken();
  }*?






  /*DatabaseManager myDBM;

  const char* attrNames[] = {"Class Name", "Days"};

  const char* classNames[] = {"Programming", "Kinesiology", "Math", "Science", "History"};
  const char* days[] = {"MWF", "MWF", "TR", "MWF", "TR"};

  vector<Attribute> attributes;

  for(int i = 0; i < 2; i++){
    attributes.push_back(Attribute(string() + attrNames[i]));
  }

  vector<Attribute*> keys;
  keys.push_back(&attributes[0]);

  myDBM.createTable("Classes", attributes, keys);

  for(int i = 0; i < 5; i++){
    vector<string> vals;

    vals.push_back(string() + classNames[i]);
    vals.push_back(string() + days[i]);

    cout << "Inserting into classes: (" << vals[0] << ", " << vals[1] << ")\n";

    myDBM.insertInto("Classes", vals);
  }

  cout << "\n\nShow() classes...\n\n";

  myDBM.show("Classes");


  cout << "\n\nRenaming() the attributes of Classes...\n\n";

  vector<string> newNames;
  newNames.push_back("Class Title");
  newNames.push_back("Days of the Week");
  myDBM.rename("Classes", newNames);

  cout << "\n\nShow() classes again...\n\n";

  myDBM.show("Classes");

  cout << "\n\nProject() classes days only...\n\n";

  vector<string> projectOnly;
  projectOnly.push_back("Days of the Week");
  myDBM.show(myDBM.project("Classes", projectOnly));


  cout << "\n\nSelect() classes only on TR...\n\n";
  myDBM.show(myDBM.select("Classes", "Days of the Week", "==", "TR"));*/

}
