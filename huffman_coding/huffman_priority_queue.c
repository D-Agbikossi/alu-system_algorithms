#include <stdlib.h>
#include "huffman.h"

static int symbol_cmp(void *a, void *b)
{
	binary_tree_node_t *na = a;
	binary_tree_node_t *nb = b;
	symbol_t *sa = na->data;
	symbol_t *sb = nb->data;

	return ((int)(sa->freq - sb->freq));
}

heap_t *huffman_priority_queue(char *data, size_t *freq, size_t size)
{
	heap_t *heap;
	binary_tree_node_t *node;
	symbol_t *symbol;
	size_t i;

	if (!data || !freq || size == 0)
		return (NULL);

	heap = heap_create(symbol_cmp);
	if (!heap)
		return (NULL);

	for (i = 0; i < size; i++)
	{
		symbol = symbol_create(data[i], freq[i]);
		node = binary_tree_node(NULL, symbol);
		heap_insert(heap, node);
	}

	return (heap);
}
