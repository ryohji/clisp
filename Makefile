LDFLAGS=-lstdc++

clisp: clisp.o expression.o number.o application.o symbol.o

.PHONY: clean
clean:
	$(RM) clisp *.o

clisp.o: sp.h expression.h application.h number.h symbol.h

expression.o: expression.h

number.o: expression.h number.h

symbol.o: expression.h symbol.h

application.o: expression.h application.h
