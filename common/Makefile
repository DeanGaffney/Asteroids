# Makefile to test common code

CPP = g++

CPPFLAGS = -c -g -O2 -Wall -Wextra -Wconversion -I../glfw/include -I/opt/local/include

LDLIBS   = -L/opt/X11/lib ../glfw/lib/cocoa/libglfw.a \
	-lm -lglut \
 	-framework Cocoa -framework OpenGL -framework IOKit
LFLAGS   =

default: test_Vector2f

test_Vector2f: test_Vector2f.o math.o Vector2f.o
	g++ $(LFLAGS) $^ $(LDLIBS) -o $@ 

test_Pool: test_Pool.o Pool.o math.o Vector2f.o
	g++ $(LFLAGS) $^ $(LDLIBS) -o $@ 

clean:
	rm -f *.o

