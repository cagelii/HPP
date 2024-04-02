CC = gcc
LD = gcc
CFLAGS = -Wall -fopenmp -lm -O3
RM = /bin/rm -f
OBJS = galsim.o quadtree.o
TARGET = galsim

all:$(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(CFLAGS) 

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) *.gal $(TARGET)
