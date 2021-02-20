CXX=g++
CXXFLAGS=-g -ggdb -O2 -Wall

TARGET=mpasi
OBJS=lexical/SymbolTable.o \
		lexical/LexicalAnalysis.o \
		syntatic/SyntaticAnalysis.o \
		mpasi.o

all: $(TARGET)

clean:
	rm -rf $(TARGET) $(OBJS)

install:
	cp $(TARGET) /usr/local/bin

mpasi.o:

$(TARGET): $(OBJS)
					 $(CXX) -o $(TARGET) $(OBJS)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<