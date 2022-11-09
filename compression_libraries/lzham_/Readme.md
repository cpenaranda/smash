# Lzham - Lossless Data Compression Codec
Author: [Richard Geldreich, Jr](richgel99@gmail.com)

## About
[Lzham](https://github.com/richgel999/lzham_codec_devel) is a lossless (LZ based) data compression codec optimized for particularly fast decompression at very high compression ratios with a zlib compatible API.

## Options
### To compress
* **Compression level** - (integer, 0-4, default 0)
  * **0** - obtains the fastest compression.
  * **4** - obtains the highest compression ratio.
* **Window size** - (integer, 15-29, default 15)
  * Bits used to indicate the real window size used by this compression library.
* **Flags** - (integer, 0-7, default 0)
  * **0 - No filter**.
  * **1 - Extreme parsing**. This flag is much slower but finds cheaper paths through a much denser parse graph.
  * **2 - Deterministic parsing**. This flag guarantees that the compressed output will always be the same given the same input and parameters.
  * **3 - Extreme and deterministic parsing**.
  * **4 - Trade off decompression rate for compression ratio**. The compressor is free to use any optimizations.
  * **5 - Extreme parsing and trade off decompression rate for compression ratio**.
  * **6 - Deterministic parsing and trade off decompression rate for compression ratio**.
  * **7 - Extreme parsing, deterministic parsing and trade off decompression rate for compression ratio**.

## License
Lzham is licensed under the [MIT License](https://github.com/richgel999/lzham_codec_devel/blob/master/LICENSE).
