# LodePNG

## About
[LodePNG](https://github.com/lvandeve/lodepng) is a PNG encoder and decoder in C and C++, without dependencies.

## Options
### To compress
* **Compression level** - (integer, 1-2, default 1)
  * **1** - obtains the fastest compression.
  * **2** - obtains the highest compression ratio.
* **Window size** - (integer, 10-15, default 10)
  * Bits used to indicate the real window size used by this compression library.
* **Work factor** - (integer, 1-20, default 1)
  * This option controls the compression behaviour when there is repetitive data.
* **Flags** - (integer, 0-1, default 0)
  * **0 - Fast compression**.
  * **1 - Slow compression**.
* **Back reference bits** - (integer, 1-8, default 1)
  * Bits used to determine the maximum length for repeated patterns that are found by this compression library.

## License
LodePNG is licensed under the [ZLIB License](https://github.com/lvandeve/lodepng/blob/master/LICENSE).
