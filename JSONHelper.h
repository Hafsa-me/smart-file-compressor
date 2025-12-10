/*
 * File: JSONHelper.h
 * Location: backend/include/JSONHelper.h
 * Description: Helper functions for JSON output (web integration)
 */

#ifndef JSON_HELPER_H
#define JSON_HELPER_H

#include <string>
#include <unordered_map>

using namespace std;

class JSONHelper {
public:
    // Escape special characters for JSON
    static string escapeJson(const string& str);
    
    // Convert character to display string
    static string charToString(char ch);
    
    // Output encoding results as JSON
    static void outputEncodeJSON(size_t originalSize, 
                                 size_t compressedSize, 
                                 size_t treeSize,
                                 const unordered_map<char, int>& frequencies,
                                 const unordered_map<char, string>& codes);
    
    // Output decoding results as JSON
    static void outputDecodeJSON(size_t decompressedSize);
    
};

#endif