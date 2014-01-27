RXE - Random XOR Encryption
===

Currently under Construction!!

:TEMPORARY:
Algorithm works like this: (pseudo code)

Seed = HashCode(Password)
SeedRandomGenerator(Seed)
Data[] = readFileToEnd(inputfile)
OutputData[] = AllocateMemory(inputfile.size)
for (index++) OutputData[index] = Data[index] xor GetRandomNumber()