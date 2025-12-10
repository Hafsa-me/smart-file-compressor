

#ifndef JSON_HELPER_H
#define JSON_HELPER_H

#include <string>
#include <unordered_map>

using namespace std;

class JSONHelper {
public:
    static string escapeJson(const string& str);
    
    static string charToString(char ch);
    
    static void outputEncodeJSON(size_t originalSize, 
                                 size_t compressedSize, 
                                 size_t treeSize,
                                 const unordered_map<char, int>& frequencies,
                                 const unordered_map<char, string>& codes);
    
    static void outputDecodeJSON(size_t decompressedSize);
    
};

#endif