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
  else if(line[0] == '('){
    current += line[0];
    line.erase(line.begin());
    addToken();
  }
  else if(line[0] == ')'){

    addToken();
    current += line[0];
    line.erase(line.begin());
    addToken();
  }
  else if(line[0] == '"'){
    current += line[0];
    line.erase(line.begin());
    addToken();
  }
  
  else{
    //current.append(line[0]);
    current += line[0];
    line.erase(line.begin());
    //cout<<"current == " + current + "\nline == " + line + "\n\n";
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
