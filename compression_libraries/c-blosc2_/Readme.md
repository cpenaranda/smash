# C-Blosc2 - A fast, compressed and persistent data store library for C

## About
Blosc is a high performance compressor optimized for binary data (i.e. floating point numbers, integers and booleans). It has been designed to transmit data to the processor cache faster than the traditional, non-compressed, direct memory fetch approach via a memcpy() OS call. Blosc main goal is not just to reduce the size of large datasets on-disk or in-memory, but also to accelerate memory-bound computations.

[C-Blosc2](https://github.com/Blosc/c-blosc2) is the new major version of C-Blosc, and tries hard to be backward compatible with both the C-Blosc1 API and its in-memory format. However, the reverse thing is generally not true; buffers generated with C-Blosc2 are not format-compatible with C-Blosc1 (i.e. forward compatibility is not supported).

## Options
### To compress
* **Compression level** - (integer, 0-9, default 0)
  * **0** - obtains the fastest compression.
  * **9** - obtains the highest compression ratio.
* **Flags** - (integer, 0-2, default 0)
  * **0 - No filter**.
  * **1 - Byte-wise shuffle**.
  * **2 - Bit-wise shuffle**.
* **Threads** - (integer, 1-8, default 1)
  * Number of threads used by the compression library

### To decompress
* **Threads** - (integer, 1-8, default 1)
  * Number of threads used by the compression library

## License
C-Blosc2 is licensed under the [BSD License](https://github.com/Blosc/c-blosc2/blob/main/LICENSE.txt).

