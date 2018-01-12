paint.out: main.o commandPrompt.o drawCommand.o adjust.o file.o
	gcc -g -Wall -o paint.out main.o commandPrompt.o drawCommand.o adjust.o file.o

main.o: main.c commandPrompt.h drawCommand.h adjust.h file.h
	gcc -g -Wall -c -o main.o main.c

commandPrompt.o: commandPrompt.c commandPrompt.h 
	gcc -g -Wall -c -o commandPrompt.o commandPrompt.c

drawCommand.o: drawCommand.c drawCommand.h
	gcc -g -Wall -c -lm -o drawCommand.o drawCommand.c

adjust.o: adjust.c adjust.h
	gcc -g -Wall -c -o adjust.o adjust.c

file.o: file.c file.h
	gcc -g -Wall -c -o file.o file.c


clean:
	rm -f *.o *.out