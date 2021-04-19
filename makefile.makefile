
SDL = -ldl `sdl2-config --libs`
LDFLAGS = $(SDL) -lSDL2 -lSDL2_image -lSDL2_ttf -lm -lSDL2_mixer


ChessProject: echiquier.o chess.o $(LDFLAGS) -o ChessProject:


echiquier.o: src/echiquier.c
	gcc -o echiquier.o -Wall src/echiquier.c -c `sdl2-config --cflags`

chess.o: SDL/Angel-Bastien/chess.c
	gcc -o chess.o -Wall SDL/Angel-Bastien/chess.c -c `sdl2-config --cflags`


clean:
	-rm *.o
	-rm ChessProject:
	@echo "Cleanup complete!"
