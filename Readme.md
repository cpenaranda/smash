# Smash: Compression abstraction library

Smash is a library that presents a single c++ API to use many compression libraries.

## References
You can access results obtained with the [AI dataset](https://github.com/cpenaranda/AI-dataset) in this [paper](https://doi.org/10.1007/978-3-031-15471-3_21). Also, if you are using this repository in your research, you need to cite the paper:
> Peñaranda, C., Reaño, C., Silla, F. (2022). Smash: A Compression Benchmark with AI Datasets from Remote GPU Virtualization Systems. In: , et al. Hybrid Artificial Intelligent Systems. HAIS 2022. Lecture Notes in Computer Science(), vol 13469. Springer, Cham. https://doi.org/10.1007/978-3-031-15471-3_21

<details><summary>BibTeX</summary>

```
@InProceedings{penaranda2022smash,
  author="Pe{\~{n}}aranda, Cristian and Rea{\~{n}}o, Carlos and Silla, Federico",
  editor="Garc{\'i}a Bringas, Pablo and P{\'e}rez Garc{\'i}a, Hilde and Mart{\'i}nez de Pis{\'o}n, Francisco Javier and Villar Flecha, Jos{\'e} Ram{\'o}n and Troncoso Lora, Alicia and de la Cal, Enrique A. and Herrero, {\'A}lvaro and Mart{\'i}nez {\'A}lvarez, Francisco and Psaila, Giuseppe and Quinti{\'a}n, H{\'e}ctor and Corchado, Emilio",
  title="Smash: A Compression Benchmark with AI Datasets from Remote GPU Virtualization Systems",
  booktitle="Hybrid Artificial Intelligent Systems",
  year="2022",
  publisher="Springer International Publishing",
  address="Cham",
  pages="236--248",
  abstract="Remote GPU virtualization is a mechanism that allows GPU-accelerated applications to be executed in computers without GPUs. Instead, GPUs from remote computers are used. Applications are not aware of using a remote GPU. However, overall performance depends on the throughput of the underlying network connecting the application to the remote GPUs. One way to increase this bandwidth is to compress transmissions made within the remote GPU virtualization middleware between the application side and the GPU side.",
  isbn="978-3-031-15471-3"
}
```

</details>

## How to compile Smash
Smash contains external code. Compression libraries have been added as submodules. Some compression libraries can return an error if the data to compress is too small, or in other situations (e.g. If you try to compress small data, the result could be data that is larger than the original data. That is why some compression libraries prefer to return an error). For that reason, some compression libraries have been modified to remove this behavior and have been stored in local repositories. The idea is the user must decide if compressed data could be used.

An easy way to compile this repository is:

```
git clone git@github.com:cpenaranda/smash.git
cd smash
git submodule update --init --force
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --config Release --target all
```

## How to run Smash
Smash API is very flexible. Compression libraries can be selected using different parameters. Here is a code example.

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
// Get estimated compressed data size
lib.GetCompressedDataSize(uncompressed_data, uncompressed_size, &compressed_size);
// Initialize compressed data
char compressed_data[compressed_size];
// Compress the uncompressed data, and the real compressed data size is taken
lib.Compress(uncompressed_data, uncompressed_size, compressed_data, &compressed_size);

// Set options to decompress
lib.SetOptionsDecompressor(&options);
// Get estimated decompressed data size
lib.GetDecompressedDataSize(compressed_data, compressed_size, &decompressed_size);
// Initialize decompressed data
char decompressed_data[decompressed_size];
// Decompress the compressed data, and the real decompressed data size is taken
lib.Decompress(compressed_data, compressed_size, decompressed_data, &decompressed_size);
```

## Different options available
There are different options in Smash, but compression libraries use only some of them. Here is the list of all the available options in Smash:

| Option              | Description    |
| :---:               | :---:          |
| Compression level   | Depending on this value, compression library gets better or faster compression                 |
| Window size         | Number of bits to indicate the window size where previous uncompressed data is allocated       |
| Mode                | Compression libraries could implements different compression/decompression modes               |
| Work factor         | This option controls how the compression works with repetitive data                            |
| Flags               | Compression libraries could implements different compression/decompression flags               |
| Back reference bits | Number of bits used to indicate the reference to previous compressed data                      |
| Number of threads   | Number of threads used by the compression library                                              |

After setting the compression library, these values can be obtained.

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

// Get the available modes depending on the compression level used
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

## Libraries used in Smash

|     |     |     | Name |     |     |     |
| :-: | :-: | :-: | :--: | :-: | :-: | :-: |
| [brieflz](https://github.com/cpenaranda/brieflz) | [brotli](https://github.com/cpenaranda/brotli) | [bzip2](https://github.com/cpenaranda/bzip2) | [c-blosc2](https://github.com/cpenaranda/c-blosc2) | [csc](https://github.com/cpenaranda/CSC) | [density](https://github.com/cpenaranda/density) | [flz](https://github.com/cpenaranda/fastlz) |
| [flzma2](https://github.com/cpenaranda/fast-lzma2) | [fse](https://github.com/cpenaranda/FiniteStateEntropy) | [gipfeli](https://github.com/cpenaranda/gipfeli) | [heatshrink](https://github.com/cpenaranda/heatshrink) | [libbsc](https://github.com/cpenaranda/libbsc) | [libdeflate](https://github.com/cpenaranda/libdeflate) | [liblzg](https://github.com/cpenaranda/liblzg) |
| [lizard](https://github.com/cpenaranda/lizard) | [lodepng](https://github.com/cpenaranda/lodepng) | [lz4](https://github.com/cpenaranda/lz4) | [lzf](https://github.com/cpenaranda/liblzf) | [lzfse](https://github.com/cpenaranda/lzfse) | [lzfx](https://github.com/cpenaranda/lzfx/) | [lzham](https://github.com/cpenaranda/lzham_codec_devel) |
| [lzjb](https://github.com/cpenaranda/lzjb) | [lzma](https://github.com/cpenaranda/xz) | [lzmat](https://github.com/cpenaranda/lzmat) | [lzo](https://github.com/cpenaranda/lzo) | [lzsse](https://github.com/cpenaranda/LZSSE) | [miniz](https://github.com/cpenaranda/miniz) | [ms](https://github.com/cpenaranda/ms-compress) |
| [pithy](https://github.com/cpenaranda/pithy) | [quicklz](https://github.com/cpenaranda/quicklz) | [snappy](https://github.com/cpenaranda/snappy) | [ucl](https://github.com/cpenaranda/ucl) | [wflz](https://github.com/cpenaranda/wflz) | [xpack](https://github.com/cpenaranda/xpack) | [yalz77](https://github.com/cpenaranda/yalz77) |
| [z3lib](https://github.com/cpenaranda/z3lib) | [zlib](https://github.com/cpenaranda/zlib) | [zlib-ng](https://github.com/cpenaranda/zlib-ng) | [zling](https://github.com/cpenaranda/libzling) | [zpaq](https://github.com/cpenaranda/zpaq) | [zstd](https://github.com/cpenaranda/zstd) | |