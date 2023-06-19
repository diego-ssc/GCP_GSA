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

#include "gsa.h"

#define MAX_COMFORT 5
#define MAX_ITERATIONS 1000

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
  /* The distance between colors. */
  double c_d;
  /* The input parser. */
  Input_parser* parser;
  /* The number of iterations. */
  int i;
  /* The maximum comfort. */
  int c;
  /* Verbose option. */
  int v;
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
GSA* gsa_new(char* file, long int seedval, int n_c, double d,
             int i, int c, int v) {
  /* Heap allocation. */
  GSA* gsa    = malloc(sizeof(struct _GSA));

  /* RNG. */
  gsa->buffer = malloc(sizeof(struct drand48_data));
  srand48_r(seedval ? seedval : 1, gsa->buffer);
  gsa->parser = input_parser_new(file, gsa->buffer);

  /* Heap initialization. */
  gsa->graph  = input_parser_parse(gsa->parser, d ? d : 100);
  gsa->agents = gsa_agents(gsa);
  gsa->n      = graph_n(gsa->graph);
  gsa->n_c    = n_c ? n_c : gsa->n;
  gsa->colors = gsa_colors(gsa);
  gsa->c_d    = 0.1 * graph_dimension(gsa->graph);
  gsa->i      = i ? i : MAX_ITERATIONS;
  gsa->c      = c ? c : MAX_COMFORT;
  gsa->v      = v;

  return gsa;
}

/* Frees the memory used by the GSA. */
void gsa_free(GSA* gsa) {
  if (gsa->buffer)
    free(gsa->buffer);
  if (gsa->agents)
    free_agents(gsa);
  if (gsa->graph)
    graph_free(gsa->graph);
  if (gsa->colors)
    free_colors(gsa);
  if (gsa->parser)
    input_parser_free(gsa->parser);
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

  for (i = 0; i < graph_n(gsa->graph); ++i) {
    *(agents + i) = agent_new(vertex_x(*(vertices + i)),
                              vertex_y(*(vertices + i)),
                              gsa->buffer, vertex_i(*(vertices + i)));
  }

  return agents;
}

/* Creates the colors of the problem. */
Color** gsa_colors(GSA* gsa) {
  int i, j;
  double a, b;
  Color** colors = malloc(sizeof(Color*)*gsa->n_c);

  for (i = 0; i < gsa->n_c; ++i) {
    drand48_r(gsa->buffer, &a);
    drand48_r(gsa->buffer, &b);
    *(colors + i) = color_new(a * graph_dimension(gsa->graph),
                              b * graph_dimension(gsa->graph), i);
    for (j = 0; j < i; ++j) {
      while (color_distance(*(colors + i), *(colors + j)) < gsa->c_d) {
        color_free(*(colors + i));
        drand48_r(gsa->buffer, &a);
        drand48_r(gsa->buffer, &b);
        *(colors + i) = color_new(a * graph_dimension(gsa->graph),
                                  b * graph_dimension(gsa->graph), i);

        /* Check again the condition with all the colors. */
        j = 0;
      }
    }
  }

  return colors;
}

/* Sets the initial conditions of the colors for
   a new iteration. */
void gsa_set_initial_conditions_color(GSA* gsa) {
  int i;
  for (i = 0; i < gsa->n_c; ++i)
    color_set_visited(*(gsa->colors + i), 0);
}

/* Updates the agent vectors during the algorithm
   iterations. */
void gsa_agent_vectors(GSA* gsa) {
  int i;
  Vector* v, *u;
  for (i = 0; i < gsa->n; ++i) {
    v = agent_vector(*(gsa->agents + i), gsa->colors, gsa->n_c);
    if (agent_v(*(gsa->agents + i))) {
      u = vector_sum(agent_v(*(gsa->agents + i)), v);
      vector_free(agent_v(*(gsa->agents + i)));
      vector_normalize(u, graph_dimension(gsa->graph));
      agent_set_vector(*(gsa->agents + i), u);
      vector_free(v);
    } else {
      vector_free(agent_v(*(gsa->agents + i)));
      vector_normalize(v, graph_dimension(gsa->graph));
      agent_set_vector(*(gsa->agents + i), v);
    }

    agent_new_pos(*(gsa->agents + i), graph_dimension(gsa->graph));
  }
}

/* Computes the cost function. */
int gsa_cost_function(GSA* gsa) {
  int i, j = 0;
  for (i = 0; i < gsa->n; ++i)
    if (agent_color(*(gsa->agents + i)))
      ++j;

  return j;
}

int gsa_sol(GSA* gsa) {
  int i, j, s = 0;
  for (i = 0; i < gsa->n; ++i)
    for (j = 0; j < i; ++j) {
      if (color_equals(agent_color(*(gsa->agents + j)),
                       agent_color(*(gsa->agents + i))))
        continue;
      if (j == i - 1)
        s++;
    }

  return s;
}

/* Sets the related color of the agents. */
void gsa_color(GSA* gsa) {
  int i, j;
  for (i = 0; i < gsa->n; ++i)
    for (j = 0; j < gsa->n_c; ++j)
      if (color_in(*(gsa->colors + j), *(gsa->agents + i)))
        agent_set_color(*(gsa->agents + i), *(gsa->colors + j));
}

/* Computes the heuristic. */
int gsa_heuristic(GSA* gsa) {
  int a = gsa->i;

  while ((gsa_cost_function(gsa) != gsa->n) && --a) {
    gsa_agent_vectors(gsa);
    gsa_color(gsa);
    comfort(gsa);
    gsa_set_initial_conditions_color(gsa);
  }

  if (gsa->v) {
    for (int i = 0; i < gsa->n; ++i) {
      printf("Agent:\nx: %f\ny: %f\n",
             agent_x(*(gsa->agents + i)),
             agent_y(*(gsa->agents + i)));
    }

    for (int i = 0; i < gsa->n_c; ++i) {
      printf("Color:\nx: %f\ny: %f\n",
             color_x(*(gsa->colors + i)),
             color_y(*(gsa->colors + i)));
    }
    printf("Cost function: %d\n", gsa_cost_function(gsa));
  }

  if (!a) {
    printf("GCP_GSA: A solution could not be found\n");
    exit(1);
  }
  return gsa_sol(gsa);
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
  for (i = 0; i < gsa->n; ++i)
    if (agent_color(*(gsa->agents + i)))
      if (!color_visited(agent_color(*(gsa->agents + i))))
        agent_set_comfort(*(gsa->agents + i), agent_comfort(*(gsa->agents + i)) == gsa->c ?
                          agent_comfort(*(gsa->agents + i)) : agent_comfort(*(gsa->agents + i)) + 1);
}
