#include <stdlib.h>
#include "huffman.h"

int huffman_extract_and_insert(heap_t *priority_queue)
{
	binary_tree_node_t *a, *b, *node;
	symbol_t *sa, *sb, *s;

	if (!priority_queue || priority_queue->size < 2)
		return (0);

	a = heap_extract(priority_queue);
	b = heap_extract(priority_queue);

	sa = a->data;
	sb = b->data;

	s = symbol_create(-1, sa->freq + sb->freq);
	node = binary_tree_node(NULL, s);
	node->left = a;
	node->right = b;
	a->parent = node;
	b->parent = node;

	heap_insert(priority_queue, node);
	return (1);
}
