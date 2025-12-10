/*
 * File: main.cpp
 * Location: backend/src/main.cpp
 * Description: Main program - command line interface for web integration
 * 
 * Usage:
 *   Encode: huffman encode input.txt output.bin tree.huf
 *   Decode: huffman decode compressed.bin tree.huf output.txt
 */

#include "HuffmanTree.h"
#include "FileHandler.h"
#include "JSONHelper.h"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    // Check minimum arguments
    if (argc < 4) {
        cout << "Invalid number of arguments";
        return 1;
    }
    
    string action = argv[1];
    
    try {
        // ENCODE ACTION
        if (action == "encode") {
            if (argc != 5) {
                cout << "Encode requires: input output tree";
                return 1;
            }
            
            string inputFile = argv[2];
            string outputFile = argv[3];
            string treeFile = argv[4];
            
            // Step 1: Read input file
            string text;
            if (!FileHandler::readTextFile(inputFile, text)) {
                cout << "Cannot read input file";
                return 1;
            }
            
            // Step 2: Count character frequencies
            unordered_map<char, int> frequencies = FileHandler::countFrequency(text);
            
            if (frequencies.empty()) {
                cout << "Empty file or no characters to encode";
                return 1;
            }
            
            // Step 3: Build Huffman Tree
            HuffmanTree huffmanTree;
            huffmanTree.buildTree(frequencies);
            huffmanTree.generateHuffmanCodes();
            
            // Step 4: Save tree structure to file
            if (!huffmanTree.saveTreeToFile(treeFile)) {
                cout << "Cannot save tree file";
                return 1;
            }
            
            // Step 5: Encode the text
            string encodedText = huffmanTree.encode(text);
            
            // Step 6: Write compressed binary file
            if (!FileHandler::writeBinaryFile(outputFile, encodedText)) {
                cout << "Cannot write compressed file";
                return 1;
            }
            
            // Step 7: Get file sizes for statistics
            size_t originalSize = FileHandler::getFileSize(inputFile);
            size_t compressedSize = FileHandler::getFileSize(outputFile);
            size_t treeSize = FileHandler::getFileSize(treeFile);
            
            // Step 8: Output results as JSON
            JSONHelper::outputEncodeJSON(originalSize, compressedSize, treeSize, 
                                        frequencies, huffmanTree.getCodes());
            
        } 
        // DECODE ACTION
        else if (action == "decode") {
            if (argc != 5) {
                cout << "Decode requires: compressed tree output";
                return 1;
            }
            
            string compressedFile = argv[2];
            string treeFile = argv[3];
            string outputFile = argv[4];
            
            // Step 1: Load Huffman Tree from file
            HuffmanTree huffmanTree;
            if (!huffmanTree.loadTreeFromFile(treeFile)) {
                cout << "Cannot load tree file";
                return 1;
            }
            
            // Step 2: Read compressed binary file
            string encodedText;
            if (!FileHandler::readBinaryFile(compressedFile, encodedText)) {
                cout << "Cannot read compressed file";
                return 1;
            }
            
            // Step 3: Decode the binary string
            string decodedText = huffmanTree.decode(encodedText);
            
            // Step 4: Write decoded text to output file
            if (!FileHandler::writeTextFile(outputFile, decodedText)) {
                cout << "Cannot write output file";
                return 1;
            }
            
            // Step 5: Output results as JSON
            JSONHelper::outputDecodeJSON(decodedText.length());
            
        } 
        // INVALID ACTION
        else {
            cout << "Invalid action. Use 'encode' or 'decode'";
            return 1;
        }
        
    } catch (const exception& e) {
        cout << string("Exception: ") + e.what();
        return 1;
    } catch (...) {
        cout << "Unknown error occurred";
        return 1;
    }
    
    return 0;
}
