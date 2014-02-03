#include <stdlib.h>
#include <stdio.h>
#include <argtable2.h>

#define println(MSG) printf("%s\n", MSG)
long seed = 0L;
int BUFFER_SIZE = 8196;

long unsigned int RXE_rand() {
	long unsigned int hi, lo;
	lo = 16807 * (seed & 0xFFFF);
	hi = 16807 * (seed >> 16);
	
	lo += (hi & 0x7FFF) << 16;
	lo += hi >> 15;
	lo = (lo & 0x7FFFFFFF) + (lo >> 31);
	return (seed = (long)lo);
}

void RXE_Crypt(char *indata, char *outdata, int size) {
	int i = 0;
	for(i = 0; i < size; i++) outdata[i] = indata[i] ^ RXE_rand();
}

void RXE_Init(char *key) {
	long i = 0;
	int klen = __builtin_strlen(key);
	while(i < klen){
		seed += (long)(key[i++] * key[(klen -1) - i]);
	}
}

void main(int argc, char *argv[]){
	struct arg_file *ifile = arg_file1("i", "input-file", "INPUT_FILE", "Set Input File");
	struct arg_file *ofile = arg_file0("o", "output-file", "OUTPUT_FILE", "Set Output File");
	struct arg_str *pass = arg_str0("p", "password", "PASSWORD","Set Encryption Password");
	struct arg_int *buf = arg_int0("b", "buffer-size", "BUFFER_SIZE","Set Buffer Size");
	struct arg_end *end = arg_end(20);
	void *argtable[] = {ifile, ofile, pass, buf, end};
	int nerrors = arg_parse(argc, argv, argtable);
	
	if (nerrors > 0) {
		arg_print_errors(stdout, end, "rxe");
		printf("\nUsage: rxe");
		arg_print_syntax(stdout, argtable, "\n");
		arg_print_glossary(stdout, argtable, "  %-10s %s\n");
	} else {
		if(pass->count > 0) RXE_Init((char *)pass->sval[0]);
		else RXE_Init("DEFAULT");
		if (buf->count > 0) {
			BUFFER_SIZE = buf->ival[0];
		}
		FILE *outfile, *infile = fopen(ifile->filename[0], "rb");
		if (ofile->count > 0) outfile = fopen(ofile->filename[0], "wb");
		else {
			char farr[2048];
			__builtin_strcpy(farr, ifile->filename[0]);
			__builtin_strcat(farr, ".rxe");
			outfile = fopen(farr, "wb");
		}
		int size;
		fseek(infile, 0L, SEEK_END);
		size = ftell(infile);
		rewind(infile);
		int itmp = 0, otmp = 0;
		char *outdata, *indata = calloc(BUFFER_SIZE, sizeof(char));
		outdata = calloc(BUFFER_SIZE, sizeof(char));
		while(size > 0) {
			if (size >= BUFFER_SIZE) {
				itmp = fread(indata, sizeof(char), BUFFER_SIZE, infile);
				printf("R/W: %i/", itmp);
				RXE_Crypt(indata, outdata, BUFFER_SIZE);
				otmp = fwrite(outdata, sizeof(char), BUFFER_SIZE, outfile);
				printf("%i\n", otmp);
				size -= BUFFER_SIZE;
			} else {
				itmp = fread(indata, sizeof(char), size, infile);
				printf("R/W: %i/", itmp);
				RXE_Crypt(indata, outdata, size);
				otmp = fwrite(outdata, sizeof(char), size, outfile);
				printf("%i\n", otmp);
				size = 0;
			}
			
		}
		fclose(outfile);
		fclose(infile);
	}
}