#pragma once
#include<string>
#include<unordered_map>
#include"huffman.hpp"

struct Header{
    size_t unique_chars;
    size_t total_chars;
    std::unordered_map<char,std::vector<bool>> codes;
};

// Write compressed file: header and body
void writeCompressed(const std::string& in_path,
                     const std::string& out_path,
                     const std::unordered_map<char, std::vector<bool>>& codes,
                     size_t total_chars);

// Read header from stream, advancing its position
Header readHeader(std::ifstream& in);

// Rebuild Huffman tree from header data
Node* rebuildTree(const Header& header);

// Decompress using an open stream positioned after header
void decompressFile(const std::string& in_path,
                    const std::string& out_path);
