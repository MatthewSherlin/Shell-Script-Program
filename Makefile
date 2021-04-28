#Simple Makefile for 2 exersises
#Homework 5
#make run to create executable for function using ./[name]

run:
	gcc -o pipe pipeList.c

clean:  
	-rm $(objects)pipe

