# Stringology

## Hash
## Description

Rolling-hash algorithm

## Test Status
Used in contest. No test.


## Suffix Array
### Description

SA-IS algorithm.  
Complexity: $O(N + C)$

### Test Status

Tested on [Library Checker](https://judge.yosupo.jp/submission/69586)


## Ex SAM
### Description

Don't know how to use.

### Test Status

Copied from 8bq


## Z value
### Description

Z algorithm

### Test Status

Tested on [Library Checker](https://judge.yosupo.jp/submission/166036)

## Manacher
### Description

Find maximal palindrome for each index.

### Test Status

Tested on [Library Checker](https://judge.yosupo.jp/submission/166048)


## Lyndon Factorization
### Description

A string is called simple (or a Lyndon word), if it is strictly smaller than any of its own nontrivial suffixes.
The Lyndon factorization of the string $s$  is a factorization $s = w_1 w_2 \dots w_k$ , where all strings $w_i$  are simple, and they are in non-increasing order $w_1 \ge w_2 \ge \dots \ge w_k$.

Duval algorithm: $O(N)$.

### Test Status

Tested @ luogu 6114, 1368 & UVA 719.
Passed [Library Checker](https://judge.yosupo.jp/submission/166342)

## Main Lorentz
### Description

A repetition is two occurrences of a string in a row.
The challenge is to find all repetitions in a given string $s$.

The algorithm described here was published in 1982 by Main and Lorentz.

Time complexity: $O(N \log N)$

Every $[l, r]$ in $\text{rep}[i]$ satisfies that if $p \in [l, r]$ then $s[p,p+i) = s[p+i,p+2i)$.

### Test Status

Passed [CF 104508J](https://codeforces.com/gym/104508/submission/228069417).
This problem is prepared with this code, but some SA solutions also passes.


## BWT
### Description
Burrows-Wheeler transform is done by sorting all the circular shifts of a text in lexicographic order and by extracting the last column and the index of the original string in the set of sorted permutations of S.

Good for run-length encoding?

### Test Status

Passed UVa 632 and UVa 741

## Palindromic Tree
### Description

Check [OI Wiki](https://oi-wiki.org/string/pam/)

Don't know how to use.

### Test Status

TODO
