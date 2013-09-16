# makefile

all: dbms

dbms: Tests.cpp Relation.cpp Relation.h Database.cpp Database.h Attribute.h Attribute.cpp DatabaseManager.cpp DatabaseManager.h Token.cpp Token.h Lexer.cpp Lexer.h Parser.cpp Parser.h
	g++ -o dbms Tests.cpp Relation.cpp Relation.h Database.cpp Database.h Attribute.h Attribute.cpp DatabaseManager.cpp DatabaseManager.h Token.cpp Token.h Lexer.cpp Lexer.h Parser.cpp Parser.h
