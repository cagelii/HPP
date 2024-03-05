all: serial multi

serial:serial.c
	gcc -pthread serial.c -o serial

multi:multi.c
	gcc -pthread multi.c -o multi

clean:
	rm -f serial multi