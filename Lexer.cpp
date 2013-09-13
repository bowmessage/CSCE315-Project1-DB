#include "Lexer.h"

Lexer::Lexer(){
}

Lexer::~Lexer(){}

void Lexer::getString(){
  string line;
  cout<<"Please enter your command and press ENTER.\n";
  cin>>line;
  cout<<"\n";
  
  tokenize(line);
}

void Lexer::tokenize(string line){
  if(line.empty()){
    //Give todo to parser to do stuff.
  }
  
  else if(line[0] == ' '){
    addToken();
  }
  
  else{
    //current.append(line[0]);
    current += line[0];
    line.erase(line.begin());
    cout<<"current == " + current + "\nline == " + line + "\n\n";
    tokenize(line);
  }
}

void Lexer::addToken(){
  if(current == "INSERT"){
    todo.push_back(Token(Token::INSERT, current));
  }
  if(current == "DELETE"){
    todo.push_back(Token(Token::DELETE, current));
  }
  if(current == "CREATE"){
    todo.push_back(Token(Token::CREATE, current));
  }
  if(current == "INTO"){
    todo.push_back(Token(Token::INTO, current));
  }
  if(current == "FROM"){
    todo.push_back(Token(Token::FROM, current));
  }
  if(current == "TABLE"){
    todo.push_back(Token(Token::TABLE, current));
  }
  if(current == "UPDATE"){
    todo.push_back(Token(Token::UPDATE, current));
  }
  if(current == "SHOW"){
    todo.push_back(Token(Token::SHOW, current));
  }
  if(current == "OPEN"){
    todo.push_back(Token(Token::OPEN, current));
  }
  if(current == "CLOSE"){
    todo.push_back(Token(Token::CLOSE, current));
  }
  if(current == "WRITE"){
    todo.push_back(Token(Token::WRITE, current));
  }
  if(current == "EXIT"){
    todo.push_back(Token(Token::EXIT, current));
  }
  if(current == "SELECT"){
    todo.push_back(Token(Token::SELECT, current));
  }
  if(current == "PROJECT"){
    todo.push_back(Token(Token::PROJECT, current));
  }
  if(current == "RENAME"){
    todo.push_back(Token(Token::RENAME, current));
  }
  if(current == "SET"){
    todo.push_back(Token(Token::SET, current));
  }
  if(current == "CROSS"){
    todo.push_back(Token(Token::CROSS, current));
  }
  if(current == "UNION"){
    todo.push_back(Token(Token::UNION, current));
  }
  if(current == "WRITE"){
    todo.push_back(Token(Token::WRITE, current));
  }
  if(current == "DIFFERENCE"){
    todo.push_back(Token(Token::DIFFERENCE, current));
  }
  if(current == "PRODUCT"){
    todo.push_back(Token(Token::PRODUCT, current));
  }
  if(current == "LEFTPAREN"){
    todo.push_back(Token(Token::LEFTPAREN, current));
  }
  if(current == "RIGHTPAREN"){
    todo.push_back(Token(Token::RIGHTPAREN, current));
  }
  if(current == "QUOTE"){
    todo.push_back(Token(Token::QUOTE, current));
  }
  if(current == "LITERAL"){
    todo.push_back(Token(Token::QUOTE, current));
  }
}
