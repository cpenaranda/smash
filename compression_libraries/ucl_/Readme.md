# UCL

## About
[UCL](http://www.oberhumer.com/opensource/ucl/) is a portable lossless data compression library written in ANSI C. UCL implements a number of compression algorithms that achieve an excellent compression ratio while allowing *very* fast decompression. Also, decompression requires no additional memory.

## Options
### To compress
* **Compression level** - (integer, 1-10, default 1)
  * **0** - obtains the fastest compression.
  * **10** - obtains the highest compression ratio.
* **Mode** - (integer, 0-2, default 0)
  * **0 - NRV2B** algorithm.
  * **1 - NRV2D** algorithm.
  * **2 - NRV2E** algorithm.

### To decompress
* **Mode** - (integer, 0-2, default 0)
  * **0 - NRV2B** algorithm.
  * **1 - NRV2D** algorithm.
  * **2 - NRV2E** algorithm.

## License
UCL is licensed under the [GNU General Public License](http://www.oberhumer.com/opensource/gpl.html).