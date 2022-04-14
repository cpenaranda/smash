# Smash: Bechmark of compression libraries

Smash is a library which present a single c++ API to use many compression libraries.

## How to compile Smash
Initially, Smash does not contain any external code. Compression libraries are added as submodules or dowloaded a tarbar or files from web when they are not able in a git repository. Also, some compression libraries can return an error if the data to compress is too small, or other situations (e.g. If you try to compress small data, the result could be data that is larger than the original data. That is why some compression libraries prefer to return an error). For that reason, some compression libraries have been modified to remove this behaviour. The idea is the user must decide if compressed data can be used.

An easy way to compile this repository is run in yout terminal the **configure** script. Warnings are shown by terminal and you can check *smash.log* when an error occurs. This script download all the compression libraries using *git* and *wget*. Also, it modifies some compression libraries code using *sed*. Finally, compile all the project using *cmake*.

```
./configure

      ___          ___          ___          ___          ___
     /\  \        /\__\        /\  \        /\  \        /\__\
    /::\  \      /::|  |      /::\  \      /::\  \      /:/  /
   /:/\:\  \    /:|:|  |     /:/\:\  \    /:/\:\  \    /:/__/
  _\:\~\:\  \  /:/|:|__|__  /::\~\:\  \  _\:\~\:\  \  /::\  \ ___
 /\ \:\ \:\__\/:/ |::::\__\/:/\:\ \:\__\/\ \:\ \:\__\/:/\:\  /\__\
 \:\ \:\ \/__/\/__/~~/:/  /\/__\:\/:/  /\:\ \:\ \/__/\/__\:\/:/  /
  \:\ \:\__\        /:/  /      \::/  /  \:\ \:\__\       \::/  /
   \:\/:/  /       /:/  /       /:/  /    \:\/:/  /       /:/  /
    \::/  /       /:/  /       /:/  /      \::/  /       /:/  /
     \/__/        \/__/        \/__/        \/__/        \/__/

                      Compression benchmark

More information in the file smash.log
Updating all submodules... [SUCCESS]
Checking compression libraries...
[SUCCESS]
Configuring building... [SUCCESS]
Compiling source... [SUCCESS]
Libraries are allocated in build/lib
Binaries are allocated in build/bin
```

## How to run Smash
This repository contains benchmarks to run Smash and allows your project to use Smash API.

<p>
<details><summary>Using Smash API</summary>
Smash API is very flexible. Different compression libraries with differents options can be chosen. Here is a code example.

``` c++
#include <smash.hpp>
#include <options.hpp>

Options options;
// Set compression library options
options.SetCompressionLevel(1);
// options.SetWindowSize(const uint32_t &window_size);
// options.SetMode(const uint8_t &mode);
// options.SetWorkFactor(const uint8_t &work_factor);
// options.SetFlags(const uint8_t &flags);
// options.SetNumberThreads(const uint8_t &number_threads);
// options.SetBackReferenceBits(const uint8_t &back_reference_bits);

uint64_t uncompress_size = 100, compressed_size = 0, decompressed_size = 0;

// Initialize uncompressed data with any information
char uncompressed_data[uncompressed_size];

// Set the compression library to use
Smash lib("zstd");

// Set options to compress
lib.SetOptionsCompressor(&options);
// Get stimated compressed data size
lib.GetCompressedDataSize(uncompressed_data, uncompressed_size, &compressed_size);
// Initialize compressed data
char compressed_data[compressed_size];
// Compress uncompressed data and the real compressed data size is taken
lib.Compress(uncompressed_data, uncompressed_size, compressed_data, &compressed_size);

// Set options to decompress
lib.SetOptionsDecompressor(&options);
// Get stimated decompressed data size
lib.GetDecompressedDataSize(compressed_data, compressed_size, &decompressed_size);
// Initialize decompressed data
char decompressed_data[decompressed_size];
// Decompress compressed data and the real decompressed data size is taken
lib.Decompress(compressed_data, compressed_size, decompressed_data, &decompressed_size);
```
</details>
</p>

<p>
<details><summary>Using Smash Benchmark</summary>
Smash benchmark is the best option if you want to discover the compression library that works best with your data. This is the list of allowed arguments:

``` bash
bin/smash_benchmark -h
To run the smash benchmark:
 bin/smash_benchmark -c <library_name> -i <name_file>

Available arguments where minimum values are used by default.
The minimum values depend on compression libraries:

 -h, --help                                  Show this message

 -h, --help <library>                        Show information about a specific library

 -a, --available_libraries                   Show a list of the available libraries

 -c, --compression_library <library_name>    Library name to use in compression/decompression

 -i, --input_file <file_name>                File name to compress

 -o, --output_file <file_name>               File name where the compress data is stored

 -e, --best_effort                           Run all possible configurations of the selected library

 -n, --repetition_number <number>            Compression and decompression are done <number> times (1 by default)

 -b, --best <option> <number>                Get the <number> configurations of the selected library
                                             with the best <option>. Available options:
                                             0: Compression ratio
                                             1: Compression time
                                             2: Decompression time
                                             3: Total time

 -l, --level <number>                        Compression level to use
                                             Values depend of different libraries

 -s, --window_size <number>                  Set window size
                                             Values depend of different libraries

 -m, --mode <number>                         Specifies the mode used
                                             Values depend of different libraries

 -w, --work_factor <number>                  Controls how the compression works with repetitive data
                                             Values depend of different libraries

 -f, --flags <number>                        Flags to use
                                             Values depend of different libraries

 -r, --back_reference_bits <number>          Number of bits used for back-reference
                                             Values depend of different libraries

 -t, --threads <number>                      Threads used in algorithms
                                             Values depend of different libraries
```
<p>
<details><summary>Running example</summary>

``` bash
bin/smash_benchmark -c all -i Makefile
| Library    | Level | Window | Mode           | WF  | Flags         | Threads | BR  | Original data | Packed data   | Ratio  | Compress    | Decompress  | Total       |
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
| zstd       | 1     | ------ | -------------- | --- | ------------- | ------- | --- | 121832 Bytes  | 10326 Bytes   | 11.80  | 579.92 MB/s | 123.24 MB/s | 414.57 MB/s |
| zpaq       | 0     | ------ | -------------- | --- | ------------- | ------- | --- | 121832 Bytes  | 12214 Bytes   | 9.97   | 54.72 MB/s  | 14.72 MB/s  | 39.86 MB/s  |
| zling      | 0     | ------ | -------------- | --- | ------------- | ------- | --- | 121832 Bytes  | 8565 Bytes    | 14.22  | 23.70 MB/s  | 11.55 MB/s  | 20.71 MB/s  |
| zlib-ng    | 0     | ------ | -------------- | --- | ------------- | ------- | --- | 121832 Bytes  | 121848 Bytes  | 1.00   | 2826.07 MB/s| 7304.16 MB/s| 2037.60 MB/s|
| zlib       | 0     | ------ | -------------- | --- | ------------- | ------- | --- | 121832 Bytes  | 121848 Bytes  | 1.00   | 1909.68 MB/s| 2146.50 MB/s| 1010.53 MB/s|
| z3lib      | ----- | ------ | -------------- | --- | None          | ------- | --- | 121832 Bytes  | 10273 Bytes   | 11.86  | 18.59 MB/s  | 49.92 MB/s  | 18.03 MB/s  |
| yalz77     | 1     | 10     | -------------- | --- | ------------- | ------- | --- | 121832 Bytes  | 15144 Bytes   | 8.04   | 298.31 MB/s | 174.43 MB/s | 246.02 MB/s |
| xpack      | 1     | ------ | -------------- | --- | ------------- | ------- | --- | 121832 Bytes  | 11725 Bytes   | 10.39  | 223.85 MB/s | 106.56 MB/s | 186.21 MB/s |
| wflz       | 0     | ------ | -------------- | --- | ------------- | ------- | --- | 121832 Bytes  | 16436 Bytes   | 7.41   | 0.56 MB/s   | 154.80 MB/s | 0.56 MB/s   |
| ucl        | 1     | ------ | NRV2B          | --- | ------------- | ------- | --- | 121832 Bytes  | 13015 Bytes   | 9.36   | 71.79 MB/s  | 56.59 MB/s  | 63.22 MB/s  |
| snappy     | ----- | ------ | -------------- | --- | ------------- | ------- | --- | 121832 Bytes  | 16994 Bytes   | 7.17   | 1182.93 MB/s| 407.33 MB/s | 841.89 MB/s |
| quicklz    | ----- | ------ | -------------- | --- | ------------- | ------- | --- | 121832 Bytes  | 15344 Bytes   | 7.94   | 747.86 MB/s | 167.36 MB/s | 478.54 MB/s |
| pithy      | 0     | ------ | -------------- | --- | ------------- | ------- | --- | 121832 Bytes  | 15302 Bytes   | 7.96   | 1267.01 MB/s| 359.63 MB/s | 878.35 MB/s |
| ms         | ----- | ------ | Lznt1          | --- | ------------- | ------- | --- | 121832 Bytes  | 22730 Bytes   | 5.36   | 58.34 MB/s  | 226.94 MB/s | 55.67 MB/s  |
| miniz      | 1     | 10     | None           | --- | ------------- | ------- | --- | 121832 Bytes  | 12949 Bytes   | 9.41   | 392.96 MB/s | 51.16 MB/s  | 216.35 MB/s |
| lzsse      | 1     | ------ | LZSSE2         | --- | ------------- | ------- | --- | 121832 Bytes  | 15083 Bytes   | 8.08   | 6.62 MB/s   | 571.56 MB/s | 6.61 MB/s   |
| lzo        | 0     | ------ | LZO1           | --- | ------------- | ------- | --- | 121832 Bytes  | 16067 Bytes   | 7.58   | 269.49 MB/s | 41.97 MB/s  | 145.93 MB/s |
| lzmat      | ----- | ------ | -------------- | --- | ------------- | ------- | --- | 121832 Bytes  | 12043 Bytes   | 10.12  | 31.94 MB/s  | 19.45 MB/s  | 27.48 MB/s  |
| lzma       | ----- | ------ | Default        | --- | ------------- | 1       | --- | 121832 Bytes  | 9456 Bytes    | 12.88  | 2.78 MB/s   | 4.86 MB/s   | 2.66 MB/s   |
| lzjb       | ----- | ------ | -------------- | --- | ------------- | ------- | --- | 121832 Bytes  | 20184 Bytes   | 6.04   | 294.29 MB/s | 62.31 MB/s  | 165.11 MB/s |
| lzham      | 0     | 15     | -------------- | --- | None          | ------- | --- | 121832 Bytes  | 11668 Bytes   | 10.44  | 2.50 MB/s   | 14.74 MB/s  | 2.46 MB/s   |
| lzfx       | ----- | ------ | -------------- | --- | ------------- | ------- | --- | 121832 Bytes  | 16030 Bytes   | 7.60   | 418.02 MB/s | 115.61 MB/s | 283.26 MB/s |
| lzfse      | ----- | ------ | -------------- | --- | ------------- | ------- | --- | 121832 Bytes  | 10318 Bytes   | 11.81  | 76.88 MB/s  | 111.67 MB/s | 72.64 MB/s  |
| lzf        | 0     | ------ | -------------- | --- | ------------- | ------- | --- | 121832 Bytes  | 17887 Bytes   | 6.81   | 466.77 MB/s | 202.74 MB/s | 348.85 MB/s |
| lz4        | 0     | ------ | Fast           | --- | ------------- | ------- | --- | 121832 Bytes  | 17543 Bytes   | 6.94   | 1078.04 MB/s| 599.92 MB/s | 856.43 MB/s |
| lodepng    | 1     | 10     | -------------- | 1   | Fast          | ------- | 1   | 121832 Bytes  | 17608 Bytes   | 6.92   | 82.16 MB/s  | 66.01 MB/s  | 69.64 MB/s  |
| lizard     | 0     | ------ | FastLZ4        | --- | ------------- | ------- | --- | 121832 Bytes  | 17726 Bytes   | 6.87   | 816.38 MB/s | 486.78 MB/s | 656.25 MB/s |
| liblzg     | 1     | ------ | -------------- | --- | ------------- | ------- | --- | 121832 Bytes  | 17106 Bytes   | 7.12   | 1.58 MB/s   | 132.05 MB/s | 1.58 MB/s   |
| libdeflate | 0     | ------ | Deflate        | --- | ------------- | ------- | --- | 121832 Bytes  | 121842 Bytes  | 1.00   | 5622.67 MB/s| 10148.43 MB/s| 3617.98 MB/s|
| libbsc     | 1     | 10     | Bwt            | --- | None          | ------- | 4   | 121832 Bytes  | 121860 Bytes  | 1.00   | 20.16 MB/s  | 1568.04 MB/s| 19.91 MB/s  |
| heatshrink | ----- | 4      | -------------- | --- | ------------- | ------- | 3   | 121832 Bytes  | 109738 Bytes  | 1.11   | 18.54 MB/s  | 31.86 MB/s  | 12.16 MB/s  |
| gipfeli    | ----- | ------ | -------------- | --- | ------------- | ------- | --- | 121832 Bytes  | 15832 Bytes   | 7.70   | 534.60 MB/s | 96.59 MB/s  | 310.95 MB/s |
| fse        | ----- | ------ | FSE            | --- | ------------- | ------- | --- | 121832 Bytes  | 77556 Bytes   | 1.57   | 224.41 MB/s | 209.55 MB/s | 133.44 MB/s |
| flzma2     | 1     | ------ | -------------- | --- | ------------- | 1       | --- | 121832 Bytes  | 9817 Bytes    | 12.41  | 20.13 MB/s  | 14.07 MB/s  | 18.05 MB/s  |
| flz        | 1     | ------ | -------------- | --- | ------------- | ------- | --- | 121832 Bytes  | 18007 Bytes   | 6.77   | 416.19 MB/s | 78.08 MB/s  | 232.79 MB/s |
| fari       | ----- | ------ | -------------- | --- | ------------- | ------- | --- | 121832 Bytes  | 23163 Bytes   | 5.26   | 23.34 MB/s  | 3.42 MB/s   | 10.16 MB/s  |
| density    | ----- | ------ | Chameleon      | --- | ------------- | ------- | --- | 121832 Bytes  | 71258 Bytes   | 1.71   | 498.68 MB/s | 541.81 MB/s | 324.17 MB/s |
| csc        | 1     | 15     | -------------- | --- | None          | ------- | --- | 121832 Bytes  | 10367 Bytes   | 11.75  | 29.93 MB/s  | 8.44 MB/s   | 22.99 MB/s  |
| c-blosc2   | 0     | ------ | -------------- | --- | None          | 1       | --- | 121832 Bytes  | 121864 Bytes  | 1.00   | 5242.57 MB/s| 7862.70 MB/s| 3145.03 MB/s|
| bzip2      | 1     | ------ | Faster         | 0   | ------------- | ------- | --- | 121832 Bytes  | 8365 Bytes    | 14.56  | 4.81 MB/s   | 2.50 MB/s   | 4.25 MB/s   |
| brotli     | 0     | 10     | Generic        | --- | ------------- | ------- | --- | 121832 Bytes  | 40594 Bytes   | 3.00   | 21.71 MB/s  | 14.13 MB/s  | 14.36 MB/s  |
| brieflz    | 1     | ------ | -------------- | --- | ------------- | ------- | --- | 121832 Bytes  | 13180 Bytes   | 9.24   | 89.72 MB/s  | 14.84 MB/s  | 54.24 MB/s  |
```
</details>
</p>

</details>
</p>

## Different options available
There are different available options in Smash, but compression libraries use some of them. Here is the list of all the available options in Smash:

| Option              | Description    |
| :---:               | :---:          |
| Compression level   | Depending on this value, compression library gets better or faster compression                 |
| Window size         | Number of bits to indicate the window size where previous uncompressed data is allocated       |
| Mode                | Compression libraries could implements different compression/decompression modes               |
| Work factor         | This option controls how the compression works with repetitive data                            |
| Flags               | Compression libraries could implements different compression/decompression flags               |
| Back reference bits | Number of bits used to indicate the reference to previous compressed data                      |
| Number of threads   | Number of threads used by the compression library                                              |

There are different ways to check the available values of these options:

<p>
<details><summary>Using Smash API</summary>
After set the compression library, these values can be obtained.

``` c++
#include <smash.hpp>

// Set the compression library to use
Smash lib("zstd");
// Get compression level values
uint8_t minimum_level = 0, maximum_level = 0;
lib.GetCompressionLevelInformation(nullptr, &minimum_level, &maximum_level);

// Get window size values
uint32_t minimum_size = 0,maximum_size = 0;
lib.GetWindowSizeInformation(nullptr, &minimum_size, &maximum_size);

// Get the available modes depending the compression level used
uint8_t minimum_mode = 0, maximum_mode = 0;
lib.GetModeInformation(nullptr, &minimum_mode, &maximum_mode, minimum_level);

// Get work factor values
uint8_t minimum_factor = 0, maximum_factor = 0;
lib.GetWorkFactorInformation(nullptr, &minimum_factor, &maximum_factor);

// Get the available flags
uint8_t minimum_flags = 0, maximum_flags = 0;
lib.GetFlagsInformation(nullptr, &minimum_flags, &maximum_flags);

// Get the available number of threads
uint8_t minimum_threads = 0, maximum_threads = 0;
lib.GetNumberThreadsInformation(nullptr, &minimum_threads, &maximum_threads);

// Get back reference bit values
uint8_t minimum_bits = 0, maximum_bits = 0;
lib.GetBackReferenceBitsInformation(nullptr,&minimum_bits, &maximum_bits);
```
</details>
</p>

<p>
<details><summary>Using Smash Benchmark</summary>
There is an argument that shows information about a specific library.

``` bash
bin/smash_benchmark -h c-blosc2
c-blosc2       - High performance compressor optimized for binary data
To run the smash benchmark:

 -i, --input_file <file_name>                File name to compress

 -o, --output_file <file_name>               File name where the compress data is stored

 -n, --repetition_number <number>            Compression and decompression are done <number> times (1 by default)

 -l, --level <number>                        Compression level to use
                                             Available values [0-9]
                                             [compression]

 -f, --flags <number>                        Flags to use
                                             Available values [0-2]
                                             0: None
                                             1: Byte
                                             2: Bit
                                             [compression]

 -t, --threads <number>                      Threads used in algorithms
                                             Available values [1-8]
                                             [compression/decompression]
```
</details>
</p>

## How to remove some compression libraries

Using **configure** script, you can specify the name of the compression libraries to remove from the build. Therefore, the command *-n* followed by the name of these compression libraries separated by spaces should be used.

## Libraries used in Smash

| Name              | Version    |
| :---:             | :---:      |
| [brieflz](https://github.com/jibsen/brieflz) | v1.3.0 |
| [brotli](https://github.com/google/brotli) | v1.0.9 |
| [bzip2](https://gitlab.com/bzip2/bzip2) | bzip2-1.0.8 |
| [c-blosc2](https://github.com/Blosc/c-blosc2) | v2.0.4 |
| [csc](https://github.com/fusiyuan2010/CSC) | commit c5dbe0944d07acbc97d2c04ec9f99a139c6f3931 |
| [density](https://github.com/k0dai/density) | density-0.14.2 |
| [fari](https://github.com/davidcatt/FastARI) | main |
| [flz](https://github.com/svn2github/fastlz) | commit 9ed1867d81a18cbda42805e7238e2dd5997dedfc |
| [flzma2](https://github.com/conor42/fast-lzma2) | v1.0.1 |
| [fse](https://github.com/Cyan4973/FiniteStateEntropy) | commit 9ba32518ad023cd4c3726fb44bba5b768ef291c8 |
| [gipfeli](https://github.com/google/gipfeli) | commit 04fe241e27f6dcfef239afc6c5e3cee0b4d7c333 |
| [heatshrink](https://github.com/atomicobject/heatshrink) | v0.4.1 |
| [libbsc](https://github.com/IlyaGrebnov/libbsc) | v3.2.4 |
| [libdeflate](https://github.com/ebiggers/libdeflate) | v1.9 |
| [liblzg](https://github.com/mbitsnbites/liblzg) | commit 182b56cb36843720f38eff2ec30db1deac4e85bd |
| [lizard](https://github.com/inikep/lizard) | v1.0 |
| [lodepng](https://github.com/lvandeve/lodepng) | commit 5601b8272a6850b7c5d693dd0c0e16da50be8d8d |
| [lz4](https://github.com/lz4/lz4) | v1.9.3 |
| [lzf](https://github.com/nemequ/liblzf) | commit fb25820c3c0aeafd127956ae6c115063b47e459a |
| [lzfse](https://github.com/lzfse/lzfse) | lzfse-1.0 |
| [lzfx](https://code.google.com/archive/p/lzfx/) | 0.1 |
| [lzham](https://github.com/richgel999/lzham_codec_devel) | commit 248325e21fc104ecaaeaafad8f13f9ad8afbf7aa |
| [lzjb](https://github.com/nemequ/lzjb) | commit 4544a180ed2ecfed8228d580253fbeaaae1fd2b4 |
| [lzma](https://tukaani.org/xz/) | v5.3.2alpha |
| [lzmat](https://github.com/nemequ/lzmat) | commit 25d9b958fff9514050a28642c99b3fff10761aac |
| [lzo](https://github.com/nemequ/lzo) | commit 0083878c235a89ef96a009d1ff0b500f3a364e4b |
| [lzsse](https://github.com/ConorStokes/LZSSE) | commit 1847c3e82794400deb56edd30d8aa3f445fd000b |
| [miniz](https://github.com/richgel999/miniz) | 2.2.0 |
| [ms](https://github.com/coderforlife/ms-compress) | commit a0fcab84a7918fa205d5f29bf03b71bd4abb19b4 |
| [pithy](https://github.com/johnezang/pithy) | commit d7d5bd3a20f97d46454f9e651ec6b3dd5801885e |
| [quicklz](https://quicklz.com/) | 1.5.0 |
| [snappy](https://github.com/google/snappy) | 1.1.9 |
| [ucl](http://www.oberhumer.com/opensource/ucl/) | 1.03 |
| [wflz](https://github.com/ShaneYCG/wflz) | commit e742c4bad7b3427fb3eeb1fc5af361af9d517a66 |
| [xpack](https://github.com/ebiggers/xpack) | v0.1 |
| [yalz77](https://bitbucket.org/tkatchev/yalz77) | commit 6810061c57dd169230808760540acb9078f53ae5 |
| [z3lib](https://scara.com/~schirmer/o/z3lib/) | 1.3 |
| [zlib](https://github.com/madler/zlib) | v1.2.11 |
| [zlib-ng](https://github.com/Dead2/zlib-ng) | 2.0.2 |
| [zling](https://github.com/richox/libzling) | 20160108 |
| [zpaq](https://github.com/zpaq/zpaq) | 7.15 |
| [zstd](https://github.com/facebook/zstd) | v1.5.2|