# LIBS=-lglut -lGLEW -lGL -lGLU
LIBS_OPENGL=-l:libGL.so -l:libGLEW.so -l:libglut.a -l:libGLU.a -lX11 -lXxf86vm -lXext -lXrandr -lXt -lXi -lm
LIBS_AUDIO=-lmpg123 -lao
LIBS=$(LIBS_OPENGL) $(LIBS_AUDIO)
CC=g++
FLAGS=-Wall -Wextra
PROGRAM=main
SRC=$(PROGRAM).cpp
AUDIO_FIFO=Audio/audio.fifo
AUDIO_LOG=Audio/audio.log

default:
	# yes, it works)
	$(CC) $(SRC) -o $(PROGRAM) $(FLAGS) $(LIBS)

run: default
	./$(PROGRAM)

debug: build-debug
	gdb ./$(PROGRAM)

build-debug:
	$(CC) $(SRC) -o $(PROGRAM) $(FLAGS) $(LIBS) -g

clear: clean
	# you should use 'make clean' but it's okey too

clean:
	rm ./$(PROGRAM)
	# be carefull with this guy:)
	rm -f $(AUDIO_FIFO) $(AUDIO_LOG)
