all: spinwait synch

spinwait: spinwait.c
	gcc -O3 spinwait.c -o spinwait

synch: synch.c
	gcc -o synch synch.c

clean:
	rm -f synch spinwait