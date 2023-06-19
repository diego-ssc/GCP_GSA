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
#include <math.h>

#include "color.h"

#define NEAR_ENOUGH 4

/* The color structure. */
struct _Color {
  /* The x coordinate. */
  double x;
  /* The y coordinate. */
  double y;
  /* The identifier. */
  int id;
  /* Tells if the color was visited. */
  int c_v;
  /* The color attraction. */
  Vector* vector;
};

/* Creates a new color. */
Color* color_new(double x, double y, int id) {
  /* Heap allocation. */
  Color* color = malloc(sizeof(struct _Color));

  /* Heap initialization. */
  color->x      = x;
  color->y      = x;
  color->id     = id;
  color->c_v    = 0;
  color->vector = vector_new(0, 0);

  return color;
}

/* Frees the memory used by the color. */
void color_free(Color* color) {
  if (color->vector)
    vector_free(color->vector);
  free(color);
}

/* Returns the x coordinate of the color. */
int color_x(Color* color) {
  return color->x;
}

/* Returns the y coordinate of the color. */
int color_y(Color* color) {
  return color->y;
}

/* Returns the attraction force related to the agent. */
Vector* color_attraction(Color* color, Agent* agent) {
  vector_set_x(color->vector, color->x - agent_x(agent));
  vector_set_y(color->vector, color->y - agent_y(agent));

  return color->vector;
}

/* Returns 1 if the agent is under the influence of the color;
   0, otherwise. */
int color_in(Color* color, Agent* agent) {
  return agent_distance(agent, color) <= NEAR_ENOUGH;
}

/* Returns 1 if the color was visitied in the most recent
   operation; or 0, otherwise. */
int color_visited(Color* color) {
  return color->c_v;
}

/* Sets the status that tells if a color was visited. */
void color_set_visited(Color* color, int status) {
  color->c_v = status;
}

/* Computes the distance between two colors. */
double color_distance(Color* c_1, Color* c_2) {
  return sqrt(pow(fabs(c_1->x - c_2->x), 2) +
              pow(fabs(c_1->y - c_2->y), 2));
}

/* Tells if two colors are equal. */
int color_equals(Color* c_1, Color* c_2) {
  return c_1->id == c_2->id;
}
