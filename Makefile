ALL: ANOTACAO
	gcc -o main main.c -lmysqlclient anotacao.o
ANOTACAO: 
	gcc -c anotacao.c
clean:
	rm *.o
	rm *.bin
