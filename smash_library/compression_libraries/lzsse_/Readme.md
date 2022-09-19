# LZSSE

## About
[LZSSE](https://github.com/ConorStokes/LZSSE) is designed for SSE based decompression.

## Options
### To compress
* **Compression level** - (integer, 1-17, default 1)
  * **1** - obtains the fastest compression.
  * **17** - obtains the highest compression ratio.
* **Mode** - (integer, 0-2, default 0)
  * **0 - LZSSE2**. Use with high compression files with small literal runs.
  * **1 - LZSSE4**. Use with a more balanced mix of literals and matches.
  * **2 - LZSSE8**. Use with lower compression data with longer runs of matches.

### To decompress
* **Mode** - (integer, 0-2, default 0)
  * **0 - LZSSE2**. Use with high compression files with small literal runs.
  * **1 - LZSSE4**. Use with a more balanced mix of literals and matches.
  * **2 - LZSSE8**. Use with lower compression data with longer runs of matches.

## License
LZSSE is licensed under the [2-Clause BSD License](https://github.com/ConorStokes/LZSSE/blob/master/LICENSE).
