# Lzf
Author: [Marc Lehmann](schmorp@schmorp.de)
[Official website](http://software.schmorp.de/pkg/liblzf)

## About
[Lzf](https://github.com/nemequ/liblzf) is an extremely fast (not that much slower than a pure memcpy) compression algorithm. It is ideal for applications where you want to save *some* space but not at the cost of speed. It is ideal for repetitive data as well.

## Options
### To compress
* **Compression level** - (integer, 0-1, default 0)
  * **0** - obtains the fastest compression.
  * **1** - obtains the highest compression ratio.

## License
Lzf is released under the terms of the license contained in the [file](https://github.com/nemequ/liblzf/blob/master/LICENSE).
