# -*- MakeFile -*-

all: lacobrita

lacobrita: lacobra.o
	gcc lacobra.o -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o lacobrita

lacobra.o: lacobra.c
	gcc -c lacobra.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
	echo 'tudo criado'

clean:
	rm *.o lacobrita
