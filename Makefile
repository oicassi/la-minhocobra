# -*- MakeFile -*-

all: lacobrafinal

lacobrafinal: lacobra.c
	clang -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL libraylib.a lacobra.c -o lacobrafinal

clean:
	rm lacobrafinal
