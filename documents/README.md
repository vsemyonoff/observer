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
Model name:                      Intel(R) Core(TM) i7-8750H CPU @ 2.20GHz
Stepping:                        10
CPU MHz:                         805.474
CPU max MHz:                     4100.0000
CPU min MHz:                     800.0000
BogoMIPS:                        4401.32
Virtualization:                  VT-x
L1d cache:                       192 KiB
L1i cache:                       192 KiB
L2 cache:                        1.5 MiB
L3 cache:                        9 MiB
```
#### Test results:
```
**> Test calls count       : 1000000000
**> Boost signal2 duration : 41463227
**> Own signal duration    : 2318948
**> Plain callback duration: 245646
**> Boost/Plain            : 168.793
**> Own/Plain              : 9.4402
**> Boost/Own              : 17.8802
```
