# CSC

## About
[CSC](https://github.com/fusiyuan2010/CSC) is a Loss-less data compression algorithm inspired by LZMA.

## Options
### To compress
* **Compression level** - (integer, 1-5, default 1)
  * **1** - obtains the fastest compression.
  * **5** - obtains the highest compression ratio.
* **Window size** - (integer, 15-29, default 15)
  * Bits used to indicate the real window size used by this compression library.
* **Flags** - (integer, 0-7, default 0)
  * **0 - Any input**.
  * **1 - Data tables input**.
  * **2 - Executables input**.
  * **3 - Data tables and executables input**.
  * **4 - English text input**.
  * **5 - Data tables and english text input**.
  * **6 - Executables and english text input**.
  * **7 - Data tables, executables and english text input**.

## License
CSC is [unlicensed](https://github.com/fusiyuan2010/CSC/blob/master/LICENSE).

