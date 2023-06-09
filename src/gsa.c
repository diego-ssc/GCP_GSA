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

/* The GSA structure. */
struct _GSA {
  /* RNG buffer. */
  struct drand48_data *buffer;
};

/* Creates a new GSA. */
GSA* gsa_new(Graph* graph, long int seedval) {
  /* Heap allocation. */
  GSA* gsa = malloc(sizeof(struct _GSA));

  /* RNG. */
  gsa->buffer = malloc(sizeof(struct drand48_data));
  srand48_r(seedval, gsa->buffer);

  return gsa;
}

/* Frees the memory used by the GSA. */
void gsa_free(GSA* gsa) {
  if (gsa->buffer)
    free(gsa->buffer);

  free(gsa);
}

/* Frees the memory used by the GSA. */
int gsa_cost_function(GSA* gsa) {
  return 0;
}
