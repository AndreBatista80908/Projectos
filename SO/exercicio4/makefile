all: i-banco i-banco-terminal

i-banco: commandlinereader.o contas.o i-banco.o
	gcc -pthread -o i-banco commandlinereader.o contas.o i-banco.o

i-banco-terminal: i-banco-terminal.o
	gcc -pthread -o i-banco-terminal commandlinereader.o i-banco-terminal.o

commandlinereader.o: commandlinereader.c commandlinereader.h
	gcc -pthread -g -Wall -pedantic -c commandlinereader.c

contas.o: contas.c contas.h
	gcc -pthread -g -Wall -pedantic -c contas.c

i-banco.o: i-banco.c
	gcc -pthread -g -Wall -pedantic -c i-banco.c

i-banco-terminal.o: i-banco-terminal.c
	gcc -pthread -g -Wall -pedantic -c i-banco-terminal.c

clean:
	rm -f i-banco *.o
