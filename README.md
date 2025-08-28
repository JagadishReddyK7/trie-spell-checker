
# Spell Checker, Autocomplete, Autocorrect using Trie

This program implements an efficient spell checker using a **Trie** datastructure to support three different functionalities.

---

### Approach

The solution is built around a Trie that stores the dictionary of `n` words. Each query is then processed based on its type.

1.  **Spell Check (Type 1)**: This function checks if an input string is present in the dictionary. It's implemented with a standard traversal of the Trie. If the traversal completes and the final node is marked as the end of a word, it returns '1', otherwise '0'.

2.  **Autocomplete (Type 2)**: This function finds all words in the dictionary that begin with the given input string. The code first traverses the Trie to the node representing the prefix. From that node, it performs a **Depth First Search (DFS)** to find all valid words in the sub-trie and prints them in lexicographical order.

3.  **Autocorrect (Type 3)**: This function finds all words in the dictionary that are within a **Levenshtein distance of at most 3** from the given input string. A recursive DFS explores the Trie while tracking the current edit distance. The search is pruned if the distance exceeds 3, making it efficient. The results are also printed in lexicographical order.

**Compilation Command:**

        $ g++ trie.cpp -o trie
