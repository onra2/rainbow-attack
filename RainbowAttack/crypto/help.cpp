#include "help.h"

namespace crypto {

help::help()
{

}

void help::displayPasswordGenerationHelp(){
    std::cout << "Usage : \"RainBowAttack generate c mc MC of_pwd of_hash\", where" << std::endl
              << "- generate is for passwords generation," << std::endl
              << "- c is the number of passwords to generate," << std::endl
              << "- mc is the minimum number of chars allowed in an alphanumeric password," << std::endl
              << "- MC is the maximum number of chars allowed in an alphanumeric password," << std::endl
              << "- of_pwd is the name of the output file where the passwords will be stored" << std::endl
              << "- of_hash is the name of the output file where the sha-256 hashes of the passwords will be stored" << std::endl;
}

void help::displayCrackHelp(){
    std::cout << "Usage : \"RainBowAttack attack RainbowTableFilePath resultPath {fileHash/hash}\", where" << std::endl
              << "- attack is to crack a given hash OR an entire file of hashes," << std::endl
              << "- RainbowTableFilePath is the path where the rainbow table is located," << std::endl
              << "- resultPath is the path where the result is stored," << std::endl
              << "- fileHash or hash is a specific hash or list of hash that you would like to crack," << std::endl
              << "example:" << std::endl
              << "  - on hash: attack D:\\temp\\rainbowTable.txt 15az3dfaz3f4zef3a1zef5d" << std::endl
              << "  - on file: attack D:\\temp\\rainbowTable.txt D:\\temp\\hash.txt" << std::endl;
}

void help::displayCheckPasswordHelp(){
    std::cout << "Usage : \"RainBowAttack check if_pwd if_hash\", where" << std::endl
              << "- check is for passwords generation," << std::endl
              << "- if_pwd is the name of the input file where the passwords are stored" << std::endl
              << "- if_hash is the name of the input file where the sha-256 hashes of the passwords are stored" << std::endl;
}

void help::displayRainbowTableHelp(){
    std::cout << "Usage : \"RainBowAttack generateTable inFilePath outFilePath\", where" << std::endl
              << "- generateTable is for rainbow table generation," << std::endl
              << "- inFilePath is the name of the input file where the passwords are stored" << std::endl
              << "- outFilePath is the name of the output file where the rainbow table will be stored" << std::endl;
}

void help::displayCommandHelp(){
    std::cout << "You can use 4 commands : 'generate', 'check', 'generateTable' and 'attack'" << std::endl << std::endl;

}
void help::displayParameterHelp(){
    std::cout << "Usage : \"RainBowAttack command parameters...\", where" << std::endl
              << "- command can be 'generate', 'check', 'generateTable' or attack" << std::endl
              << "- parameters that you will use with the command. " << std::endl << std::endl ;

}

}
