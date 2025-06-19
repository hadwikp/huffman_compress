#include <iostream>
#include "utils.hpp"
#include "huffman.hpp"
#include "io.hpp"

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0]
                  << " --compress <in> <out>  or  --decompress <in> <out>\n";
        return 1;
    }
    std::string mode = argv[1];
    std::string in_path = argv[2];
    std::string out_path = argv[3];

    if (mode == "--compress") {
        auto freq = countFrequencies(in_path);
        Node* root = buildHuffmanTree(freq);
        auto codes = generateCodes(root);
        // Compute total characters for header
        size_t total_chars = 0;
        for (const auto& kv : freq) {
            total_chars += kv.second;
        }
        writeCompressed(in_path, out_path, codes, total_chars);
    }
    else if (mode == "--decompress") {
        decompressFile(in_path, out_path);
    }
    else {
        std::cerr << "Unknown mode: " << mode << "\n";
        return 1;
    }
    return 0;
}
