expression.o: expression.h
clisp.o: expression.o sp.h

LDFLAGS=-lstdc++

clisp: expression.o clisp.o
