

#include "HuffmanTree.h"
#include "FileHandler.h"
#include "JSONHelper.h"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    // Check minimum arguments
    if (argc < 2) {
        cout << "Invalid number of arguments";
        return 1;
    }
    
    string action = argv[1];
    
    try {
        if (action == "encode") {
            if (argc != 5) {
                cout << "Encode requires: input output tree";
                return 1;
            }
            
            string inputFile = argv[2];
            string outputFile = argv[3];
            string treeFile = argv[4];
            
            string text;
            if (!FileHandler::readTextFile(inputFile, text)) {
                cout << "Cannot read input file";
                return 1;
            }
            
            unordered_map<char, int> frequencies = FileHandler::countFrequency(text);
            
            if (frequencies.empty()) {
                cout << "Empty file or no characters to encode";
                return 1;
            }
            
            HuffmanTree huffmanTree;
            huffmanTree.buildTree(frequencies);
            huffmanTree.generateHuffmanCodes();
            
            if (!huffmanTree.saveTreeToFile(treeFile)) {
                cout << "Cannot save tree file";
                return 1;
            }
            
            string encodedText = huffmanTree.encode(text);
            
            if (!FileHandler::writeBinaryFile(outputFile, encodedText)) {
                cout << "Cannot write compressed file";
                return 1;
            }
            
            size_t originalSize = FileHandler::getFileSize(inputFile);
            size_t compressedSize = FileHandler::getFileSize(outputFile);
            size_t treeSize = FileHandler::getFileSize(treeFile);
            
            JSONHelper::outputEncodeJSON(originalSize, compressedSize, treeSize, 
                                        frequencies, huffmanTree.getCodes());
            
        } 
        else if (action == "decode") {
            if (argc != 5) {
                cout << "Decode requires: compressed tree output";
                return 1;
            }
            
            string compressedFile = argv[2];
            string treeFile = argv[3];
            string outputFile = argv[4];
            
            HuffmanTree huffmanTree;
            if (!huffmanTree.loadTreeFromFile(treeFile)) {
                cout << "Cannot load tree file";
                return 1;
            }
            
            string encodedText;
            if (!FileHandler::readBinaryFile(compressedFile, encodedText)) {
                cout << "Cannot read compressed file";
                return 1;
            }
            
            string decodedText = huffmanTree.decode(encodedText);
            
            if (!FileHandler::writeTextFile(outputFile, decodedText)) {
                cout << "Cannot write output file";
                return 1;
            }
            
            JSONHelper::outputDecodeJSON(decodedText.length());
            
        } 
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
