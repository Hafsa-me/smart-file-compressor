
#include "JSONHelper.h"
#include <iostream>
#include <iomanip>

using namespace std;

string JSONHelper::escapeJson(const string& str) {
    string result;
    for (char ch : str) {
        switch (ch) {
            case '"': result += "\\\""; break;
            case '\\': result += "\\\\"; break;
            case '\n': result += "\\n"; break;
            case '\r': result += "\\r"; break;
            case '\t': result += "\\t"; break;
            default: result += ch;
        }
    }
    return result;
}

string JSONHelper::charToString(char ch) {
    if (ch == ' ') return "SPACE";
    if (ch == '\n') return "NEWLINE";
    if (ch == '\t') return "TAB";
    if (ch == '\r') return "RETURN";
    return string(1, ch);
}

void JSONHelper::outputEncodeJSON(size_t originalSize, 
                                   size_t compressedSize, 
                                   size_t treeSize,
                                   const unordered_map<char, int>& frequencies,
                                   const unordered_map<char, string>& codes) {
    double ratio = (1.0 - (double)(compressedSize + treeSize) / originalSize) * 100;
    
    cout << "{" << endl;
    cout << "  \"success\": true," << endl;
    cout << "  \"originalSize\": " << originalSize << "," << endl;
    cout << "  \"compressedSize\": " << (compressedSize + treeSize) << "," << endl;
    cout << "  \"compressionRatio\": " << fixed << setprecision(2) << ratio << "," << endl;
    cout << "  \"frequencies\": [" << endl;
    
    bool first = true;
    for (const auto& pair : frequencies) {
        if (!first) cout << "," << endl;
        first = false;
        
        cout << "    {" << endl;
        cout << "      \"char\": \"" << escapeJson(charToString(pair.first)) << "\"," << endl;
        cout << "      \"freq\": " << pair.second << "," << endl;
        
        if (codes.find(pair.first) != codes.end()) {
            cout << "      \"code\": \"" << codes.at(pair.first) << "\"" << endl;
        } else {
            cout << "      \"code\": \"\"" << endl;
        }
        
        cout << "    }";
    }
    
    cout << endl << "  ]" << endl;
    cout << "}" << endl;
}

void JSONHelper::outputDecodeJSON(size_t decompressedSize) {
    cout << "{" << endl;
    cout << "  \"success\": true," << endl;
    cout << "  \"decompressedSize\": " << decompressedSize << endl;
    cout << "}" << endl;
}

