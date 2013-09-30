# makefile

all: dbms

dbms: main.cpp System.cpp System.h Relation.cpp Relation.h Database.cpp Database.h Attribute.h Attribute.cpp DatabaseManager.cpp DatabaseManager.h Token.cpp Token.h Lexer.cpp Lexer.h Parser.cpp Parser.h
	g++ -ggdb -o dbms main.cpp System.cpp System.h Relation.cpp Relation.h Database.cpp Database.h Attribute.h Attribute.cpp DatabaseManager.cpp DatabaseManager.h Token.cpp Token.h Lexer.cpp Lexer.h Parser.cpp Parser.h
