#include<iostream>
#include<fstream>
#include"utils.hpp"
#include"huffman.hpp"
#include"io.hpp"

int main(int argc,char* argv[])
{
    if(argc<5)
    {
        std::cerr<<"Usage:"<<argv[0]<<" --compress <in> <out>"<<"or --decompress <in> <out>\n";
        return 1;
    }
    std::string mode=argv[1];
    std::string in_path=argv[2];
    std::string out_path=argv[3];

    if(mode=="--compress")
    {
        auto freq=countFrequencies(in_path);
        Node* root=buildHuffmanTree(freq);
        auto codes=generateCodes(root);
        writeCompressed(in_path,out_path,codes,freq.size());
    }
    else if(mode=="--decompress")
    {
        auto head=readHeader(in_path);
        Node* root=rebuild(head);
        decompressFile(in_path,out_path,root,head.total_chars);
    }
    else{
        std::cerr<<"Unknown mode: "<<mode<<"\n";
        return 1;
    }
    return 0;
}