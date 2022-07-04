# Rainbow attack

Ce repository contient le travail Rainbow attack de SECG4 labo.

## What the program can do
This program can generate a list of passwords and export them to a file.
The same is true for the respective hashed passwords.
You can then check if the hashes matches the passwords in both text files.
After that you can generate a Rainbow Table using these passwords.
Finally you can attack the hashes using the rainbow table.

## Build

### Dependency
qmake from qt Creator

### Build process
On a shell in the git root directory, type the command `make`

## Usage
The program is used with command line arguments:

**1)**
First you have to generate a list of passwords and their respective hashes.
To do so you can use the **"generate"** command.
Usage: RainBowAttack generate c mc MC of_pwd of_hash, where
              - generate is for passwords generation
              - c is the number of passwords to generate
              - mc is the minimum number of chars allowed in an alphanumeric password
              - MC is the maximum number of chars allowed in an alphanumeric password
              - of_pwd is the name of the output file where the passwords will be stored
              - of_hash is the name of the output file where the sha-256 hashes of the passwords will be stored
    Example: generate 100 6 8 D:\temp\pwd.txt D:\temp\hash.txt
    Will generate 100 passwords with a minimum and maximum lenght of 6 and 8 in pwd.txt located at D:\temp
    and will put all the hashed passwords in hash.txt

**2)**
If you want to check if the hashes and passwords matches, use the command **"check"**.
Usage : RainBowAttack check if_pwd if_hash, where
              - check is for passwords generation,
              - if_pwd is the name of the input file where the passwords are stored
              - if_hash is the name of the input file where the sha-256 hashes of the passwords are stored
    Example: check D:\temp\pwd.txt D:\temp\hash.txt

**3)**
Once you generated a list of passwords you can generate the Rainbow table.
To do so you can use the **"generateTable"** command.
Usage : RainBowAttack generateTable inFilePath outFilePath, where
              - generateTable is for rainbow table generation,
              - inFilePath is the name of the input file where the passwords are stored
              - outFilePath is the name of the output file where the rainbow table will be stored
    Example: generateTable D:\temp\pwd.txt D:\temp\rainbowTable.txt


**4)**
You are now ready to attack the hashes.
To do so you can use the **"attack"** command.
"Usage : RainBowAttack attack RainbowTableFilePath resultPath {fileHash/hash}, where
                - attack is to crack a given hash OR an entire file of hashes,
                - RainbowTableFilePath is the path where the rainbow table is located,
                - resultPath is the path where the result is stored,
                - fileHash or hash is a specific hash or list of hash that you would like to crack,
    Example 1) attack s D:\temp\rainbowTable.txt d736d2d1bf519dbfa3769e2704ed199bd009c6b5d8acd258cd5be96002b66f0d
    Will try to crack only the given hash using the rainbow table and print them.
    Example 1) attack a D:\temp\rainbowTable.txt D:\temp\hash.txt
    Will try to crack the entire list of hashes and print them.


## Auteurs
-**54024 Arno Pierre Pion**
-**54456 Damiano Deplano**
-**54193 Serena di Stefano**
-**54198 Aymane Elalami**
