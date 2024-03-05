all: enumsort enumsortM

enumsort: enumsort.c
	gcc -Wall -O3 -o enumsort enumsort.c -lpthread

enumsortM: enumsortM.c
	gcc -Wall -O3 -o enumsortM enumsortM.c -lpthread

clean:
	rm -f enumsort enumsortM
