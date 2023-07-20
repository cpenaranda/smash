# CPU-Smash: Compression abstraction library

CPU-Smash library presents a single C++ API to use many CPU-based compression libraries.

## References
You can access results obtained with the [AI dataset](https://github.com/cpenaranda/AI-dataset) in this [paper](https://doi.org/10.1007/978-3-031-15471-3_21). Also, if you are using this repository in your research, you need to cite the paper:
> Peñaranda, C., Reaño, C., & Silla, F. (2022, September). Smash: A Compression Benchmark with AI Datasets from Remote GPU Virtualization Systems. In International Conference on Hybrid Artificial Intelligence Systems (pp. 236-248). Cham: Springer International Publishing.

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

## How to compile CPU-Smash
CPU-Smash contains external code. Compression libraries have been added as submodules. Some compression libraries can return an error if the data to compress is too small or in other situations (e.g., if you try to compress small data, the result could be data that is larger than the original data. That is why some compression libraries prefer to return an error). Therefore, some compression libraries have been modified to remove this behavior and stored in local repositories. The idea is the user must decide if compressed data could be used.

An easy way to compile this repository is as follows:

```
git clone git@github.com:cpenaranda/smash.git
cd smash
git submodule update --init --force
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --config Release --target all
```

## How to run CPU-Smash
CPU-Smash API is very flexible. Compression libraries can be selected using different parameters. Here is a code example.

``` c++
#include <cpu_smash.hpp>
#include <cpu_options.hpp>

CpuOptions options;
// Set compression library options
options.SetCompressionLevel(1);
// options.SetWindowSize(const uint32_t &window_size);
// options.SetMode(const uint8_t &mode);
// options.SetWorkFactor(const uint8_t &work_factor);
// options.SetFlags(const uint8_t &flags);
// options.SetNumberThreads(const uint8_t &number_threads);
// options.SetBackReference(const uint8_t &back_reference);

uint64_t uncompressed_data_size = 100, compressed_data_size = 0, decompressed_data_size = 0;

// Initialize uncompressed data with any information
char uncompressed_data[uncompressed_data_size];

// Set the compression library to use
CpuSmash lib("zstd");

// Set options to compress
lib.SetOptionsCompressor(&options);
// Get estimated compressed data size
lib.GetCompressedDataSize(uncompressed_data, uncompressed_data_size, &compressed_data_size);
// Initialize compressed data
char compressed_data[compressed_data_size];
// Compress the uncompressed data, and the real compressed data size is taken
lib.Compress(uncompressed_data, uncompressed_data_size, compressed_data, &compressed_size);

// Set options to decompress
lib.SetOptionsDecompressor(&options);
// Get estimated decompressed data size
lib.GetDecompressedDataSize(compressed_data, compressed_data_size, &decompressed_data_size);
// Initialize decompressed data
char decompressed_data[decompressed_data_size];
// Decompress the compressed data, and the real decompressed data size is taken
lib.Decompress(compressed_data, compressed_data_size, decompressed_data, &decompressed_data_size);
```

## Different options available
CPU-Smash has different options, but compression libraries use only some of them. Here is the list of all the available options in CPU-Smash:

| Option              | Description    |
| :---:               | :---:          |
| Compression level   | This parameter allows to control the quality and speed of the compression data. Depending on the value, the compression can be fast but with a low compression ratio or slow with a high compression ratio. |
| Window size         | Some compression libraries use previous uncompressed information to compress data. Using this parameter, we can indicate the number of bits used to the window of that uncompressed information. For example, a value of 8 means we use a window size of 256 Bytes, which means 256 Bytes of previous uncompressed data. |
| Mode                | Compression libraries could implement different compression/decompression modes to optimize their results. Each mode uses different combinations of compression algorithms to compress and decompress data. |
| Work factor         | This option controls how the library works with reiterative data. |
| Flags               | Flags control the strategy used by the compression library. |
| Back reference      | This parameter controls the length representing repeated patterns. |
| Number of threads   | The number of threads the compression library uses. |

After setting the compression library, these values can be obtained.

``` c++
#include <cpu_smash.hpp>

// Set the compression library to use
CpuSmash lib("zstd");
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

// Get back reference values
uint8_t minimum_back_reference = 0, maximum_back_reference = 0;
lib.GetBackReferenceInformation(nullptr, &minimum_back_reference, &maximum_back_reference);
```

## Libraries used in CPU-Smash

|     |     |     | Name |     |     |     |
| :-: | :-: | :-: | :--: | :-: | :-: | :-: |
| [brieflz](https://github.com/cpenaranda/brieflz) | [brotli](https://github.com/cpenaranda/brotli) | [bzip2](https://github.com/cpenaranda/bzip2) | [c-blosc2](https://github.com/cpenaranda/c-blosc2) | [csc](https://github.com/cpenaranda/CSC) | [density](https://github.com/cpenaranda/density) | [flz](https://github.com/cpenaranda/fastlz) |
| [flzma2](https://github.com/cpenaranda/fast-lzma2) | [fse](https://github.com/cpenaranda/FiniteStateEntropy) | [gipfeli](https://github.com/cpenaranda/gipfeli) | [heatshrink](https://github.com/cpenaranda/heatshrink) | [libbsc](https://github.com/cpenaranda/libbsc) | [libdeflate](https://github.com/cpenaranda/libdeflate) | [liblzg](https://github.com/cpenaranda/liblzg) |
| [lizard](https://github.com/cpenaranda/lizard) | [lodepng](https://github.com/cpenaranda/lodepng) | [lz4](https://github.com/cpenaranda/lz4) | [lzf](https://github.com/cpenaranda/liblzf) | [lzfse](https://github.com/cpenaranda/lzfse) | [lzfx](https://github.com/cpenaranda/lzfx/) | [lzham](https://github.com/cpenaranda/lzham_codec_devel) |
| [lzjb](https://github.com/cpenaranda/lzjb) | [lzma](https://github.com/cpenaranda/xz) | [lzmat](https://github.com/cpenaranda/lzmat) | [lzo](https://github.com/cpenaranda/lzo) | [lzsse](https://github.com/cpenaranda/LZSSE) | [miniz](https://github.com/cpenaranda/miniz) | [ms](https://github.com/cpenaranda/ms-compress) |
| [pithy](https://github.com/cpenaranda/pithy) | [quicklz](https://github.com/cpenaranda/quicklz) | [snappy](https://github.com/cpenaranda/snappy) | [ucl](https://github.com/cpenaranda/ucl) | [wflz](https://github.com/cpenaranda/wflz) | [xpack](https://github.com/cpenaranda/xpack) | [yalz77](https://github.com/cpenaranda/yalz77) |
| [z3lib](https://github.com/cpenaranda/z3lib) | [zlib](https://github.com/cpenaranda/zlib) | [zlib-ng](https://github.com/cpenaranda/zlib-ng) | [zling](https://github.com/cpenaranda/libzling) | [zpaq](https://github.com/cpenaranda/zpaq) | [zstd](https://github.com/cpenaranda/zstd) | |
