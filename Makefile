LDFLAGS=-lstdc++

clisp: expression.o clisp.o

.PHONY: clean
clean:
	$(RM) clisp *.o

expression.o: expression.h

clisp.o: expression.o sp.h
