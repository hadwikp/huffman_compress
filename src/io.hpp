#pragma once
#include<string>
#include<unordered_map>
#include"huffman.hpp"

struct Header{
    size_t unique_chars;
    size_t total_chars;
    std::unordered_map<char,std::vector<bool>> codes;
};

void writeCompressed(const std::string& int_path , const std::string& out_path,
                    const std::unordered_map<char,std::vector<bool>>& codes , size_t total_chars);

Header readHeader(const std::string& in_path);

Node* rebuildTree(const Header& header);

void decompressFile(const std::string& in_path , const std::string& out_path,
                    Node* root,size_t total_chars);
