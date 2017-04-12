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
	#./$(PROJ_NAME) assign3/single.0
	#./$(PROJ_NAME) assign3/two.0
	#./$(PROJ_NAME) assign3/unweighted.0
	#./$(PROJ_NAME) assign3/g6.0
	#./$(PROJ_NAME) assign3/g7.0
	#./$(PROJ_NAME) assign3/g8.0
	#./$(PROJ_NAME) assign3/g9.0
	#./$(PROJ_NAME) assign3/g10.0
	#./$(PROJ_NAME) assign3/g11.0
	#./$(PROJ_NAME) assign3/g12.0
	#./$(PROJ_NAME) assign3/g13.0
	#./$(PROJ_NAME) assign3/g14.0
	#./$(PROJ_NAME) assign3/g15.0
	#./$(PROJ_NAME) assign3/g16.0
	#./$(PROJ_NAME) assign3/g17.0
	./dartest
	./dtest 50 19 0
	./bintest
	./btest 50 18 0
	#Testing against existing files
	@echo Testing Sequence complete.

clean :
	rm $(OBJS) $(PROJ_NAME) bintest dartest
