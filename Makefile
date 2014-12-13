CC=gcc
CFLAGS=-g -Wall 
DEPS = mymalloc.h
OBJ = mymalloc.c

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

test: $(OBJ) test.c
	$(CC) -o $@ $^ $(CFLAGS)
	
bugtest: $(OBJ) bugtest.c
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f $(ODIR)/*.o *~ test bugtest $(INCDIR)/*~ 
