/*
 * File: FileHandler.cpp
 * Location: backend/src/FileHandler.cpp
 * Description: Implementation of file handling operations
 */

#include "FileHandler.h"
#include <fstream>
#include <iostream>
#include <string>

// Read entire text file into string
bool FileHandler::readTextFile(const string& filename, string& content) {
    ifstream inputFile(filename);
    
    if (!inputFile.is_open()) {
        return false;
    }

    string line;
    while(getline(inputFile, line)){
        content += line;
    }
    
    inputFile.close();
    return content.length() !=0;
}

// Write string to text file
bool FileHandler::writeTextFile(const string& filename, const string& content) {
    ofstream outputFile(filename);
    
    if (!outputFile.is_open()) {
        return false;
    }
    
    outputFile << content;
    outputFile.close();
    return true;
}

// Write binary string to file (converts '0' and '1' chars to actual bits)
bool FileHandler::writeBinaryFile(const string& filename, const string& binaryString) {
    ofstream outFile(filename, ios::binary);
    
    if (!outFile.is_open()) {
        return false;
    }
    
    // Write the original length first (for proper decoding)
    size_t length = binaryString.length();
    outFile.write(reinterpret_cast<const char*>(&length), sizeof(length));
    
    // Convert binary string to bytes (8 bits per byte)
    unsigned char byte = 0;
    int bitCount = 0;
    
    for (char bit : binaryString) {
        byte = (byte << 1) | (bit - '0');  // Shift and add bit
        bitCount++;
        
        if (bitCount == 8) {
            outFile.write(reinterpret_cast<char*>(&byte), 1);
            byte = 0;
            bitCount = 0;
        }
    }
    
    // Write remaining bits with padding
    if (bitCount > 0) {
        byte <<= (8 - bitCount);  // Pad with zeros
        outFile.write(reinterpret_cast<char*>(&byte), 1);
    }
    
    outFile.close();
    return true;
}

// Read binary file and convert to binary string ('0' and '1' chars)
bool FileHandler::readBinaryFile(const string& filename, string& binaryString) {
    ifstream inFile(filename, ios::binary);
    
    if (!inFile.is_open()) {
        return false;
    }
    
    // Read the original binary string length
    size_t length;
    inFile.read(reinterpret_cast<char*>(&length), sizeof(length));
    
    binaryString = "";
    unsigned char byte;
    
    // Read each byte and convert to 8-bit binary string
    while (inFile.read(reinterpret_cast<char*>(&byte), 1)) {
        for (int i = 7; i >= 0; i--) {
            binaryString += ((byte >> i) & 1) ? '1' : '0';
        }
    }
    
    // Trim to original length (remove padding)
    if (binaryString.length() > length) {
        binaryString = binaryString.substr(0, length);
    }
    
    inFile.close();
    return true;
}

// Get file size in bytes
size_t FileHandler::getFileSize(const string& filename) {
    ifstream file(filename, ios::binary | ios::ate);
    if (!file.is_open()) {
        return 0;
    }
    
    size_t size = file.tellg();
    file.close();
    return size;
}

// Count frequency of each character in text
unordered_map<char, int> FileHandler::countFrequency(const string& text) {
    unordered_map<char, int> frequencies;
    
    for (int i =0; i < text.length(); i++) {
        char ch = text[i];
        frequencies[ch]++;
    }
    
    return frequencies;
}