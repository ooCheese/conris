.PHONY: run clean

objects= src/conris.c src/vector2d.c src/tetro.c src/score.c \
		 src/field.c src/queue.c src/readSingelChar.c src/configReader.c
		 
output= conris

conris: $(objects)
	gcc -g -ansi -pedantic -Wall $(objects) -lpthread -lcurses -o $(output)

run: conris
	./conris
	
debug:
	-valgrind --leak-check=full --track-origins=yes ./$(output)


clean:
	rm $(output)
