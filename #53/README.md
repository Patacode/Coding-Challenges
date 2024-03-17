# CC Spell Checker

Check words spelling through **Bloom Filter**.

## Usage

The spelling checker is invoked through `ccspellcheck`:

```
Usage: ccspellcheck [options]
-h, --help                       prints this help
-b, --build DICTIONARY_FILE      Build bloom filter
-u, --use BLOOM_FILTER_FILE      Use the provided bloom filter
-v, --version VERSION_NUMBER     Set version of built bloom filter (DEFAULT: 1)
```

It is capable of building a bloom filter based on a dictionary file (some examples of valid dictionary can be found under `data/`):

```bash
./ccspellcheck -b data/dict.txt

# sample output
Number of bits used           = 1188404
Number of hash functions used = 7
It took 7.341633 seconds to build the bloom filter
```

The result is store in a binary file called `result.bf`, generated in the invoking directory.

Each `.bf` file is versioned using a single positive integer (starting from version 1 up to 2**16). To set a specific version, different than 1, use the `-v|--version` option along with the `-b|--build` option:

```bash
./ccspellcheck -b data/dict.txt -v 2

# sample output
Number of bits used           = 1188404
Number of hash functions used = 7
It took 7.341633 seconds to build the bloom filter
```

Now, using a generated bloom filter file, you can check the spelling of your words by using the `-u|--use` option:

```bash
./ccspellcheck -u result.bf one two three fowr

# sample output
Loaded from file "result.bf"
Version                       = 1
Number of bits used           = 1188404
Number of hash functions used = 7

These words are spelt wrong:
  fowr
```

The bloom filter's false positive rate is always set to `0.01` (= 1%).
