CFLAGS = -std=c99 -g -Wall -Wshadow --pedantic -Wvla -Werror
GCC = gcc $(CFLAGS)
EXEC = gradeCalc
OBJS = main.o grade.o
HDRS = grade.h
VALGRIND = valgrind --tool=memcheck --leak-check=yes --verbose

$(EXEC): $(OBJS) $(HDRS)
	$(GCC) $(OBJS) -o $(EXEC)

# creates executable
all: $(OBJS) $(HDRS)
	$(GCC) $(OBJS) -o $(EXEC)

# run to build spreadsheet
build: $(EXEC)
	./$(EXEC) yourGradingSheet.csv

%.o : %.c
	$(GCC) -c $< 

clean:
	/bin/rm -f *.o
	/bin/rm -f $(EXEC)
	/bin/rm -f $(OUTFILES)
	/bin/rm -f log?
