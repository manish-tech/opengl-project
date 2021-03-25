#-*- MakeFile -*-

output: main.o displayIntro.o drawText.o drawShape.o displaySolarSystem.o
	gcc -o output main.o displayIntro.o drawText.o drawShape.o displaySolarSystem.o -lGL -lGLU -lglut

main.o: ./main.c 
	gcc -c ./main.c -lGL -lGLU -lglut

displayIntro.o: ./lib/displayIntro.c 
	gcc -c ./lib/displayIntro.c -lGL -lGLU -lglut

drawText.o: ./lib/drawText.c
	gcc -c ./lib/drawText.c -lGL -lGLU -lglut

drawShape.o: ./lib/drawShape.c
	gcc -c ./lib/drawShape.c -lGL -lGLU -lglut

displaySolarSystem.o: ./lib/displaySolarSystem.c
	gcc -c ./lib/displaySolarSystem.c -lGL -lGLU -lglut