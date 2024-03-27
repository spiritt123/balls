CC=g++
CFLAGS=-c
LDFLAGS=
SOURCES=main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=client

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ -DSFML_STATIC \
	-Iinclude -Llib -pthread -lsfml-graphics -lsfml-system -lsfml-window -lsfml-network -lstdc++

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clear:
	rm -f *.o $(EXECUTABLE)
