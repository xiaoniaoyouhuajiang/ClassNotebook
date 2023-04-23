# Task
[Solution](https://leetcode.com/problems/3sum/description/)

Given an array S of n integers, are there elements a, b, c in S such that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero.

Note: The solution set must not contain duplicate triplets.

```
For example, given array S = [-1, 0, 1, 2, -1, -4],

A solution set is:
[
  [-1, 0, 1],
  [-1, -1, 2]
]
```

# [Presentation](../../docs/04.3sum.pdf)

# Solutions
* Time complexity: `O(n!)`. [Solution](gorunov1.cpp).
Shortest solution. Implementation is based on permutations.
* Time complexity: `O(n^4)`.
Implementation is based on permutations. Use additional binary array (size is equal to original array) with only 3 elements equal to 1. Custom permutation implementation can reduce complexity to `O(n^3)`.
* Time complexity: `O(n^2 * log n)`. [Solution](banin.cpp).
Brute-force through pairs of values, find a third one with binary search. Asymptote is `O(n^2 * log^2 n)` due to deduplicating returns by storing them into a `std::set`. Input sequence is left uncompressed.
* Time complexity: `O(n^2 * log n)`. [Solution](gritsenko.cpp).
Sort the array, consider all pairs (one iterator is set to the begin and the second iterator is set to the end), find the third element for triplet with binary_search between iterators. If iterator is moved to the repeated value, skip it.  
* Time complexity: `O(n^2 * log n)`. [Solution](sidnev_bin_search.cpp).
Sort the array and reduce task to 2-sum problem. Move first pointer `k` from left to right and solve 2-sum problem for other elements: `[i] + [j] = -[k]`. Move pointers `i` and `j` with binary search.
* Time complexity: `O(n^2)`. [Solution](barinova.cpp).
  1. Sort input array.
  2. Obtain 2 vectors from input one: first contains sorted unique elements, second - counts of corresponding elements in input vector.
  3. Additional vector 'max_corresp_candidat_idx' for storage min checked third triple element index for a second element in triplet (initialized with nums.size() - 1).
  4. Check triplets of elements with 3 indices:
  idx[0] is increasing from min element index to max negative index,
  idx[1] is increasing from idx[0] and stops increasing when triplets is found or when idx[1] == idx[2],
  idx[2] is decreasing from max_corresp_candidat_idx[idx[1]] and stops decreasing when triples is found or when idx[1] == idx[2].
* Time complexity: `O(n^2)`. [Solution](sidnev_unordered_map.cpp), [faster std::unordered_map solution](Ruslan_Arutyunyan.cpp).
Use `std::unorderd_map` to store elements and their quantity. Two loops iterate over elements `i` and `j`. The third element `-[i] -[j]` is found in the `unordered_map`.
* Time complexity: `O(n^2)`. [Solution](sidnev.cpp).
Sort the array and reduce task to 2-sum problem. Move first pointer `k` from left to right and solve 2-sum problem for other elements: `[i] + [j] = -[k]`.
