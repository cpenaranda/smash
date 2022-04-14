# MS-compress

## About
[MS-compress](https://github.com/coderforlife/ms-compress) is an open source implementations of Microsoft compression algorithms.

## Options
### To compress
* **Mode** - (integer, 0-2, default 0)
  * **0 - Lznt1**. Used for NTFS file compression, Windows 2000 hibernation file, Active Directory, File Replication Service, Windows Vista SuperFetch Files, and Windows Vista/7 bootmgr.
  * **1 - Xpress**. Used for Windows XP and newer hibernation file, Directory Replication Service (LDAP/RPC/AD), Windows Update Services, and Windows CE.
  * **2 - Xpress Huffman**. Xpress algorithm with Huffman encoding, used in WIM files, Distributed File System Replication, Windows 7 SuperFetch, and Windows 8 bootmgr.

### To decompress
* **Mode** - (integer, 0-2, default 0)
  * **0 - Lznt1**. Used for NTFS file compression, Windows 2000 hibernation file, Active Directory, File Replication Service, Windows Vista SuperFetch Files, and Windows Vista/7 bootmgr.
  * **1 - Xpress**. Used for Windows XP and newer hibernation file, Directory Replication Service (LDAP/RPC/AD), Windows Update Services, and Windows CE.
  * **2 - Xpress Huffman**. Xpress algorithm with Huffman encoding, used in WIM files, Distributed File System Replication, Windows 7 SuperFetch, and Windows 8 bootmgr.

## License
MS-compress is licensed under the [GNU General Public License](https://github.com/coderforlife/ms-compress/blob/master/gpl.txt).
