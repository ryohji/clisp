LDFLAGS=-lstdc++

clisp: clisp.o expression.o number.o application.o symbol.o list.o environment.o

.PHONY: clean
clean:
	$(RM) clisp *.o

.PHONY: all
all: clisp

clisp.o: sp.h expression.h application.h number.h symbol.h

expression.o: expression.h

number.o: expression.h number.h

symbol.o: expression.h environment.h symbol.h

list.o: expression.h environment.h list.h

application.o: expression.h application.h number.h list.h

environment.o: expression.h environment.h
