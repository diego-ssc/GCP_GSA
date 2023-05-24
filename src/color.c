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

#include "heuristic.h"

/* The color structure */
struct _Color {
  /* The x coordinate. */
  int x;
  /* The y coordinate. */
  int y;
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
