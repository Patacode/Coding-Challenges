# CC WC

Simplified clone of the **wc** Unix command line tool.

- man wc
- info '(coreutils) wc invocation'

## Installation

```bash
make build # compile project (create executable ./ccwc)
make test # run unit tests
make report # generate unit tests coverage report
```

## Usage

Available options:

```bash
$ ./ccwc --help

# sample output
Usage: ccwc [OPTION...] [FILENAME]
A simplified clone of wc.

  -c, --bytes                print the byte counts
  -l, --lines                print the newline counts
  -m, --chars                print the character counts
  -w, --words                print the word counts
  -?, --help                 Give this help list
      --usage                Give a short usage message
  -V, --version              Print program version

Report bugs to <maxou.info@gmail.com>.
```

Count number of bytes in given file:

```bash
$ ./ccwc -c data/test.txt

# sample output
342190 data/test.txt
```

Count number of lines in given file:

```bash
$ ./ccwc -l data/test.txt

# sample output
7145 data/test.txt
```

Count number of chars in given file:

```bash
$ ./ccwc -m data/test.txt

# sample output
339292 data/test.txt
```

Count number of words in given file:

```bash
$ ./ccwc -w data/test.txt

# sample output
58164 data/test.txt
```

You can combine multiple count flags:

```bash
$ ./ccwc -wlm data/test.txt

# sample output
7145 58164 339292 data/test.txt
```

When multiple count flags are provided, the print order will always be
lines, words, chars and then bytes count.

If no count flags are given, default to lines, words and bytes count:

```bash
$ ./ccwc data/test.txt

# sample output
7145 58164 342190 data/test.txt
```

If no file is given, default to stdin:

```bash
$ cat data/test.txt | ./ccwc

# sample output
7145 58164 342190
```
