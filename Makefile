CC=gcc
CFLAGS=-g -Wall 
DEPS = mymalloc.h
OBJ = mymalloc.c test.c

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

test: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f $(ODIR)/*.o *~ test $(INCDIR)/*~ 
