#include <stdio.h>
#include "huffman.h"

static void print_codes(binary_tree_node_t *node, char *code, int depth)
{
	symbol_t *s;

	if (!node)
		return;

	s = node->data;
	if (!node->left && !node->right)
	{
		code[depth] = '\0';
		printf("%c: %s\n", s->data, code);
		return;
	}

	code[depth] = '0';
	print_codes(node->left, code, depth + 1);
	code[depth] = '1';
	print_codes(node->right, code, depth + 1);
}

int huffman_codes(char *data, size_t *freq, size_t size)
{
	binary_tree_node_t *root;
	char code[128];

	root = huffman_tree(data, freq, size);
	if (!root)
		return (0);

	print_codes(root, code, 0);
	return (1);
}
