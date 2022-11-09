# Brotli

## About
[Brotli](https://github.com/google/brotli) is a generic-purpose lossless compression algorithm that compresses data using a combination of a modern variant of the LZ77 algorithm, Huffman coding and 2nd order context modeling, with a compression ratio comparable to the best currently available general-purpose compression methods. It is similar in speed with deflate but offers more dense compression.

The specification of the Brotli Compressed Data Format is defined in [RFC 7932](https://datatracker.ietf.org/doc/html/rfc7932).

## Options
### To compress
* **Compression level** - (integer, 0-11, default 0)
  * **0** - obtains the fastest compression.
  * **11** - obtains the highest compression ratio.
* **Window size** - (integer, 10-24, default 10)
  * Bits used to indicate the real window size used by this compression library.
* **Mode** - (integer, 0-2, default 0)
  * **0 - Any input**.
  * **1 - UTF-8 input**.
  * **2 - Web Open Font Format input**.

## License
Brotli is licensed under the [MIT License](https://github.com/google/brotli/blob/master/LICENSE).

