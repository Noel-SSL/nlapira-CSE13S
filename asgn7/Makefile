CFLAGS = -Wall -Werror -gdwarf-4

.PHONY: all clean

all: test_graph_1 test_stack_1 test_path_1 tsp

test_graph_1: test_graph_1.o graph.o
	$(CC) $(CFLAGS) -o $@ $^

test_stack_1: test_stack_1.o stack.o
	$(CC) $(CFLAGS) -o $@ $^

test_path_1: test_path_1.o graph.o stack.o path.o
	$(CC) $(CFLAGS) -o $@ $^

tsp: tsp.o graph.o stack.o path.o
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

clean: 
	rm -f *.o test_graph_1 test_stack_1 test_path_1 tsp