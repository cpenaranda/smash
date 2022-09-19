# Zling

## About
[Zling](https://github.com/Dead2/zlib-ng) is an improved lightweight compression utility and library. libzling uses fast order-1 ROLZ (16MB block size and 10MB dictionary size) followed with Huffman encoding, making it 3 times as fast as gzip on compressing, while still getting much better compression ratio and decompression speed.

## Options
### To compress
* **Compression level** - (integer, 0-4, default 0)
  * **4** - obtains the fastest compression.
  * **0** - obtains the highest compression ratio.

## License
Zling is licensed under the [3-clause BSD License](https://opensource.org/licenses/BSD-3-Clause).