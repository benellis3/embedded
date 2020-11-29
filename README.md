# Hash Table Implementation

This is a fairly simple implementation of a hash table with conflict resolution via chaining.

## Reproducing Results

To reproduce results from the report, you must first clone the repository and then run

```bash
git checkout 7e9bf3e03418a4db09f8fcdb91d373449596643e
```
Then you must change `RESIZE_THRESHOLD` in `hash_table.h` to 0.5. This is to ensure a fair comparison between the two implementations.

Then run
```bash
cd src/ && make all && ./hash-table
```

You can then run `git checkout master` and `make all && ./hash-table` to benchmark the results for the multi-element chaining table.
