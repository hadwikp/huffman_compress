#include <catch2/catch_test_macros.hpp>
#include <fstream>
#include "utils.hpp"
#include "huffman.hpp"
#include "io.hpp"

TEST_CASE("Roundtrip compression and decompression", "[roundtrip]") {
    const std::string input_path      = "sample_in.txt";
    const std::string compressed_path = "sample_out.bin";
    const std::string output_path     = "sample_out.txt";

    // 1) Write a small sample file
    std::string sample_text = "aaabbcdeeeeefffff";
    {
        std::ofstream out(input_path, std::ios::binary);
        out << sample_text;
    }

    // 2) Compress it
    auto freq  = countFrequencies(input_path);
    auto root  = buildHuffmanTree(freq);
    auto codes = generateCodes(root);
    writeCompressed(input_path, compressed_path, codes, sample_text.size());

    // 3) Decompress with the new API
    decompressFile(compressed_path, output_path);

    // 4) Read back the output and compare
    std::ifstream in(output_path, std::ios::binary);
    std::string decompressed{ std::istreambuf_iterator<char>(in),
                              std::istreambuf_iterator<char>() };

    REQUIRE(decompressed == sample_text);
}
