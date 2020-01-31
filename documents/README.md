## C++ 17 Signal/Slot library

#### TODO:
- multithreading support
- unit tests

#### Test CPU:
```
Architecture:                    x86_64
CPU op-mode(s):                  32-bit, 64-bit
Byte Order:                      Little Endian
Address sizes:                   39 bits physical, 48 bits virtual
CPU(s):                          12
On-line CPU(s) list:             0-11
Thread(s) per core:              2
Core(s) per socket:              6
Socket(s):                       1
NUMA node(s):                    1
Vendor ID:                       GenuineIntel
CPU family:                      6
Model:                           158
Model name:                      Intel(R) Core(TM) i7-8700 CPU @ 3.20GHz
Stepping:                        10
CPU MHz:                         4340.963
CPU max MHz:                     4600.0000
CPU min MHz:                     800.0000
BogoMIPS:                        6402.62
Virtualization:                  VT-x
L1d cache:                       192 KiB
L1i cache:                       192 KiB
L2 cache:                        1.5 MiB
L3 cache:                        12 MiB
```

#### Test results:
```
**> Result (MAX)           : 18446744073709551615
**> Test calls count       : 1000000000
**> Boost signal2 duration : 37406525
**> Own signal duration    : 2331969
**> Plain callback duration: 769363
**> Boost/Plain            : 48.6201
**> Own/Plain              : 3.03104
**> Boost/Own              : 16.0407
**> Result                 : 2476562500
```
