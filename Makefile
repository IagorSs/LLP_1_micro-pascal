CXX=g++
CXXFLAGS=-g -ggdb -O2 -Wall

TARGET=mpasi
OBJS=lexical/SymbolTable.o \
		lexical/LexicalAnalysis.o \
		\
		syntatic/SyntaticAnalysis.o \
		\
		interpreter/value/IntegerValue/IntegerValue.o \
		interpreter/value/RealValue/RealValue.o \
		interpreter/value/StringValue/StringValue.o \
		\
		interpreter/expression/Expr/BinaryExpr/BinaryExpr.o \
		interpreter/expression/Expr/ConstExpr/ConstExpr.o \
		interpreter/expression/Expr/Variable/Variable.o \
		interpreter/expression/BoolExpr/CompositeBoolExpr/CompositeBoolExpr.o \
		interpreter/expression/BoolExpr/NotBoolExpr/NotBoolExpr.o \
		interpreter/expression/BoolExpr/SingleBoolExpr/SingleBoolExpr.o \
		\
		interpreter/command/AssignCommand/AssignCommand.o \
		interpreter/command/BlocksCommand/BlocksCommand.o \
		interpreter/command/CaseCommand/CaseCommand.o \
		interpreter/command/CaseCommand/CaseOption/CaseOption.o \
		interpreter/command/ForCommand/ForCommand.o \
		interpreter/command/IfCommand/IfCommand.o \
		interpreter/command/ReadCommand/ReadCommand.o \
		interpreter/command/RepeatCommand/RepeatCommand.o \
		interpreter/command/WhileCommand/WhileCommand.o \
		interpreter/command/WriteCommand/WriteCommand.o \
		\
		util/Memory.o \
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