# LIBS=-lglut -lGLEW -lGL -lGLU
LIBS_OPENGL=-l:libGL.so -l:libGLEW.so -l:libglut.a -l:libGLU.a -lX11 -lXxf86vm -lXext -lXrandr -lXt -lXi -lm
LIBS_AUDIO=-lmpg123 -lao
LIBS=$(LIBS_OPENGL) $(LIBS_AUDIO)
CC=g++
OPTIMISATION=-O2
FLAGS=-Wall -Wextra
PROGRAM=main
SRC=$(PROGRAM).cpp
CONFIG_SCALES_PROGRAM=genScaleInfo
CONFIG_SCALES_SRC=Config/GenScaleInfo/$(CONFIG_SCALES_PROGRAM).cpp
CONFIG_SCALES_AUTO_OPTION=auto
CONFIG_MODELS_PROGRAM=genModelInfo
CONFIG_MODELS_SRC=Config/GenModelInfo/$(CONFIG_MODELS_PROGRAM).cpp
CONFIG_MODELS_AUTO_OPTION=auto
AUDIO_FIFO=Audio/audio.fifo
AUDIO_LOG=Audio/audio.log

default: build-config
	# yes, it works)
	$(CC) $(SRC) -o $(PROGRAM) $(FLAGS) $(OPTIMISATION) $(LIBS)

build-unoptimized: build-config
	$(CC) $(SRC) -o $(PROGRAM) $(FLAGS) $(LIBS)

build-config:
	$(CC) $(CONFIG_SCALES_SRC) -o $(CONFIG_SCALES_PROGRAM) $(FLAGS)
	$(CC) $(CONFIG_MODELS_SRC) -o $(CONFIG_MODELS_PROGRAM) $(FLAGS)

run: default
	./$(PROGRAM)

debug: build-debug
	gdb ./$(PROGRAM)

build-debug:
	$(CC) $(SRC) -o $(PROGRAM) $(FLAGS) $(LIBS) -g
	$(CC) $(CONFIG_SCALES_SRC) -o $(CONFIG_SCALES_PROGRAM) $(FLAGS) -g

config-scales: $(CONFIG_SCALES_PROGRAM)
	./$(CONFIG_SCALES_PROGRAM)

config-models: $(CONFIG_MODELS_PROGRAM)
	./$(CONFIG_MODELS_PROGRAM)

auto-config: $(CONFIG_SCALES_PROGRAM) $(CONFIG_MODELS_PROGRAM)
	./$(CONFIG_SCALES_PROGRAM) $(CONFIG_SCALES_AUTO_OPTION)
	echo "\n\n"
	./$(CONFIG_MODELS_PROGRAM) $(CONFIG_MODELS_AUTO_OPTION)

clean:
	rm ./$(PROGRAM)
	# be carefull with this guy:)
	rm -f $(AUDIO_FIFO) $(AUDIO_LOG)
