#include <stdlib.h>
#include <string.h>

#include "graphs.h"

/**
 * dfs_recursive - recursive helper for depth-first traversal
 *
 * @vertex: current vertex
 * @visited: array tracking visited vertices
 * @depth: current depth
 * @action: function to apply to each visited vertex
 *
 * Return: maximum depth reached
 */
static size_t dfs_recursive(const vertex_t *vertex,
                            unsigned char *visited,
                            size_t depth,
                            void (*action)(const vertex_t *, size_t))
{
    edge_t *edge;
    size_t max_depth = depth;
    size_t child_depth;

    if (!vertex || visited[vertex->index])
        return (depth);

    visited[vertex->index] = 1;
    action(vertex, depth);

    edge = vertex->edges;
    while (edge)
    {
        if (!visited[edge->dest->index])
        {
            child_depth = dfs_recursive(edge->dest,
                                        visited,
                                        depth + 1,
                                        action);
            if (child_depth > max_depth)
                max_depth = child_depth;
        }
        edge = edge->next;
    }

    return (max_depth);
}

/**
 * depth_first_traverse - traverses a graph using depth-first search
 *
 * @graph: pointer to the graph
 * @action: function to call for each visited vertex
 *
 * Return: biggest vertex depth, or 0 on failure
 */
size_t depth_first_traverse(const graph_t *graph,
                            void (*action)(const vertex_t *v, size_t depth))
{
    unsigned char *visited;
    size_t max_depth;

    if (!graph || !graph->vertices || !action)
        return (0);

    visited = calloc(graph->nb_vertices, sizeof(unsigned char));
    if (!visited)
        return (0);

    max_depth = dfs_recursive(graph->vertices, visited, 0, action);

    free(visited);
    return (max_depth);
}
