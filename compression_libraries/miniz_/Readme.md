# Miniz

## About
[Miniz](https://github.com/richgel999/miniz) is a lossless, high performance data compression library in a single source file that implements the zlib (RFC 1950) and Deflate (RFC 1951) compressed data format specification standards. It supports the most commonly used functions exported by the zlib library, but is a completely independent implementation so zlib's licensing requirements do not apply. Miniz also contains simple to use functions for writing .PNG format image files and reading/writing/appending .ZIP format archives.

## Options
### To compress
* **Compression level** - (integer, 1-9, default 1)
  * **1** - obtains the fastest compression.
  * **9** - obtains the highest compression ratio.
* **Window size** - (integer, 10-11, default 10)
  * Bits used to indicate the real window size used by this compression library.
* **Mode** - (integer, 0-4, default 0)
  * **0 - Default**.
  * **1 - Filtered**. For data produced by a filter (or predictor).
  * **2 - Huffman**. Force Huffman encoding only
  * **3 - Rle**. Limit match distances to one.
  * **4 - Fixed**. Prevent the use of dynamic Huffman codes.

### To decompress
* **Window size** - (integer, 10-11, default 10)
  * Bits used to indicate the real window size used by this compression library.

## License
Miniz is licensed under the [MIT License](https://github.com/richgel999/miniz/blob/master/LICENSE).
