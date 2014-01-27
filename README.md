RXE - Random XOR Encryption
===

Currently under Construction!!

:TEMPORARY:<br>
Algorithm works like this: (pseudo code)

Seed = HashCode(Password)<br >
SeedRandomGenerator(Seed)<br>
Data[] = readFileToEnd(inputfile)<br>
OutputData[] = AllocateMemory(inputfile.size)<br>
for (index++) OutputData[index] = Data[index] xor GetRandomNumber()<br>
