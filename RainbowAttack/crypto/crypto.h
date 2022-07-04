#ifndef CRYPTO_H
#define CRYPTO_H

#include <stdio.h>
#include <string.h>
#include <chrono>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include "passwd-utils.hpp"
#include <mutex>
#include <map>
#include <thread>

namespace crypto {

class Crypto
{
private:
    static std::mutex myMutex;

    const static std::string delimiter;
    const static int limit;

    static constexpr std::array<char,62> alphabet = {
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
        'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
        'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
    };

    static void reduce(std::string &str, int &size);

    //static void reduce2(std::string &in, int &size);

    static void reduce3(std::string &in, int &size);

    //static void reduce4(std::string &in, int &size);

    static void chooseReducFunc(int *i, std::string &in, int &size);

    static void hashReduction(unsigned long long *outFileLineCount, std::ofstream *outFile,std::string value);

    std::array<std::string,3> splitRainbowTable(std::string rainbowTablePath);

    std::string getPasswordInRainbowLine(std::string originalHash, std::string head, std::string tail);


public:
    Crypto();
    void RainbowTableGeneration(std::string inFilePath, std::string outFilePath);
    bool crack(std::string inFilePath, std::string resultPath, std::string check_hash);
    void crackAll(std::string rainbowFilePath, std::string resultPath, std::string hashFilePath);
};

}



#endif // CRYPTO_H
