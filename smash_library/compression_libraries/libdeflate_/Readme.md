# LibDeflate

## About
[LibDeflate](https://github.com/ebiggers/libdeflate) is a library for fast, whole-buffer DEFLATE-based compression and decompression.

## Options
### To compress
* **Compression level** - (integer, 0-12, default 0)
  * **0** - obtains the fastest compression.
  * **12** - obtains the highest compression ratio.
* **Mode** - (integer, 0-2, default 0)
  * **0 - Deflate**.
  * **1 - Zlib**.
  * **2 - Gzip**.

### To decompress
* **Mode** - (integer, 0-2, default 0)
  * **0 - Deflate**.
  * **1 - Zlib**.
  * **2 - Gzip**.

## License
LibDeflate is licensed under the [MIT License](https://github.com/ebiggers/libdeflate/blob/master/COPYING).
