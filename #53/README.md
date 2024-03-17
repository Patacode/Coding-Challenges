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

It is capable of building a bloom filter based on a ditionary file (some examples of valid dictionary can be found under `data/`):

```bash
./ccspellcheck -b data/dict.txt
```

The result is store in a binary file called `result.bf`, generated in the invoking directory.

Each `.bf` file is versioned using a single positive integer (starting from version 1 up to 2**16). To set a specific version, different than 1, use the `-v|--version` option along with the `-b|--build` option:

```bash
./ccspellcheck -b data/dict.txt -v 2
```

Now, using a generated bloom filter file, you can check the spelling of your words by using the `-u|--use` option:

```bash
./ccspellcheck -u result.bf one two three
```

The bloom filter's false positive rate is always set to `0.01` (= 1%)
