CC = g++
LIBS = -lX11 -lglut -lGL -lGLU -lGLEW -lm
SOURCES = $(wildcard  *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = lights
CFLAGS=-c -Wall -DDEBUG -g

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) -o $@ $(LIBS)

clean:
	rm -f $(EXECUTABLE) $(OBJECTS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
