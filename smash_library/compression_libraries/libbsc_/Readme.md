# LibBSC - High performance block-sorting data compression library

## About
[LibBSC](https://github.com/atomicobject/heatshrink) is a high performance compresion library based on lossless, block-sorting data compression algorithms.

## Options
### To compress
* **Compression level** - (integer, 1-3, default 1)
  * **3** - obtains the fastest compression.
  * **1** - obtains the highest compression ratio.
* **Window size** - (integer, 10-28, default 10)
  * Bits used to indicate the real window size used by this compression library.
* **Mode** - (integer, 1-5, default 1)
  * **1 - Block sorter Burrows–Wheeler transform**.
  * **2 - Block sorter St3**.
  * **3 - Block sorter St4**.
  * **4 - Block sorter St5**.
  * **5 - Block sorter St6**.
* **Flags** - (integer, 0-7, default 0)
  * **0 - No filter**.
  * **1 - Fast mode**.
  * **2 - Paralel mode**.
  * **3 - Fast and paralel mode**.
  * **4 - Large pages**.
  * **5 - Fast mode with large pages**.
  * **6 - Paralel mode with large pages**.
  * **7 - Fast and paralel mode with large pages**.
* **Back reference bits** - (integer, 3-8, default 3)
  * Bits used to determine the maximum length for repeated patterns that are found by this compression library.

### To decompress
* **Flags** - (integer, 0-7, default 0)
  * **0 - No filter**.
  * **1 - Fast mode**.
  * **2 - Paralel mode**.
  * **3 - Fast and paralel mode**.
  * **4 - Large pages**.
  * **5 - Fast mode with large pages**.
  * **6 - Paralel mode with large pages**.
  * **7 - Fast and paralel mode with large pages**.

## License
LibBSC is licensed under the [Apache License](https://github.com/IlyaGrebnov/libbsc/blob/master/LICENSE).
