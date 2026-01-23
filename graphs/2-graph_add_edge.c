#include <stdlib.h>
#include <string.h>

#include "graphs.h"

/**
 * graph_add_edge - adds an edge between two vertices in a graph
 *
 * @graph: pointer to the graph
 * @src: string identifying the source vertex
 * @dest: string identifying the destination vertex
 * @type: UNIDIRECTIONAL or BIDIRECTIONAL
 *
 * Return: 1 on success, 0 on failure
 */
int graph_add_edge(graph_t *graph, const char *src,
                   const char *dest, edge_type_t type)
{
    vertex_t *current, *src_vertex = NULL, *dest_vertex = NULL;
    edge_t *edge_sd = NULL, *edge_ds = NULL;

    if (!graph || !src || !dest ||
        type < UNIDIRECTIONAL || type > BIDIRECTIONAL)
        return (0);

    /* Find source and destination vertices */
    current = graph->vertices;
    while (current)
    {
        if (!src_vertex && strcmp(current->content, src) == 0)
            src_vertex = current;
        else if (!dest_vertex && strcmp(current->content, dest) == 0)
            dest_vertex = current;
        current = current->next;
    }

    if (!src_vertex || !dest_vertex)
        return (0);

    /* Allocate required edges first */
    edge_sd = malloc(sizeof(edge_t));
    if (!edge_sd)
        return (0);

    if (type == BIDIRECTIONAL)
    {
        edge_ds = malloc(sizeof(edge_t));
        if (!edge_ds)
        {
            free(edge_sd);
            return (0);
        }
    }

    /* Initialize edges */
    edge_sd->dest = dest_vertex;
    edge_sd->next = src_vertex->edges;

    if (type == BIDIRECTIONAL)
    {
        edge_ds->dest = src_vertex;
        edge_ds->next = dest_vertex->edges;
    }

    /* Commit edges */
    src_vertex->edges = edge_sd;
    src_vertex->nb_edges++;

    if (type == BIDIRECTIONAL)
    {
        dest_vertex->edges = edge_ds;
        dest_vertex->nb_edges++;
    }

    return (1);
}
