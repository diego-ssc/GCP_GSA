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

#include "vector.h"

/* The Vector structure. */
struct _Vector {
  /* The first component. */
  double v_1;
  /* The second component. */
  double v_2;
};

/* Creates a new Vector. */
Vector* vector_new(double v_1, double v_2) {
  /* Heap allocation. */
  Vector* vector = malloc(sizeof(struct _Vector));

  /* Heap initialization. */
  vector->v_1 = v_1;
  vector->v_2 = v_2;

  return vector;
}

/* Frees the memory used by the vector. */
void vector_free(Vector* vector) {
  free(vector);
}

/* Computes the magnitude of the vector. */
double vector_magnitude(Vector* vector) {
  return sqrt(pow(vector->v_1, 2) + pow(vector->v_2, 2));
}

/* Computes the vector angle in degrees. */
double vector_angle(Vector* vector) {
  return cosh(vector->v_1 / vector_magnitude(vector));
}

/* Computes the scalar multiplication. */
Vector* s_mult(Vector* vector, double sc) {
  return vector_new(vector->v_1 * sc,
                    vector->v_2 * sc);
}

/* Computes the sum between two vectors. */
Vector* vector_sum(Vector* vector_1, Vector* vector_2) {
  return vector_new(vector_1->v_1 + vector_2->v_1,
                    vector_1->v_2 + vector_2->v_2);
}

/* Returns the first component of the vector. */
double vector_x(Vector* vector) {
  return vector->v_1;
}

/* Returns the second component of the vector. */
double vector_y(Vector* vector) {
  return vector->v_2;
}

/* Sets the first component of the vector. */
void vector_set_x(Vector* vector, double v_1) {
  vector->v_1 = v_1;
}

/* Sets the second component of the vector. */
void vector_set_y(Vector* vector, double v_2) {
  vector->v_2 = v_2;
}

/* Normalizes the vector to fit the toric world. */
void vector_normalize(Vector* vector, double d) {
  vector->v_1 = (int)vector->v_1 % (int)d;
  vector->v_2 = (int)vector->v_2 % (int)d;
}
