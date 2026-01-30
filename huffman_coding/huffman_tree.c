#include "huffman.h"

binary_tree_node_t *huffman_tree(char *data, size_t *freq, size_t size)
{
	heap_t *heap;

	heap = huffman_priority_queue(data, freq, size);
	if (!heap)
		return (NULL);

	while (heap->size > 1)
		huffman_extract_and_insert(heap);

	return (heap->root);
}
