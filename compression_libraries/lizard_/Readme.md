# Lizard

## About
[Lizard](https://github.com/inikep/lizard) is based on frequently used LZ4 library by Yann Collet but the Lizard compression format is not compatible with LZ4.

## Options
### To compress
* **Compression level** - (integer, 0-9, default 0)
  * **0** - obtains the fastest compression.
  * **9** - obtains the highest compression ratio.
* **Mode** - (integer, 0-3, default 0)
  * **0 - Fast LZ4 method**.
  * **1 - Fast LIZv1 method**.
  * **2 - Fast LZ4 + Huffman method**.
  * **3 - Fast LIZv1 + Huffman method**.

## License
Lizard is dual-licensed under the [2-Clause BSD License](https://github.com/inikep/lizard/blob/lizard/lib/LICENSE) and the [GPLv2 License](https://github.com/inikep/lizard/blob/lizard/LICENSE).
