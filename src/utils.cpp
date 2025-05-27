#include"utils.hpp"
#include<fstream>
#include<iostream>
#include<cstdlib>
#include<cstdio>

std::unordered_map<char,std::size_t> countFrequencies(const std::string& str)
{
    std::ifstream in(str,std::ios::binary);
    if(!in)
    {
        perror("Open Failed for input file ");
        std::exit(1);
    }
    std::unordered_map<char,std::size_t> freq;
    char c;
    while(in.get(c))
    {
        freq[c]++;
    }
    return freq;
}