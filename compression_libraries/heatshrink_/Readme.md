# Heatshrink - A data compression/decompression library for embedded/real-time systems

## About
[Heatshrink](https://github.com/atomicobject/heatshrink) is based on LZSS, since it's particularly suitable for compression in small amounts of memory. It can use an optional, small index to make compression significantly faster, but otherwise can run in under 100 bytes of memory.

## Options
### To compress
* **Window size** - (integer, 4-14, default 4)
  * Bits used to indicate the real window size used by this compression library.
* **Back reference bits** - (integer, 3-`window size`, default 3)
  * Bits used to determine the maximum length for repeated patterns that are found by this compression library.

### To decompress
* **Window size** - (integer, 4-14, default 4)
  * Bits used to indicate the real window size used by this compression library.
* **Back reference bits** - (integer, 3-`window size`, default 3)
  * Bits used to determine the maximum length for repeated patterns that are found by this compression library.

## License
Heatshrink is licensed under the [ISC License](https://github.com/atomicobject/heatshrink/blob/master/LICENSE).

