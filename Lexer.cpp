#include "Lexer.h"
#include <iostream>

Lexer::Lexer(){
  p = Parser();
}

Lexer::~Lexer(){}

void Lexer::readFile(string filename){
  ifstream file(filename.c_str());
  string line;
  if (file.is_open())
  {
    while ( getline (file,line) )
    {
      tokenize(line);
    }
    file.close();
  }
  else cout << "Unable to open file"; 
}

void Lexer::getString(){
  string line;
  cout<<"Please enter your command and press ENTER.\n";
  /*char* tmp = new char[1000];
  cin.get( tmp, 1000);
  line = string(tmp);*/
  //cin >> line;
  getline(cin, line);
  cout<<"\n";
  
  tokenize(line);
}

void Lexer::tokenize(string line){
  bool keepTokenizing = true;
    cout<<"current == " + current + "\nline == " + line + "\n\n";
  if(line.empty()){
    addToken();
    keepTokenizing = false;
    vector<Token>* toPass = new vector<Token>(todo);
    cout << "toPass Size: " << toPass->size() << "\n";
    for(int i = 0; i < toPass->size(); i++){
      std::cout << toPass->at(i).value << "\n";
    }
    bool didParse = p.parse(toPass);
    if(didParse){
      cout << "Parsed successfully.\n";
    }
    else{
      cout << "Parse failed.\n";
    }
    todo.clear();
    //Give todo to parser to do stuff.
  }
  
  else if(line[0] == ' '){
	printf("Found a space.");
    addToken();
    line.erase(line.begin());
  }
  else if(line[0] == '('){
	  if(current != "") addToken();
    current += line[0];
    line.erase(line.begin());
    addToken();
  }
  else if(line[0] == ')'){

    addToken();
	printf("Current string is %s\n", current.c_str());
    current += line[0];
    line.erase(line.begin());
    addToken();
  }
  else if(line[0] == '"'){
	  if(current != "") addToken();
    current += line[0];
    line.erase(line.begin());
    addToken();
  }
  
  else{
    //current.append(line[0]);
    current += line[0];
    line.erase(line.begin());
  }
  if(keepTokenizing){
    tokenize(line);
  }
}

void Lexer::addToken(){
  if(current == "INSERT"){
    todo.push_back(Token(Token::INSERT, current));
  }
  else if(current == "DELETE"){
    todo.push_back(Token(Token::DELETE, current));
  }
  else if(current == "CREATE"){
    todo.push_back(Token(Token::CREATE, current));
  }
  else if(current == "INTO"){
    todo.push_back(Token(Token::INTO, current));
  }
  else if(current == "FROM"){
    todo.push_back(Token(Token::FROM, current));
  }
  else if(current == "TABLE"){
    todo.push_back(Token(Token::TABLE, current));
  }
  else if(current == "UPDATE"){
    todo.push_back(Token(Token::UPDATE, current));
  }
  else if(current == "SHOW"){
    todo.push_back(Token(Token::SHOW, current));
  }
  else if(current == "OPEN"){
    todo.push_back(Token(Token::OPEN, current));
  }
  else if(current == "CLOSE"){
    todo.push_back(Token(Token::CLOSE, current));
  }
  else if(current == "WRITE"){
    todo.push_back(Token(Token::WRITE, current));
  }
  else if(current == "EXIT"){
    todo.push_back(Token(Token::EXIT, current));
  }
  else if(current == "SELECT"){
    todo.push_back(Token(Token::SELECT, current));
  }
  else if(current == "PROJECT"){
    todo.push_back(Token(Token::PROJECT, current));
  }
  else if(current == "RENAME"){
    todo.push_back(Token(Token::RENAME, current));
  }
  else if(current == "SET"){
    todo.push_back(Token(Token::SET, current));
  }
  else if(current == "CROSS"){
    todo.push_back(Token(Token::CROSS, current));
  }
  else if(current == "UNION"){
    todo.push_back(Token(Token::UNION, current));
  }
  else if(current == "WRITE"){
    todo.push_back(Token(Token::WRITE, current));
  }
  else if(current == "DIFFERENCE"){
    todo.push_back(Token(Token::DIFFERENCE, current));
  }
  else if(current == "PRODUCT"){
    todo.push_back(Token(Token::PRODUCT, current));
  }
  else if(current == "("){
    todo.push_back(Token(Token::LEFTPAREN, current));
  }
  else if(current == ")"){
    todo.push_back(Token(Token::RIGHTPAREN, current));
  }
  else if(current == "\""){
    /*if (isalpha(line[0])) todo.push_back(Token(Token::OPENQUOTE, current));
    else todo.push_back(Token(Token::CLOSEQUOTE, current));*/
    todo.push_back(Token(Token::QUOTE, current ));
  }
  else {
    todo.push_back(Token(Token::LITERAL, current));
  }
  current = "";
}
