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

#include "gsa.h"

#define MAX_COMFORT 5

/* The GSA structure. */
struct _GSA {
  /* RNG buffer. */
  struct drand48_data *buffer;
  /* The agents. */
  Agent** agents;
  /* The graph. */
  Graph* graph;
  /* The number of agents. */
  int n;
  /* The colors. */
  Color** colors;
  /* The number of colors. */
  int n_c;
};

/* Frees the agents. */
static void free_agents(GSA*);

/* Frees the colors. */
static void free_colors(GSA*);

/* Computes the repulsion induced to an agent. */
static int repulsion(GSA*, Agent*);

/* Computes the comfort for all the agents in a specific iteration. */
static void comfort(GSA*);

/* Creates a new GSA. */
GSA* gsa_new(Graph* graph, long int seedval, int n_c) {
  /* Heap allocation. */
  GSA* gsa = malloc(sizeof(struct _GSA));

  /* RNG. */
  gsa->buffer = malloc(sizeof(struct drand48_data));
  srand48_r(seedval, gsa->buffer);

  /* Heap initialization. */
  gsa->graph  = graph;
  gsa->agents = gsa_agents(gsa);
  gsa->n      = graph_n(graph);
  gsa->n_c    = n_c;
  gsa->colors = malloc(sizeof(Color*)*gsa->n_c);
  
  return gsa;
}

/* Frees the memory used by the GSA. */
void gsa_free(GSA* gsa) {
  if (gsa->buffer)
    free(gsa->buffer);
  if (gsa->graph)
    graph_free(gsa->graph);
  if (gsa->agents)
    free_agents(gsa);
  if (gsa->colors)
    free_colors(gsa);
  free(gsa);
}

/* Frees the agents. */
static void free_agents(GSA* gsa) {
  int i;
  for (i = 0; i < graph_n(gsa->graph); ++i)
    agent_free(*(gsa->agents + i));
  free(gsa->agents);
}

/* Frees the colors. */
static void free_colors(GSA* gsa) {
  int i;
  for (i = 0; i < gsa->n_c; ++i)
    color_free(*(gsa->colors + i));
  free(gsa->colors);
}

/* Creates the agents of the problem. */
Agent** gsa_agents(GSA* gsa) {
  Vertex** vertices = graph_vertices(gsa->graph);
  Agent** agents = malloc(sizeof(Agent*)* graph_n(gsa->graph));
  int i;

  for (i = 0; i < graph_n(gsa->graph); ++i)
    *(agents + i) = agent_new(vertex_x(*(vertices + i)),
                              vertex_y(*(vertices + i)),
                              gsa->buffer);

  return agents;
}

/* Creates the colors of the problem. */
Color** gsa_colors(GSA* gsa) {
  gsa->n_c;
}

/* Computes the cost function. */
int gsa_cost_function(GSA* gsa) {
  int i, j = 0;
  for (i = 0; i < gsa->n; ++i)
    if (agent_color(*(gsa->agents + i)))
      ++j;

  return j;
}

/* Computes the heuristic. */
void gsa(GSA* gsa) {
  
  
  while (gsa_cost_function(gsa) != gsa->n) {
    comfort(gsa);
  }
}

/* Computes the repulsion induced to an agent. */
static int repulsion(GSA* gsa, Agent* agent) {
  int i, r = 0;
  if (!agent_color(agent))
    return 0;
  Color* c = agent_color(agent);

  for (i = 0; i < gsa->n; ++i)
    if (color_in(c, *(gsa->agents + i)) &&
        graph_are_connected
        (gsa->graph, agent_node(*(gsa->agents + i)),
         agent_node(agent))) {
      r++;
      color_set_visited(c, 1);
    }

  return r;
}

/* Computes the comfort for all the agents in a specific iteration. */
static void comfort(GSA* gsa) {
  int i, j;
  for (i = 0; i < gsa->n; ++i)
    for (j = i+1; j < gsa->n; ++j)
      if (graph_are_connected(gsa->graph,
                              agent_node(*(gsa->agents + i)),
                              agent_node(*(gsa->agents + j))) &&
          repulsion(gsa, *(gsa->agents + i)) > 0)
        agent_comfort(*(gsa->agents + j)) > 0 ?
          agent_set_comfort(*(gsa->agents + j),
                            agent_comfort(*(gsa->agents + j)) - 1) : 0;
}
