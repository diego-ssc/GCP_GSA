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
 * Creates a new GSA.
 * @param graph the graph.
 */
GSA* gsa_new(Graph* graph);

/**
 * Frees the memory used by the GSA.
 * @param gsa the gravitational search algorithm.
 */
void gsa_free(GSA* gsa);

/**
 * Frees the memory used by the GSA.
 * @param gsa the gravitational search algorithm.
 * @return the cost.
 */
int gsa_cost_function(GSA* gsa);
