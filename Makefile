CC=@gcc
CFLAGS=-c -w -Ofast -Isrc/
PRINT=@echo

AT_SRC=src/argtable2/
AT_OBJ=obj/argtable2/

all: obj/RXE.o libargtable2
	$(PRINT) Link: "libargtable2 RXE.o -> RXE"
	$(CC) -Ofast -s -o RXE obj/RXE.o $(AT_OBJ)*.o
	
libargtable2: $(AT_OBJ)arg_dbl.o $(AT_OBJ)arg_end.o $(AT_OBJ)arg_file.o $(AT_OBJ)arg_int.o $(AT_OBJ)arg_lit.o $(AT_OBJ)arg_rem.o $(AT_OBJ)arg_str.o $(AT_OBJ)argtable2.o
	
$(AT_OBJ)arg_dbl.o: $(AT_SRC)arg_dbl.c
	$(PRINT) Compile: "arg_dbl.c -> arg_dbl.o"
	$(CC) $(CFLAGS) $(AT_SRC)arg_dbl.c -o $(AT_OBJ)arg_dbl.o
	
$(AT_OBJ)arg_end.o: $(AT_SRC)arg_end.c
	$(PRINT) Compile: "arg_end.c -> arg_end.o"
	$(CC) $(CFLAGS) $(AT_SRC)arg_end.c -o $(AT_OBJ)arg_end.o
	
$(AT_OBJ)arg_file.o: $(AT_SRC)arg_file.c
	$(PRINT) Compile: "arg_file.c -> arg_file.o"
	$(CC) $(CFLAGS) $(AT_SRC)arg_file.c -o $(AT_OBJ)arg_file.o
	
$(AT_OBJ)arg_int.o: $(AT_SRC)arg_int.c
	$(PRINT) Compile: "arg_int.c -> arg_int.o"
	$(CC) $(CFLAGS) $(AT_SRC)arg_int.c -o $(AT_OBJ)arg_int.o
	
$(AT_OBJ)arg_lit.o: $(AT_SRC)arg_lit.c
	$(PRINT) Compile: "arg_lit.c -> arg_lit.o"
	$(CC) $(CFLAGS) $(AT_SRC)arg_lit.c -o $(AT_OBJ)arg_lit.o
	
$(AT_OBJ)arg_rem.o: $(AT_SRC)arg_rem.c
	$(PRINT) Compile: "arg_rem.c -> arg_rem.o"
	$(CC) $(CFLAGS) $(AT_SRC)arg_rem.c -o $(AT_OBJ)arg_rem.o
	
$(AT_OBJ)arg_str.o: $(AT_SRC)arg_str.c
	$(PRINT) Compile: "arg_str.c -> arg_str.o"
	$(CC) $(CFLAGS) $(AT_SRC)arg_str.c -o $(AT_OBJ)arg_str.o
	
$(AT_OBJ)argtable2.o: $(AT_SRC)argtable2.c
	$(PRINT) Compile: "argtable2.c -> argtable2.o"
	$(CC) $(CFLAGS) $(AT_SRC)argtable2.c -o $(AT_OBJ)argtable2.o
	
obj/RXE.o: src/RXE.c
	$(PRINT) Compile: "RXE.c -> RXE.o"
	$(CC) $(CFLAGS) src/RXE.c -o obj/RXE.o
	
clean:
	rm obj/*.o $(AT_OBJ)*.o
