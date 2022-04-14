# Z3lib

## About
[Z3lib](https://scara.com/~schirmer/o/z3lib/) is a substitute for the well known zlib compression library. This library provides simple interface both for memory mapped data and for files RFC 1951, RFC 1952 compliance.

## Options
### To compress
* **Flags** - (integer, 0-3, default 0)
  * **0 - No filter**.
  * **1 - Prefer longer match**.
  * **2 - Limit length**. Use with codes with lenght 3 and large distance.
  * **3 - Prefer longer match and limit length**.

## License
Z3lib is dual-licensed under the [3-clause BSD License](https://opensource.org/licenses/BSD-3-Clause) and the [GNU General Public License](https://opensource.org/licenses/gpl-license).