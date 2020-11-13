This project is a realization of the Trie class and the Aho-Korasick algorithm.
The algorithm finds all the patterns in the text in a single pass.
The Trie constructs from a list of patterns and represents a prefix tree. It has two user methods: "Go" and "GetTerminals". "Go" moves to the next condition according to the given next symbol of the text. "GetTerminals" returns the indexes of the patterns which end at this position in the text.
The example of use is provided in the main function.

