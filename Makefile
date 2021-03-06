.PHONY: run clean conris install distclean uninstall

prefix= /usr/local
macros= -DGCONFG

objects= src/main.c src/controls.c src/vector2d.c src/tetro.c src/score.c \
		 src/field.c src/queue.c src/readSingelChar.c src/configReader.c src/ghostTetro.c
		 
output= conris

conris: $(objects)
	gcc $(macros) -g -ansi -pedantic -Wall $(objects) -lpthread -lcurses -o $(output)

run: conris
	./conris
	
debug: conris
	-valgrind --leak-check=full --track-origins=yes ./$(output)

install: conris
	install -D conris $(DESTDIR)$(prefix)/bin/conris

distclean: clean

uninstall:
	-rm -f $(DESTDIR)$(prefix)/bin/conris

clean:
	-rm -f $(output)
