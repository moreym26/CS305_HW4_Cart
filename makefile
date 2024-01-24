#define the compiler-executable path
COMPILE_SWITCHES = -g
COMPILE = gcc $(COMPILE_SWITCHES)
OFILES = cart.o tree.o retail_item.o main.o

run: $(OFILES)
	$(COMPILE) -o run $(OFILES)

cart.o: cart.c cart.h retail_item.h
	$(COMPILE) -c cart.c

retail_item.o: retail_item.c retail_item.h
	$(COMPILE) -c retail_item.c

main.o: main.c retail_item.h cart.h tree.h
	$(COMPILE) -c main.c
tree.o: tree.c tree.h retail_item.h cart.h
	$(COMPILE) -c tree.c


# this defines the command for cleaning up
# all generated files
clean:
	/bin/rm -f *.o run
