#CentOs makefile

#Game specific settings
GAME = asteroids

SRC = $(wildcard *.cpp) \
	../../common/core.cpp ../../common/core_glfw.cpp \
	../../common/Vector2f.cpp ../../common/math.cpp

TARGET = $(GAME)

CFLAGS = -pthread 
LFLAGS = -L/usr/local/lib -lXrandr -lrt -lX11 -lGL -lm -lGLU  -lGL -pthread -lm -lglfw

default: run

$(TARGET): ${SRC}
	g++ ${CFLAGS} ${SRC} ${LFLAGS} -o $(TARGET)

run: $(TARGET)
	./$(TARGET)
clean:
	rm -f $(TARGET) *.o *.~ *.bak deps.mak
	
