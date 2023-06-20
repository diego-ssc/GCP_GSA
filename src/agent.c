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
#include <float.h>
#include <math.h>

#include "agent.h"

#define MAX_VELOCITY 50
#define MAX_DISTANCE 100

/* The Agent structure. */
struct _Agent {
  /* The x coordinate. */
  double x;
  /* The y coordinate. */
  double y;
  /* The node. */
  int n;
  /* The comfort. */
  int comfort;
  /* The color. */
  Color* color;
  /* The Vector. */
  Vector* vector;
  /* RNG buffer. */
  struct drand48_data *buffer;
};

/* Creates a new Agent. */
Agent* agent_new(double x, double y, struct drand48_data *buffer, int n) {
  /* Heap allocation. */
  Agent* agent = malloc(sizeof(struct _Agent));

  /* Heap initialization. */
  agent->x       = x;
  agent->y       = y;
  agent->color   = 0;
  agent->comfort = 0;
  agent->buffer  = buffer;
  agent->vector  = 0;
  agent->n       = n;

  return agent;
}


/* Frees the memory used by the agent. */
void agent_free(Agent* agent) {
  if (agent->vector)
    vector_free(agent->vector);
  free(agent);
}

/* Returns the comfort of the agent. */
int agent_comfort(Agent* agent) {
  return agent->comfort;
}

/* Returns the color of the agent. */
Color* agent_color(Agent* agent) {
  return agent->color;
}

/* Returns the node of the agent. */
int agent_node(Agent* agent) {
  return agent->n;
}

/* Returns the vector of the agent. */
Vector* agent_v(Agent* agent) {
  return agent->vector;
}

/* Returns the x coordinate. */
double agent_x(Agent* agent) {
  return agent->x;
}

/* Returns the y coordinate. */
double agent_y(Agent* agent) {
  return agent->y;
}

/* Computes the vector of the agent. */
Vector* agent_vector(Agent* agent, Color** colors,
                     int color_n) {
  Color *c;
  double a, b, x, y;

  drand48_r(agent->buffer, &a);

  /* Random magnitude. */
  double r_m = MAX_DISTANCE*a;

  drand48_r(agent->buffer, &a);
  drand48_r(agent->buffer, &b);
  drand48_r(agent->buffer, &x);
  drand48_r(agent->buffer, &y);

  /* Random position. */
  Vector* r_pos = vector_new(x > 0.5 ? MAX_DISTANCE*a : MAX_DISTANCE*(-a),
                             y > 0.5 ? MAX_DISTANCE*b : MAX_DISTANCE*(-b));

  if (!agent->color) {
    c = agent_nearest_color(agent, colors, color_n);
    vector_free(r_pos);
    return s_mult(color_attraction(c, agent), agent_distance(agent, c));
  }

  if (0 == agent->comfort) {/* Leak. */
    Vector* v = s_mult(r_pos, MAX_DISTANCE*r_m);
    vector_free(r_pos);
    return v;
    }

  vector_set_x(r_pos, 0);
  vector_set_y(r_pos, 0);
  return r_pos;
}

/* Sets the vector of the agent. */
void agent_set_vector(Agent* agent, Vector* vector) {
  agent->vector = vector;
}

double agent_distance(Agent* agent, Color* color) {
  return sqrt(pow(fabs(agent->x - color_x(color)), 2) +
              pow(fabs(agent->y - color_y(color)), 2));
}

/* Sets the comfort of the agent. */
void agent_set_comfort(Agent* agent, int comfort) {
  agent->comfort = comfort;
}

/* Sets the color of the agent. */
void agent_set_color(Agent* agent, Color* color) {
  agent->color = color;
}

/* Computes the nearest color to the agent. */
Color* agent_nearest_color(Agent* agent, Color** colors,
                           int color_n) {
  int i;
  double d = DBL_MAX;
  Color* c = 0;

  for (i = 0; i < color_n; ++i) {
    if (d >= agent_distance(agent, *(colors+i))) {
      d = agent_distance(agent, *(colors+i));
      c = *(colors+i);
    }
  }

  return c;
}

/* Computes the new position of the vector. */
void agent_new_pos(Agent* agent, double d) {
  agent->x += vector_x(agent->vector);
  agent->y += vector_y(agent->vector);
  agent->x = fmod(agent->x, d);
  agent->y = fmod(agent->y, d);
}
