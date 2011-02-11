LDFLAGS=-lstdc++

clisp: expression.o number.o clisp.o

.PHONY: clean
clean:
	$(RM) clisp *.o

clisp.o: sp.h expression.h number.h

expression.o: expression.h

number.o: number.h