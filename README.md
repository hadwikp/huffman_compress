# Huffman Compress

C++17 implementation of lossless text compression/decompression using Huffman coding.

## Build & Run
```bash
mkdir build
cd build
cmake ..
make
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
