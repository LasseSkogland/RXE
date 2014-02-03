RXE - Random XOR Encryption
===

Usage: rxe -i INPUT_FILE [-o OUTPUT_FILE] [-p PASSWORD] [-b BUFFER_SIZE]
  -i, --input-file=INPUT_FILE Set Input File
  -o, --output-file=OUTPUT_FILE Set Output File
  -p, --password=PASSWORD Set Encryption Password
  -b, --buffer-size=BUFFER_SIZE Set Buffer Size

Algorithm works like this: (pseudo code)
```C
Seed = HashCode(Password);
SeedRandomGenerator(Seed);
Data[] = readFileToEnd(inputfile);
OutputData[] = AllocateMemory(inputfile.size);
for (index++) OutputData[index] = Data[index] xor GetRandomNumber();
```
