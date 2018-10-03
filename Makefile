

#INC = -I/home2/amerson/anaconda2/include/ -I/usr/lib/openmpi/include/ -L/home2/amerson/anaconda2/lib/
INC = -I/home/abenson/Galacticus/Tools/include/ -I/usr/lib/openmpi/include/ -L/home/abenson/Galacticus/Tools/lib/


CC = gcc
CFLAGS= -DH5_USE_16_API -g $(INC)
CFLAGS+=-Wno-unused-result

OBJECTS = get_treeInfo.o get_nodeData.o create_galacticusFile.o write_nodeData.o write_treeData.o write_attributes.o read_param.o main.o
TARGET = convert.exe
LIBS =  -lm -lhdf5
INCLUDES = tree.h node.h parameter.h searchFunctions.h 

$(TARGET): $(OBJECTS) 
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET) $(LIBS)

$(OBJECTS) : $(INCLUDES) Makefile

.PHONY: clean
clean:
	rm -rf *.o $(TARGET)
