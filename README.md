# String Pattern Matching Algoritms
This repository contains implementations for several algorithms for solving the single and multiple string pattern matching problem. 

## Instructions

### Compile
To compile the algorithms, you can simple run
```
make [algorithm_name]
```
For instance,
```
make boyermoore
```

### Running 
To run the Single Pattern Matching Algorithm, the syntax is:
```
./[algorithm_name] [text] [pattern]
```
For instance,
```
./boyermoore rise.txt rise
```
To run the Multiple Pattern Matching Algorithms, the syntax is:
```
./[algorithm_name] [text] [patterns] [# of patterns]
```
For instance,
```
./ahoCorasick hamlet.txt patterns.txt 256
```