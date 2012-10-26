
CC = gcc
CFLAGS= -DH5_USE_16_API -O2

OBJECTS = get_treeInfo.o get_nodeData.o create_galacticusFile.o write_nodeData.o write_treeData.o write_attributes.o read_param.o main.o
TARGET = convert
LIBS =  -lm -lhdf5 
INCLUDES = tree.h node.h parameter.h

$(TARGET): $(OBJECTS) 
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET) $(LIBS)

$(OBJECTS) : $(INCLUDES) Makefile

.PHONY: clean
clean:
	rm -rf *.o $(TARGET)
