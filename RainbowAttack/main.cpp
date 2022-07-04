#include <iostream>
#include <cstring>
#include "crypto/help.h"
#include "crypto/crypto.h"
#include <stdbool.h>

using namespace std;

bool is_readable( const std::string & file )
{
    std::ifstream fichier( file.c_str() );
    bool result = !fichier.fail();
    if(result){
        fichier.close();
    }
    return result;
}

int main(int argc, char *argv[])
{
    if(argc > 1){
        // Pasword generation
        if(std::string(argv[1]) == "generate"){
            if(argc == 7)
            {
                std::cout << std::endl << "Processing with Hash" << std::endl;
                rainbow::mass_generate(std::stoi(argv[2]), std::stoi(argv[3]), std::stoi(argv[4]), argv[5], argv[6]);
                std::cout << "End processing" << std::endl << std::endl;
            }else if(argc == 6)
            {
                std::cout << std::endl << "Processing without Hash" << std::endl;
                rainbow::mass_generate(std::stoi(argv[2]), std::stoi(argv[3]), std::stoi(argv[4]), argv[5], "");
                std::cout << "End processing" << std::endl << std::endl;
            }else{
                crypto::help::displayPasswordGenerationHelp();
            }

        // Check generate password
        }else if(std::string(argv[1]) == "check"){
            if(argc == 4)
            {
                double success = rainbow::mass_check(argv[2], argv[3]);
                std::cout << success << "% success" << std::endl;
            }else{
                crypto::help::displayCheckPasswordHelp();
            }

        // Rainbow table generation
        }else if(std::string(argv[1]) == "generateTable"){
            std::string existingFile;
            if(argc == 4){
                crypto::Crypto crypto;

                if( ! is_readable(argv[2]) ){
                    cerr << "Password file not found."<<std::endl;
                }else{
                    crypto.RainbowTableGeneration(argv[2],argv[3]);
                }

            }else{
                crypto::help::displayRainbowTableHelp();
            }

        // Rainbow attack
        }else if (std::string(argv[1]) == "attack") {
            if(argc == 6)
            {
                std::string existingFile;
                std::string arg3 = argv[3];
                if(!is_readable(argv[3]) ){
                    cerr << "RainbowTable file not found."<<std::endl;

                }else{
                    crypto::Crypto crypto;

                    if(is_readable(argv[5])){
                        crypto.crackAll(argv[3], argv[4], argv[5]);

                    }else if(std::strlen(argv[5]) == 64){
                        crypto.crack(argv[3], argv[4], argv[5]);

                    }else{
                        cerr << "Error on hash"<<std::endl;
                    }
                }

            }else {
                crypto::help::displayCrackHelp();
            }

        // Error on command
        }else{
            crypto::help::displayCommandHelp();
        }

    // Error general
    }else{
        crypto::help::displayParameterHelp();
    }
    return 0;
}
