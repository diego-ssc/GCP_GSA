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

#include "color.h"

#define NEAR_ENOUGH 4

/* The color structure */
struct _Color {
  /* The x coordinate. */
  int x;
  /* The y coordinate. */
  int y;
  /* Tells if the color was visited. */
  int c_v;
};

/* Creates a new color. */
Color* color_new(int x, int y) {
  /* Heap allocation. */
  Color* color = malloc(sizeof(struct _Color));

  /* Heap initialization. */
  color->x = x;
  color->y = x;

  return color;
}

/* Frees the memory used by the color. */
void color_free(Color* color) {
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
  Vector* vector = vector_new(0, 0);
  return vector;
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
