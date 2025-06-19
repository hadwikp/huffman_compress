#include "io.hpp"
#include <fstream>
#include <bitset>
#include <cstdint>

void writeCompressed(const std::string& in_path,
                     const std::string& out_path,
                     const std::unordered_map<char, std::vector<bool>>& codes,
                     size_t total_chars) {
    std::ifstream in(in_path, std::ios::binary);
    std::ofstream out(out_path, std::ios::binary);

    // Write header: unique count (uint64), total count (uint64)
    uint64_t uc = static_cast<uint64_t>(codes.size());
    uint64_t tc = static_cast<uint64_t>(total_chars);
    out.write(reinterpret_cast<char*>(&uc), sizeof(uc));
    out.write(reinterpret_cast<char*>(&tc), sizeof(tc));

    // Write codes: char, length, and packed bits
    for (auto& kv : codes) {
        char c = kv.first;
        uint8_t len = static_cast<uint8_t>(kv.second.size());
        out.write(&c, 1);
        out.write(reinterpret_cast<char*>(&len), 1);
        uint8_t buf = 0, bit_count = 0;
        for (bool b : kv.second) {
            buf = (buf << 1) | b;
            if (++bit_count == 8) {
                out.write(reinterpret_cast<char*>(&buf), 1);
                buf = bit_count = 0;
            }
        }
        if (bit_count) {
            buf <<= (8 - bit_count);
            out.write(reinterpret_cast<char*>(&buf), 1);
        }
    }

    // Write body bits
    uint8_t buf = 0, bit_count = 0;
    char c;
    while (in.get(c)) {
        for (bool b : codes.at(c)) {
            buf = (buf << 1) | b;
            if (++bit_count == 8) {
                out.write(reinterpret_cast<char*>(&buf), 1);
                buf = bit_count = 0;
            }
        }
    }
    if (bit_count) {
        buf <<= (8 - bit_count);
        out.write(reinterpret_cast<char*>(&buf), 1);
    }
}

Header readHeader(std::ifstream& in) {
    Header h;
    // Read fixed-size counts
    uint64_t uc, tc;
    in.read(reinterpret_cast<char*>(&uc), sizeof(uc));
    in.read(reinterpret_cast<char*>(&tc), sizeof(tc));
    h.unique_chars = static_cast<size_t>(uc);
    h.total_chars  = static_cast<size_t>(tc);

    // Read codes
    for (size_t i = 0; i < h.unique_chars; ++i) {
        char c;
        uint8_t len;
        in.read(&c, 1);
        in.read(reinterpret_cast<char*>(&len), 1);
        std::vector<bool> bits;
        size_t byte_count = (len + 7) / 8;
        for (size_t b = 0; b < byte_count; ++b) {
            uint8_t buf;
            in.read(reinterpret_cast<char*>(&buf), 1);
            for (int bit = 7; bit >= 0 && bits.size() < len; --bit) {
                bits.push_back((buf >> bit) & 1);
            }
        }
        h.codes[c] = bits;
    }
    return h;
}

Node* rebuildTree(const Header& header) {
    Node* root = new Node('\0', 0);
    for (auto& kv : header.codes) {
        Node* cur = root;
        for (bool b : kv.second) {
            if (!b) {
                if (!cur->left) cur->left = new Node('\0', 0);
                cur = cur->left;
            } else {
                if (!cur->right) cur->right = new Node('\0', 0);
                cur = cur->right;
            }
        }
        cur->character = kv.first;
    }
    return root;
}

void decompressFile(const std::string& in_path,
                    const std::string& out_path) {
    std::ifstream in(in_path, std::ios::binary);
    std::ofstream out(out_path, std::ios::binary);

    // Read header & codes from same stream
    Header h = readHeader(in);
    Node* root = rebuildTree(h);

    // Decode body
    size_t written = 0;
    Node* cur = root;
    char byte;
    while (written < h.total_chars && in.get(byte)) {
        std::bitset<8> bits((unsigned char)byte);
        for (int i = 7; i >= 0 && written < h.total_chars; --i) {
            cur = bits[i] ? cur->right : cur->left;
            if (!cur->left && !cur->right) {
                out.put(cur->character);
                ++written;
                cur = root;
            }
        }
    }
}