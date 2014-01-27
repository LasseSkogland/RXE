#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

#define debug(MSG) printf("%s\n", MSG)

char *RXE(char *file, char *key) {
	// Open input file
	FILE *f;
	f = fopen(file, "rb");
	
	// Setup variables for reading
	int c, i = 0, read = 0, fsize = 0;
	
	// Get size of file
	fseek(f, 0L, SEEK_END);
	fsize = ftell(f);
	printf("Size: %i bytes\n", fsize);
	rewind(f);
	
	// Allocate input and output buffers
	char *data = calloc(fsize + 1, sizeof(char)), *outdata = calloc(fsize + 1, sizeof(char));
	
	// Read file to memory
	read = fread(data, sizeof(char), fsize, f);
	
	// Close file
	fclose(f);
	
	// Compare FileSize(fSize) to bytes read(read) 
	if(fsize == read) {
	
		// Generate key/seed from password
		int tkey = 0;
		i = 0, read = 0;
		while(i < strlen(key)){
			tkey += (int)key[i++];
		}
		
		// Seed random generator
		srand(tkey);
		
		i = 0;
		// Open file
		f = fopen(file, "wb");
		
		/*
		 * This is where the magic happens!
		 * Algorithm works like this: (pseudo code)
		 *
		 * Seed = HashCode(Password)
		 * SeedRandomGenerator(Seed)
		 * Data[] = readFileToEnd(inputfile)
		 * OutputData[] = AllocateMemory(inputfile.size)
		 * for (index++) OutputData[index] = Data[index] xor GetRandomNumber()
		 * 
		 */
		for(i = 0; i < fsize; i++) outdata[i] = data[i] ^ rand();
		
		// Write data to original file, this writes over previous data(Be careful!!!) 
		fwrite(outdata, sizeof(char), fsize, f);
		
		// Close File
		fclose(f);
		
	} else printf("Failed to read file...\n");
	// Free buffers
	free(data);
	free(outdata);
	
}

void main(int argc, char **argv){
	if(argc == 3) {
		RXE(argv[1], argv[2]);
	}else if(argc == 2) {
		RXE(argv[1], "default");
	}else{
		debug("RXE 0.3");
		debug("Usage: ");
		debug("rxe <INPUTFILE> (PASSWORD)");
		debug("Password is optional, it defaults to \"default\"");
	}
}