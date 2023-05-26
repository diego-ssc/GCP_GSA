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

#include "agent.h"

/* The Agent structure. */
struct _Agent {
  /* The x coordinate. */
  int x;
  /* The y coordinate. */
  int y;
  /* The comfort. */
  int comfort;
  /* The color. */
  Color* color;
};

/* Creates a new Agent. */
Agent* agent_new(int x, int y) {
  /* Heap allocation. */
  Agent* agent = malloc(sizeof(struct _Agent));

  /* Heap initialization. */
  agent->x       = x;
  agent->y       = y;
  agent->color   = 0;
  agent->comfort = 0;

  return agent;
}


/* Frees the memory used by the agent. */
void agent_free(Agent* agent) {
  free(agent);
}

/* Returns the comfort of the agent. */
int agent_comfort(Agent* agent) {
  return comfort;
}

/* Returns the color of the agent. */
Color* agent_color(Agent* agent) {
  return agent->color;
}

/* Computes the velocity of the agent. */
double agent_velocity(Agent* agent, Color** colors,
                      int color_n) {
  Colot *c;

  if (!agent->agent) {
    c = agent_nearest_color(agent, colors, color_n);
    return agent_distance(agent, c) * color_attraction(color, agent);
  }

  return 0;
}

double agent_distance(Agent* agent, Color* color) {
  return sqrt(pow(fabs(agent->x - color_x(color)), 2) +
              pow(fabs(agent->y - color_y(color)), 2));
}

Color* agent_nearest_color(Agent* agent, Color** colors,
                           int color_n) {
  int i;
  double d = DBL_MAX;
  Color* c;

  for (i = 0; i < color_n; ++i) {
    if (d >= agent_distance(agent, *(colors+i))) {
      d = agent_distance(agent, *(colors+i));
      c = *(colors+i);
    }
  }

  return c;
}
