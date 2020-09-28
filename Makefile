DEBUG = -g

ppmcvt: ppmcvt.o pbm.o
	gcc $(DEBUG) -o ppmcvt ppmcvt.o pbm.o

pbm.o: pbm.h pbm.c
	gcc $(DEBUG) -c pbm.c

ppmcvt.o: ppmcvt.c pbm.c pbm.h
	gcc $(DEBUG) -c ppmcvt.c

clean:
	rm ppmcvt.o pbm.o ppmcvt
