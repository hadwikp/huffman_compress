#pragma once
#include<unordered_map>
#include<vector>

struct Node{
    char character;
    size_t freq;
    Node *left,*right;
    Node(char c,size_t f):character(c),freq(f),right(nullptr),left(nullptr) {}
};

Node* buildHuffmanTree(const std::unordered_map<char,size_t>&);

std::unordered_map<char,std::vector<bool>> generateCodes(Node*);