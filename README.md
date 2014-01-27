RXE - Random XOR Encryption
===

Currently under Construction!!

:TEMPORARY:<br>
Algorithm works like this: (pseudo code)
```C
Seed = HashCode(Password);
SeedRandomGenerator(Seed);
Data[] = readFileToEnd(inputfile);
OutputData[] = AllocateMemory(inputfile.size);
for (index++) OutputData[index] = Data[index] xor GetRandomNumber();
```
