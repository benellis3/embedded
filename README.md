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

All benchmarking was done on a 2020 Macbook Pro (2.3 GHz 8-core Intel i9, 16GB RAM) so results may vary on your machine. To produce your
own traces you can run
```bash
xcrun xctrace record --template "Time Profiler" --launch ./hash-table
```
provided that XCode is installed.
