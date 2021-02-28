CXX=g++
CXXFLAGS=-g -ggdb -O2 -Wall

TARGET=mpasi
OBJS=lexical/SymbolTable.o \
		lexical/LexicalAnalysis.o \
		syntatic/SyntaticAnalysis.o \
		interpreter/value/IntegerValue/IntegerValue.o \
		interpreter/value/RealValue/RealValue.o \
		interpreter/value/StringValue/StringValue.o \
		interpreter/expression/Expr/BinaryExpr/BinaryExpr.o \
		interpreter/expression/Expr/ConstExpr/ConstExpr.o \
		interpreter/expression/Expr/Variable/Variable.o \
		interpreter/expression/BoolExpr/CompositeBoolExpr/CompositeBoolExpr.o \
		interpreter/expression/BoolExpr/NotBoolExpr/NotBoolExpr.o \
		interpreter/expression/BoolExpr/SingleBoolExpr/SingleBoolExpr.o \
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