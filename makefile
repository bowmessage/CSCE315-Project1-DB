# makefile

all: dbms

dbms: Tests.cpp Entity.cpp Entity.h Relation.cpp Relation.h Database.cpp Database.h Attribute.h Attribute.cpp DatabaseManager.cpp DatabaseManager.h
	g++ -o dbms Tests.cpp Entity.cpp Entity.h Relation.cpp Relation.h Database.cpp Database.h Attribute.h Attribute.cpp DatabaseManager.cpp DatabaseManager.h
