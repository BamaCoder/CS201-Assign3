PROJ_NAME = dijkstra

OBJS = scanner.o integer.o queue.o sll.o darray.o binomial.o comparator.o
FLAGS = -std=c99 -Wall -Wextra -g



$(PROJ_NAME): $(PROJ_NAME).c $(OBJS)
	gcc $(FLAGS) -o $(PROJ_NAME) $(PROJ_NAME).c $(OBJS)

%.o : %.c
	gcc $(FLAGS) -c $<

test : $(PROJ_NAME)
	gcc $(FLAGS) -o dartest testdarray.c $(OBJS)
	gcc $(FLAGS) -o dtest dtest.c $(OBJS)
	gcc $(FLAGS) -o bintest binomialtest.c $(OBJS)
	gcc $(FLAGS) -o btest btest.c $(OBJS)
	./$(PROJ_NAME) single.0>mytest3.txt
	./$(PROJ_NAME) two.0>mytest4.txt
	./$(PROJ_NAME) unweighted.0>mytest5.txt
	./$(PROJ_NAME) g6.0>mytest6.txt
	./$(PROJ_NAME) g7.0>mytest7.txt
	./$(PROJ_NAME) g8.0>mytest8.txt
	./$(PROJ_NAME) g9.0>mytest9.txt
	./$(PROJ_NAME) g10.0>mytest10.txt
	./$(PROJ_NAME) g11.0>mytest11.txt
	./$(PROJ_NAME) g12.0>mytest12.txt
	./$(PROJ_NAME) g13.0>mytest13.txt
	./$(PROJ_NAME) g14.0>mytest14.txt
	./$(PROJ_NAME) g15.0>mytest15.txt
	./$(PROJ_NAME) g16.0>mytest16.txt
	./$(PROJ_NAME) g17.0>mytest17.txt
	./dartest
	./dtest 50 19 0
	./bintest
	./btest 50 18 0
	diff mytest3.txt expected.3
	diff mytest4.txt expected.4
	diff mytest5.txt expected.5
	diff mytest6.txt expected.6
	diff mytest7.txt expected.7
	diff mytest8.txt expected.8
	diff mytest9.txt expected.9
	diff mytest10.txt expected.10
	diff mytest11.txt expected.11
	diff mytest12.txt expected.12
	diff mytest13.txt expected.13
	diff mytest14.txt expected.14
	diff mytest15.txt expected.15
	diff mytest16.txt expected.16
	diff mytest17.txt expected.17
	#Testing against existing files
	@echo Testing Sequence complete.

clean :
	rm $(OBJS) $(PROJ_NAME) bintest dartest btest dtest *.txt
