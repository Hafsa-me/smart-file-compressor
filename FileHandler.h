

#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <string>
#include <unordered_map>
#include <fstream>

using namespace std;

class FileHandler {
public:
    static bool readTextFile(const string& filename, string& content);
    
    static bool writeTextFile(const string& filename, const string& content);
    
    static bool writeBinaryFile(const string& filename, const string& binaryString);
  
    static bool readBinaryFile(const string& filename, string& binaryString);
    
    static size_t getFileSize(const string& filename);
    
    static unordered_map<char, int> countFrequency(const string& text);
};

#endif