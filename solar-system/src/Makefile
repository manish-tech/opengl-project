#-*- MakeFile -*-

output: main.o displayIntro.o drawText.o drawLine.o
	gcc -o output main.o displayIntro.o drawText.o drawLine.o -lGL -lGLU -lglut

main.o: ./main.c 
	gcc -c ./main.c -lGL -lGLU -lglut

displayIntro.o: ./lib/displayIntro.c 
	gcc -c ./lib/displayIntro.c -lGL -lGLU -lglut

drawText.o: ./lib/drawText.c
	gcc -c ./lib/drawText.c -lGL -lGLU -lglut

drawLine.o: ./lib/drawLine.c
	gcc -c ./lib/drawLine.c -lGL -lGLU -lglut