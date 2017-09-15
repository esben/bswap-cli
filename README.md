# bswap-cli

This project provides a simple CLI wrapper for the 3 bswap(3) functions:
bswap\_16(), bswap\_32(), and bswap\_64(), allowing for reversing the byte
order of files.

The output is zero padded if needed in order to reverse the final bytes.

## Usage

```sh
$ hexdump -C test.bin
00000000  41 42 43 44 45 46 47 48  49 4a 4b                 |ABCDEFGHIJK|
0000000b
$ bswap-16 test.bin test.bin~16
$ hexdump -C test.bin~16
00000000  42 41 44 43 46 45 48 47  4a 49 00 4b              |BADCFEHGJI.K|
0000000c
$ bswap-32 test.bin test.bin~32
$ hexdump -C test.bin~32
00000000  44 43 42 41 48 47 46 45  00 4b 4a 49              |DCBAHGFE.KJI|
0000000c
$ bswap-64 test.bin test.bin~64
$ hexdump -C test.bin~64
00000000  48 47 46 45 44 43 42 41  00 00 00 00 00 4b 4a 49  |HGFEDCBA.....KJI|
00000010
```
