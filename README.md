# Huffman Compress

C++17 implementation of lossless text compression/decompression using Huffman coding.

This project implements an efficient, lossless file-compression and decompression system based on Huffman coding.By constructing an optimal prefix code for the symbols in the input data, it reduces file size—often by up to 50%—without discarding or altering any information. The compressed output can be transmitted easily, and upon decompression the original file is recovered exactly, with zero errors or data loss.

## Build & Run
```bash
mkdir build
cd build
cmake ..
make
cd ..
```

Compress:
```bash
./build/huffman --compress input.txt output.bin
```

Decompress:
```bash
./build/huffman --decompress input.bin output.txt
```

## Testing
```bash
cd build
ctest --output-on-failure
