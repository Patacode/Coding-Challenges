# CC WC

Simplified clone of the **wc** Unix command line tool.

- man wc
- info '(coreutils) wc invocation'

## Installation

```bash
make build
```

## Usage

Count number of bytes in given file:

```bash
./ccwc -c data/test.txt

# sample output
342190 data/test.txt
```
