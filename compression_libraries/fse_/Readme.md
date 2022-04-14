# Finite State Entropy

## About
[Finite State Entropy](https://github.com/Cyan4973/FiniteStateEntropy) library proposes two high speed entropy coders :
* **Huff0** - A [Huffman codec](https://en.wikipedia.org/wiki/Huffman_coding) designed for modern CPU, featuring OoO (Out of Order) operations on multiple ALU (Arithmetic Logic Unit), achieving extremely fast compression and decompression speeds.
* **FSE** - A new kind of [Entropy encoder](http://en.wikipedia.org/wiki/Entropy_encoding), based on [ANS theory, from Jarek Duda](http://arxiv.org/abs/1311.2540), achieving precise compression accuracy (like [Arithmetic coding](http://en.wikipedia.org/wiki/Arithmetic_coding)) at much higher speeds.

## Options
### To compress
* **Mode** - (integer, 0-1, default 0)
  * **0 - FSE coder**.
  * **1 - Huff0 coder**.

### To decompress
* **Mode** - (integer, 0-1, default 0)
  * **0 - FSE coder**.
  * **1 - Huff0 coder**.

## License
Finite State Entropy is licensed under the [2-Clause BSD License](https://github.com/Cyan4973/FiniteStateEntropy/blob/dev/LICENSE).

