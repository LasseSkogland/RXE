#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "argtable2/argtable2.h"

//Define builtin GCC functions
#ifdef __GNUC__
#define malloc __builtin_malloc
#define strcat __builtin_strcat
#define strlen __builtin_strlen
#define strstr __builtin_strstr
#define strcpy __builtin_strcpy
#endif

#ifdef __linux__
#include <sys/types.h>
#define _off_t off_t
#endif

#define println(MSG) printf("%s\n", MSG)
#define RXE_rand() (seed = ((16807 * (seed & 0xFFFF)) + (((((16807 * (seed >> 16)) & 0x7FFF) << 16) + ((16807 * (seed >> 16)) >> 15)) & 0x7FFFFFFF)) + (16807 * (seed & 0xFFFF) + ((((16807 * (seed >> 16)) & 0x7FFF) << 16) + ((((16807 * (seed >> 16)) >> 15)) >> 31))))

unsigned int seed;
int i = 0;
int BUFFER_SIZE = 1024, PASSES = 1, PASS;
clock_t begin, end;

void RXE_Init(char *key) {
	seed = 0;
	long i = 0;
	long klen = strlen(key);
	while(i < klen) {
		seed = seed + (long)(key[i] * key[(klen -1) - i]);
		i++;
	}
}

void RXE_Main(FILE *in, FILE *out, char *pass) {
	RXE_Init(pass);
	begin = clock();
	long size, SIZE;
	fseek(in, 0L, SEEK_END);
	SIZE = size = ftell(in);
	printf("Size: %I32d\n", SIZE);
	if(SIZE == -1) {
		printf("Error: File is too large.\nMax FileSize: %.00fMb", pow(2, sizeof(_off_t) * 8) / 2097152);
		return;
	}
	rewind(in);
	if(SIZE < BUFFER_SIZE) BUFFER_SIZE = SIZE;
	char *outdata = malloc(BUFFER_SIZE * sizeof(char)), *indata = malloc(BUFFER_SIZE * sizeof(char));
	while(size > 0) {
		if (size >= BUFFER_SIZE) {
			fread(indata, sizeof(char), BUFFER_SIZE, in);
			for(PASS = 0; PASS < PASSES; PASS++) 
				for(i = 0; i < BUFFER_SIZE; i++)
					outdata[i] = indata[i] ^ RXE_rand();
			
			fwrite(outdata, sizeof(char), BUFFER_SIZE, out);
		} else {
			fread(indata, sizeof(char), size, in);
			for(PASS = 0; PASS < PASSES; PASS++) 
				for(i = 0; i < BUFFER_SIZE; i++) outdata[i] = indata[i] ^ RXE_rand();
			
			fwrite(outdata, sizeof(char), size, out);
		}
		if(size - BUFFER_SIZE < 0) size = 0;
		else size -= BUFFER_SIZE;

	}
	end = clock();
	printf("%fkb processed in %fs\n", ((double)SIZE / 1024.0), ((double)(end - begin) / CLOCKS_PER_SEC));
}

/*
 * All code below is "unimportant", it's only argument and file handling
 */
int main(int argc, char *argv[]) {
	struct arg_file *ifile = arg_file1("i", "input-file", "INPUT_FILE", "Set Input File");
	struct arg_file *ofile = arg_file0("o", "output-file", "OUTPUT_FILE", "Set Output File");
	struct arg_str *pass = arg_str0("p", "password", "PASSWORD", "Set Encryption Password");
	struct arg_int *pas = arg_int0("c", "passes", "PASSES", "Set number of passes (To decrypt you'll need the same number of passes)");
	struct arg_int *buf = arg_int0("b", "buffer-size", "BUFFER_SIZE", "Set Buffer Size");
	struct arg_end *end = arg_end(20);
	void *argtable[] = {
	ifile, ofile, pass, pas, buf, end};
	int nerrors = arg_parse(argc, argv, argtable);
	
	if (nerrors > 0) {
		arg_print_errors(stdout, end, "rxe");
		printf("\nUsage: rxe");
		arg_print_syntax(stdout, argtable, "\n");
		arg_print_glossary(stdout, argtable, "  %-10s %s\n");
	} else {
		if (buf->count > 0) {
			BUFFER_SIZE = buf->ival[0];
		}
		FILE *outfile, *infile = fopen(ifile->filename[0], "rb");
		if (ofile->count > 0) outfile = fopen(ofile->filename[0], "wb");
		else {
			char farr[2048];
			char *ptr;
			strcpy(farr, ifile->filename[0]);
			if ((ptr = strstr(farr, ".rxe")) != NULL) {
				farr[0] = '\0';
				farr[1] = '\0';
				farr[2] = '\0';
				farr[3] = '\0';
			} else strcat(farr, ".rxe");
			outfile = fopen(farr, "wb");
		}
		if(pas->count > 0) PASSES = pas->ival[0];
		if(pass->count > 0) RXE_Main(infile, outfile, (char *)pass->sval[0]);
		else RXE_Main(infile, outfile, "DEFAULT");
		fclose(outfile);
		fclose(infile);
	}
	return 0;
}
