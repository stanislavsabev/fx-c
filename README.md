# **fx-c**

C library with common functions and data structures 

+ `darr` - Dynamic array

String manipulation
+ `str` - String view
+ `String` - Owned string

---

## Development setup

### Prerequisites

- C compiler (gcc, clang)

- make

- criterion

```shell
 sudo apt install -y libcriterion-dev
 ```

```shell
> make
 Usage:
 make  <target>
 
 Targets:
     h help         *Show this message, default
     b build         Build static
     rb rebuild       Clean and rebuild
     bsh shared        Build shared library
     bt build-tests   Build tests
     t test          Run tests
     c clean         Clean up
     md makedirs      Create buld directories
     f format        Format with clang-format
>
```
