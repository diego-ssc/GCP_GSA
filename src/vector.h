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

#pragma once

#include "heuristic.h"

/**
 * Creates a new Vector.
 * @param v_1 the first component.
 * @param v_2 the second component.
 */
Vector* vector_new(double v_1, double v_2);

/**
 * Frees the memory used by the vector.
 * @param vector the vector.
 */
void vector_free(Vector* vector);

/**
 * Computes the magnitude of the vector.
 * @param vector the vector.
 * @return the vector magnitude.
 */
double vector_magnitude(Vector* vector);

/**
 * Computes the vector angle in degrees.
 * @param vector the vector.
 * @return the vector angle.
 */
double vector_angle(Vector* vector);

/**
 * Computes the scalar multiplication.
 * @param vector the vector.
 * @param sc the scalar.
 * @return the result vector.
 */
Vector* s_mult(Vector* vector, double sc);
