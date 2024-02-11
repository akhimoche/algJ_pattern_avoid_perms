# Pattern Avoiding Permutations via Algorithm J

## Description

Generate zig-zag permutation language via pattern avoiding permutations. Using 'Algorithm J' to create combinatorial objects, paying particular attention to the ordering of the jumps performed in the algorithm as these constitute permutation languages (see 'Context').

## Theory

Without selecting a substring to avoid, the resultant permutation generation order is consistent with Steinhaus-Johnson-Trotter Ordering. By selecting certain patterns to avoid of a particular type, families of combinatorial objects such as Catalan and Bell families are generated.

## Computation

This algorithm can apply for vincular and non-vincular patterns of limited length. The maximum size of vincular pattern within input substring is 2, an extension of this code could be written for arbitrary length of substring & vincular pattern to avoid and length of the string to be moved. 

## Analysis

The code above is able to generate all possible permutations consistent with SJT ordering. 

## Context
The algorithm pseudocode is laid out in the papers below, along with the respective families of combinatorial objects Algorithm J can generate. 

1. https://arxiv.org/abs/1906.06069
2. https://arxiv.org/abs/2103.09333
