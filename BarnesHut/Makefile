CC = gcc
LD = gcc
CFLAGS = -Wall -fopenmp -lm -O3
INCLUDES = -I/opt/X11/include
RM = /bin/rm -f
OBJS = galsim.o quadtree.o graphics.o
TARGET = galsim

all:$(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(CFLAGS) -L/opt/X11/lib -lX11

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJS) *.gal *.png $(TARGET)
