CC=@gcc
CFLAGS=-c -w

all: rxe
	@echo Linking Executable
	$(CC) -Ofast -s -o RXE src/*.o src/argtable2/*.o -lopencl -DOPENCL
	@rm src/*.o src/argtable2/*.o

rxe: argtable
	@echo Compiling RXE
	$(CC) $(CFLAGS) src/RXE.c -o src/RXE.o

argtable: 
	@echo Compiling Argtable2
	$(CC) $(CFLAGS) src/argtable2/arg_dbl.c -o src/argtable2/arg_dbl.o
	$(CC) $(CFLAGS) src/argtable2/arg_end.c -o src/argtable2/arg_end.o
	$(CC) $(CFLAGS) src/argtable2/arg_file.c -o src/argtable2/arg_file.o
	$(CC) $(CFLAGS) src/argtable2/arg_int.c -o src/argtable2/arg_int.o
	$(CC) $(CFLAGS) src/argtable2/arg_lit.c -o src/argtable2/arg_lit.o
	$(CC) $(CFLAGS) src/argtable2/arg_rem.c -o src/argtable2/arg_rem.o
	$(CC) $(CFLAGS) src/argtable2/arg_str.c -o src/argtable2/arg_str.o
	$(CC) $(CFLAGS) src/argtable2/argtable2.c -o src/argtable2/argtable.o