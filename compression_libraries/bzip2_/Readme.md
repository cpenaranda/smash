# Bzip2

## About
[Bzip2](https://gitlab.com/bzip2/bzip2) is a program and library for lossless, block-sorting data compression.

## Options
### To compress
* **Compression level** - (integer, 1-9, default 1)
  * **1** - obtains the fastest compression.
  * **9** - obtains the highest compression ratio.
* **Work factor** - (integer, 0-250, default 0)
  * This option controls the compression behaviour when there is repetitive data.

## To decompress
* **Mode** - (integer, 0-1, default 0)
  * **0 - Faster decompression** using more memory.
  * **1 - Slower decompression** using less memory.

## License
Bzip2 is released under the terms of the license contained in the [file](https://gitlab.com/bzip2/bzip2/-/blob/master/COPYING).

