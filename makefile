CC = gcc
OBJ_NAME = main
OBJS = src/main.c src/init.c src/draw.c src/input.c src/stage.c src/util.c
LIBS = -lSDL2 -lSDL2_image
all:
	$(CC) -o $(OBJ_NAME) $(OBJS) $(LIBS)	
clean:
	rm -f $(OBJ_NAME)