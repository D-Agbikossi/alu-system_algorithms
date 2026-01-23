#include <stdlib.h>
#include <string.h>

#include "graphs.h"

/**
 * bfs_queue - queue structure for BFS
 */
typedef struct bfs_queue
{
    const vertex_t *vertex;
    size_t depth;
    struct bfs_queue *next;
} bfs_queue_t;

/**
 * breadth_first_traverse - traverses a graph using breadth-first search
 *
 * @graph: pointer to the graph
 * @action: function to call for each visited vertex
 *
 * Return: biggest vertex depth, or 0 on failure
 */
size_t breadth_first_traverse(const graph_t *graph,
                              void (*action)(const vertex_t *v, size_t depth))
{
    unsigned char *visited;
    bfs_queue_t *head = NULL, *tail = NULL, *node;
    edge_t *edge;
    size_t max_depth = 0;

    if (!graph || !graph->vertices || !action)
        return (0);

    visited = calloc(graph->nb_vertices, sizeof(unsigned char));
    if (!visited)
        return (0);

    /* Initialize queue with first vertex */
    head = malloc(sizeof(bfs_queue_t));
    if (!head)
    {
        free(visited);
        return (0);
    }

    head->vertex = graph->vertices;
    head->depth = 0;
    head->next = NULL;
    tail = head;

    while (head)
    {
        node = head;
        head = head->next;

        if (!visited[node->vertex->index])
        {
            visited[node->vertex->index] = 1;
            action(node->vertex, node->depth);

            if (node->depth > max_depth)
                max_depth = node->depth;

            edge = node->vertex->edges;
            while (edge)
            {
                if (!visited[edge->dest->index])
                {
                    bfs_queue_t *new = malloc(sizeof(bfs_queue_t));
                    if (!new)
                    {
                        free(node);
                        free(visited);
                        while (head)
                        {
                            node = head;
                            head = head->next;
                            free(node);
                        }
                        return (0);
                    }

                    new->vertex = edge->dest;
                    new->depth = node->depth + 1;
                    new->next = NULL;

                    tail->next = new;
                    tail = new;
                }
                edge = edge->next;
            }
        }

        free(node);
    }

    free(visited);
    return (max_depth);
}
