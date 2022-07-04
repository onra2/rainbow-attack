#include "crypto.h"
#include "threadpool.hpp"
#include "timer.h"

namespace crypto {

    std::mutex Crypto::myMutex;
    const std::string Crypto::delimiter = " ";
    const int Crypto::limit = 10000;

    Crypto::Crypto()
    {

    }

    void Crypto::reduce(std::string &in, int &size){
        int j = 0;

        for(int i(0); i < size; ++i){
            in[i] = alphabet[ (in[i]+ j ) % alphabet.size()];
            j = (j + 9) % in.length();
        }
        in.resize(size);
    }

    //full of collision, unusable and return only uppercases and numbers
    /*void Crypto::reduce2(std::string &in, int &size){
        std::string::size_type k = (size / in.length() + 1);
        int k_idx;

        if(k > in.length()){
            k = (k - 1) % in.length() + 1;
            k_idx = (size - 1) % in.length();
        }else{
            k_idx = size - ((k-1)*in.length() + 1);
        }

        if(k == in.length()) k = 9;

        int j = k_idx;
        for(int i = 0; i < size; i++ ){
            in[i] = alphabet[(in[i]+j) % alphabet.size()];
            j = (j + k) % in.length();
        }
        in.resize(size);
    }*/

    //Return only lowercases and numbers
    /*void Crypto::reduce3(std::string &in, int &size){
        int j = 0;
        uint8_t byte, mask;

        for(int i = 0; i < size; i++){
            byte  = in[ (i + size - 1) % in.length()];
            mask = 0x7f;
            byte &= mask;

            if(( 0x2f< byte && byte<=0x39 )
            ||  ( 0x41<=byte && byte <0x5b )
            ||  ( 0x61<=byte && byte <0x7b )){
                in[j] = (char)byte;
            }
            else if((byte>=0x3a && byte<=0x41)
                ||  (byte>=0x7b && byte<=0x7f)){
                in[j] = '@';
            }
            else if((byte<=0x2f) || (byte>=0x5b && byte<=0x60)) {
                in[j] = '!';
            }
            else {
                std::cerr << "Case not supported!" << (int)byte << std::endl;
            }

            j++;
        }
        in.resize(size);
    }*/

    // full of collision, unusable
    /*void Crypto::reduce4(std::string &in, int &size)
    {
        int i, j;
        int range_from = 0;
        int range_to = alphabet.size();

        j = (size + 9) % in.length();

        std::default_random_engine generator(in[j]);
        std::uniform_int_distribution<int> distr(range_from, range_to);

        for(i = 0; i < size; i++ ){
            in[i] = alphabet[distr(generator)];
        }
        in.resize(size);
    }*/

    // useless with only one reduction function
    /*void Crypto::chooseReducFunc(int *i, std::string &in, int &size)
    {
        //Cette ordre la est particulièrement bon for some reason
        if(*i % 2 == 0){
            reduce2(in, size);
            return;
        }
        if(*i % 2 == 0){
            reduce3(in, size);
            return;
        }
        if(*i % 4 == 0){
            reduce4(in, size);
            return;
        }
        else{
            reduce(in, size);
            return;
        }
    }*/

    void Crypto::hashReduction(unsigned long long *outFileLineCount, std::ofstream *outFile, std::string value){
        std::string orignalValue(value);
        int size = value.length();

        for(int i(0); i < Crypto::limit; ++i){
            value = crypto::sha256(value);
            reduce(value, size);
        }

        std::unique_lock<std::mutex> myLock(Crypto::myMutex);
        // Write head and tail
        *outFile << orignalValue << Crypto::delimiter << value << "\n";
        ++*outFileLineCount;
        myLock.unlock();
    }

    void Crypto::RainbowTableGeneration(std::string inFilePath, std::string outFilePath) {
        std::string currentValue;

        std::ifstream inFile;
        inFile.open(inFilePath);

        std::ofstream outFile;
        outFile.open(outFilePath);

        std::cout << std::boolalpha;
        std::cout << "inFile \"" << inFilePath << "\" isOpen: " << inFile.is_open() << std::endl;
        std::cout << "outFile \""<< outFilePath << "\" isOpen: " << outFile.is_open() << std::endl;

        if(inFile && outFile){

            int threadsNumber = std::thread::hardware_concurrency();
            std::cout << "Detected CPU threads number : " << threadsNumber << std::endl
                      << "hash-reduciton per line: " << Crypto::limit  << std::endl;

            unsigned long long inFileLineCount = 0;
            unsigned long long outFileLineCount = 0;
            ThreadPool tp;

            Timer timer;
            std::cout << std::endl << timer.currentTime() << "Processing ..." << std::endl;
            timer.start();

            while(getline(inFile, currentValue)){
                // Limite file reader memory usage to approximatively 1.5Go (with 6 to 8 characters password)
                while((inFileLineCount - outFileLineCount) > 5000000){
                    std::this_thread::sleep_for(std::chrono::milliseconds(10));
                }

                ++inFileLineCount;
                tp.enqueue(&hashReduction, &outFileLineCount, &outFile, currentValue);
            }

            while(outFileLineCount < inFileLineCount){
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }

            timer.stop();
            std::cout << std::endl  << timer.currentTime() << "End processing" << std::endl << std::endl;
            timer.displayChrono();
        }

        inFile.close();
        outFile.close();
    }

    bool Crypto::crack(std::string rainbowTablePath, std::string resultPath, std::string sourceHash) {

        bool haveResult = false;
        std::string valueToCheck = sourceHash;

        std::ofstream attackResultFile;
        attackResultFile.open(resultPath);

        std::array<std::string,3> rainBowtables = splitRainbowTable(rainbowTablePath);

        std::cout << std::boolalpha;
        std::cout << "--------------------------------------------------------------------------------------" << std::endl;
        std::cout << "Trying to crack hash: " << sourceHash << std::endl;
        std::cout << "Thinking..." << std::endl;

        std::string currentLine;

        std::string lineHead = "";
        std::string lineTail = "";

        std::vector<std::string> results;

        for(size_t rainbowIndex(0); rainbowIndex < rainBowtables.size(); ++rainbowIndex){
            std::ifstream rainbowTableFile;
            rainbowTableFile.open(rainBowtables.at(rainbowIndex));
            int reduceSize(rainbowIndex + 6);

            //std::cout << "check size " << reduceSize << std::endl;

            int i = 0;
            while(i < Crypto::limit) {

                reduce(valueToCheck, reduceSize);

                while (getline(rainbowTableFile, currentLine)) {

                    lineHead = currentLine.substr(0, currentLine.find(Crypto::delimiter));
                    lineTail = currentLine.substr(currentLine.find(Crypto::delimiter) + 1, currentLine.length());

                    if(valueToCheck == lineTail){
                        //std::cout << "i: " << i <<  " Tail: " << lineTail << ", ";
                        //TODO: multithreading
                        haveResult = true;
                        std::string result = getPasswordInRainbowLine(sourceHash,lineHead,lineTail);
                        if(result != "" && !std::binary_search(results.begin(), results.end(), result)){
                            std::cout << "Password was found: " << result << std::endl;
                            results.push_back(result);
                            attackResultFile << sourceHash << Crypto::delimiter << result << std::endl;
                        }
                    }
                }

                valueToCheck = crypto::sha256(valueToCheck);
                rainbowTableFile.clear();
                rainbowTableFile.seekg(0, std::ios::beg);
                ++i;
            }

            rainbowTableFile.close();
            attackResultFile.close();

        }

        if(results.size() == 0){
            std::cout << "Password was not found" << std::endl;
        }

        return haveResult;
    }

    void Crypto::crackAll(std::string rainbowTablePath, std::string resultPath, std::string hashFilePath)
    {
        std::ifstream hashFile;
        hashFile.open(hashFilePath);

        std::string attack_hash;

        double correctCount = 0;
        double sur = 0;
        while(getline(hashFile, attack_hash)){
            if(this->crack(rainbowTablePath, resultPath, attack_hash)){
               ++correctCount;
            }
            ++sur;
        }
        hashFile.close();
        std::cout << "----------------------------------------------------------------------------" << std::endl;
        std::cout << "Total found passwords: " << correctCount << "/" << sur << " | " << (correctCount/sur)*100 << "%" << std::endl;
    }

    std::array<std::string,3> Crypto::splitRainbowTable(std::string rainbowTablePath){

        std::array<std::string,3> rainBowtables = {rainbowTablePath + '6',rainbowTablePath + '7',rainbowTablePath + '8'};

        std::ifstream rainbowTableFile;
        rainbowTableFile.open(rainbowTablePath);

        std::ofstream outFile6;
        outFile6.open(rainBowtables.at(0));

        std::ofstream outFile7;
        outFile7.open(rainBowtables.at(1));

        std::ofstream outFile8;
        outFile8.open(rainBowtables.at(2));

        std::string currentLine;
        std::string lineHead = "";

        while (getline(rainbowTableFile, currentLine)) {
            lineHead = currentLine.substr(0, currentLine.find(Crypto::delimiter));
            switch (lineHead.length()) {
            case 6:
                outFile6 << currentLine << "\n";
                break;
            case 7:
                outFile7 << currentLine << "\n";
                break;
            case 8:
                outFile8 << currentLine << "\n";
                break;
            }
        }

        outFile6.close();
        outFile7.close();
        outFile8.close();

        return rainBowtables;

    }

    std::string Crypto::getPasswordInRainbowLine(std::string sourceHash, std::string head, std::string tail){
        std::string BasePassword = head;
        std::string tempReduction = head;

        bool isDone = false;
        int size = head.length();

        while (!isDone && head != tail) {

            head = crypto::sha256(head);
            if(sourceHash != head){
                reduce(head, size);
                tempReduction = head;
            }
            else{
                isDone = true;
            }
        }

        return (isDone)? tempReduction : "";
    }

}
