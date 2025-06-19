#include <catch2/catch_test_macros.hpp>
#include "huffman.hpp"

TEST_CASE("Huffman Tree builds correct codes","[huffman]") {
    std::unordered_map<char,size_t> freq={
        {'a',5},
        {'b',9},
        {'c',12},
        {'d',13},
        {'e',16},
        {'f',45}
    };

    Node* root=buildHuffmanTree(freq);
    auto codes=generateCodes(root);

    REQUIRE(codes.size()==freq.size());

    for (auto& [ch,code] : codes) {
        REQUIRE(code.size()>0);
    }

    // Check prefix property (no code is a prefix of another)
    for (auto& [a, acode] : codes) {
        for (auto& [b, bcode] : codes) {
            if (a != b) {
                REQUIRE(!(std::mismatch(acode.begin(), acode.end(), bcode.begin()).first == acode.end()));
            }
        }
    }
}
