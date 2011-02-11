LDFLAGS=-lstdc++

clisp: expression.o number.o application.o clisp.o

.PHONY: clean
clean:
	$(RM) clisp *.o

clisp.o: sp.h expression.h application.h number.h

expression.o: expression.h

number.o: expression.h number.h

application.o: expression.h application.h
