/*
 * This file is part of GCP_GSA.
 *
 * Copyright © 2023 Diego Sebastián Sánchez Correa
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <https://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include <stdio.h>

#include "graph.h"

/* The vertex structure. */
typedef struct _Vertex {
  /* The x coordinate. */
  double x;
  /* The y coordinate. */
  double y;
  /* The index. */
  int i;
  /* The string representation. */
  char* s;
} Vertex;

/* The graph structure. */
struct _Graph {
  /* The list of vertices. */
  Vertex** vertices;
  /* The adjacency matrix. */
  int** edges;
  /* The number of vertices. */
  int n;
  /* The RNG buffer. */
  struct drand48_data *buffer;
  /* The dimensions of the toric world. */
  double d;
};

/* Frees the adjacency matrix. */
static void free_adj_matrix(Graph*);

/* Frees the vertices. */
static void free_v(Graph*);

/* Defines the vertices. */
static void graph_n_vertices(Graph*);

/* Returns a new Graph. */
Graph* graph_new(struct drand48_data *buffer, int** edges, int n, double d) {
  /* Heap allocation. */
  Graph* graph    = malloc(sizeof(struct _Graph));
  graph->vertices = malloc(sizeof(Vertex*) * n);

  /* Heap initialization. */
  graph->n      = n;
  graph->buffer = buffer;
  graph->edges  = edges;
  graph->d      = d;

  graph_n_vertices(graph);

  return graph;
}

/* Frees the memory used by the graph. */
void graph_free(Graph* graph) {
  if (graph->edges)
    free_adj_matrix(graph);
  if (graph->vertices)
    free_v(graph);
  free(graph);
}

/* Returns a new Vertex. */
Vertex* vertex_new(double x, double y, int i) {
  /* Heap allocation. */
  Vertex* vertex = malloc(sizeof(struct _Vertex));

  /* Heap initialization. */
  vertex->x = x;
  vertex->y = y;
  vertex->i = i;
  vertex->s = malloc(sizeof(char) * 28);

  return vertex;
}

/* Returns the x coordinate of the vertex. */
double vertex_x(Vertex* vertex) {
  return vertex->x;
}

/* Returns the y coordinate of the vertex. */
double vertex_y(Vertex* vertex) {
  return vertex->y;
}

/* Returns the index of the vertex. */
double vertex_i(Vertex* vertex) {
  return vertex->i;
}

/* Frees the memory used by the vertex. */
void vertex_free(Vertex* vertex) {
  if (vertex->s)
    free(vertex->s);
  free(vertex);
}

/* Returns the string representation of the vertex. */
char* vertex_to_string(Vertex* vertex) {
  sprintf(vertex->s, "(%.2f, %.2f, %d)", vertex->x, vertex->y,
          vertex->i);
  return vertex->s;
}

/* Frees the memory used by the adjacency matrix. */
static void free_adj_matrix(Graph* graph) {
  int i;
  for (i = 0; i < graph->n; ++i)
    free(*(graph->edges + i));
  free(graph->edges);
}

/* Frees the vertices. */
static void free_v(Graph* graph) {
  int i;
  for (i = 0; i < graph->n; ++i)
    vertex_free(*(graph->vertices + i));
  free(graph->vertices);
}

/* Defines the vertices of the graph. */
static void graph_n_vertices(Graph* graph) {
  int i;
  double a, b;

  for (i = 0; i < graph->n; ++i) {
    drand48_r(graph->buffer, &a);
    drand48_r(graph->buffer, &b);
    *(graph->vertices + i) = vertex_new(graph->d * a, graph->d * b, i);
  }
}

/* Returns the vertices of the graph. */
Vertex** graph_vertices(Graph* graph) {
  return graph->vertices;
}

/* Returns the number of nodes. */
int graph_n(Graph* graph) {
  return graph->n;
}

/* Returns 1 if the two nodes are connectes; 0, otherwise. */
int graph_are_connected(Graph* graph, int n, int m) {
  return *(*(graph->edges + n) + m) == 1;
}
