RXE - Random XOR Encryption
===

<h5>Experimental Features:</h5>
```

```


This is a file encryptor that uses XOR mixed with a PRNG.<br>
This program is tested with 1GB files, and using MD5 to verify.<br>

<b>100mb file: RXE x 2 (Encrypt then decrypt) MD5 PASS!<br>
1024mb(1GB) file: RXE x 2 (Encrypt then decrypt) MD5 PASS!<br></b>

Both files were generated with a Random Byte Generator,<br>
which gives an output like this: (rn!GL(1}$5#gH7Z8KQ{Jrzul)N8QnsP<br>

Comparison XOR vs Random XOR:
```
{} means ascii code
Password is "pass"
String to encrypt is "aaaaaaaa"

Normal XOR: 1{0}221{0}22

Random XOR: jZ™{18}{21}”“¢
```
Usage:
```
Usage: rxe -i INPUT_FILE [-o OUTPUT_FILE] [-p PASSWORD] [-b BUFFER_SIZE]
  -i, --input-file=INPUT_FILE Set Input File
  -o, --output-file=OUTPUT_FILE Set Output File
  -p, --password=PASSWORD Set Encryption Password
  -b, --buffer-size=BUFFER_SIZE Set Buffer Size
```
Algorithm works like this: (pseudo code)
```C
Seed = HashCode(Password);
SeedRandomGenerator(Seed);
Data[] = readFileToEnd(inputfile);
OutputData[] = AllocateMemory(inputfile.size);
for (index++) OutputData[index] = Data[index] xor GetRandomNumber();
```
