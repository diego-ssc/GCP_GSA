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

#include "heuristic.h"

/**
 * Returns a new Graph.
 * @param buffer the RNG buffer.
 * @param elements the matrix of elements.
 * @param n the number of elements.
 * @param d the dimensions of the world.
 */
Graph* graph_new(struct drand48_data *buffer, int** elements, int n, double d);

/**
 * Frees the memory used by the graph.
 * @param graph the graph.
 */
void graph_free(Graph* graph);

/**
 * Returns the x coordinate of the vertex.
 * @param the vertex.
 * @return the x coordinate.
 */
double vertex_x(Vertex* vertex);

/**
 * Returns the y coordinate of the vertex.
 * @param the vertex.
 * @return the y coordinate.
 */
double vertex_y(Vertex* vertex);

/**
 * Returns the index of the vertex.
 * @param vertex the vertex.
 * @return the index.
 */
double vertex_i(Vertex* vertex);

/**
 * Returns the string representation of the vertex.
 * @param vertex the vertex.
 * @return the string representation.
 */
char* vertex_to_string(Vertex* vertex);

/**
 * Returns the vertices of the graph.
 * @param graph the graph.
 * @return the vertices.
 */
Vertex** graph_vertices(Graph* graph);

/**
 * Returns the number of nodes.
 * @param graph the graph.
 * @return the number of nodes.
 */
int graph_n(Graph* graph);

/**
 * Returns 1 if the two nodes are connectes; 0, otherwise.
 * @param graph the graph.
 * @param n the first node.
 * @param m the second node.
 */
int graph_are_connected(Graph* graph, int n, int m);
