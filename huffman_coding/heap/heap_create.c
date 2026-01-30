#include <stdlib.h>
#include "heap.h"

heap_t *heap_create(int (*data_cmp)(void *, void *))
{
	heap_t *heap;

	if (!data_cmp)
		return (NULL);

	heap = malloc(sizeof(heap_t));
	if (!heap)
		return (NULL);

	heap->size = 0;
	heap->data_cmp = data_cmp;
	heap->root = NULL;

	return (heap);
}
