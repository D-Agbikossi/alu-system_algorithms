#include <stdlib.h>

#include "graphs.h"

/**
 * graph_delete - completely deletes a graph
 *
 * @graph: pointer to the graph to delete
 */
void graph_delete(graph_t *graph)
{
    vertex_t *vertex, *next_vertex;
    edge_t *edge, *next_edge;

    if (!graph)
        return;

    vertex = graph->vertices;
    while (vertex)
    {
        next_vertex = vertex->next;

        /* Free vertex content */
        free(vertex->content);

        /* Free all edges of the vertex */
        edge = vertex->edges;
        while (edge)
        {
            next_edge = edge->next;
            free(edge);
            edge = next_edge;
        }

        /* Free vertex */
        free(vertex);
        vertex = next_vertex;
    }

    /* Free graph structure */
    free(graph);
}
