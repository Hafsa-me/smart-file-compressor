/*
 * File: FileHandler.h
 * Location: backend/include/FileHandler.h
 * Description: Handles all file input/output operations
 */

#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <string>
#include <unordered_map>
#include <fstream>

using namespace std;

class FileHandler {
public:
    // Read text file
    static bool readTextFile(const string& filename, string& content);
    
    // Write text file
    static bool writeTextFile(const string& filename, const string& content);
    
    // Write binary file (converts binary string to actual bytes)
    static bool writeBinaryFile(const string& filename, const string& binaryString);
    
    // Read binary file (converts bytes to binary string)
    static bool readBinaryFile(const string& filename, string& binaryString);
    
    // Get file size in bytes
    static size_t getFileSize(const string& filename);
    
    // Count character frequencies in text
    static unordered_map<char, int> countFrequency(const string& text);
};

#endif