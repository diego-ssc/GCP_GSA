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
 * @param seedval the seed.
 * @param n_c the number of colors.
 * @param file the file.
 * @param d the graph dimension.
 * @param i the number of iterations.
 * @param c the comfort.
 * @param v verbose option.
 */
GSA* gsa_new(char* file, long int seedval, int n_c, double d,
             int i, int c, int v);

/**
 * Frees the memory used by the GSA.
 * @param gsa the gravitational search algorithm.
 */
void gsa_free(GSA* gsa);

/**
 * Creates the agents of the problem.
 * @param gsa the gravitational search algorithm.
 * @return the agents.
 */
Agent** gsa_agents(GSA* gsa);

/**
 * Creates the colors of the problem.
 * @param gsa the gravitational search algorithm.
 * @return the colors.
 */
Color** gsa_colors(GSA* gsa);

/**
 * Sets the initial conditions of the colors for
 * a new iteration.
 * @param gsa the gravitational search algorithm.
 */
void gsa_set_initial_conditions_color(GSA* gsa);

/**
 * Updates the agent vectors during the algorithm
 * iterations.
 * @param gsa the gravitational search algorithm.
 */
void gsa_agent_vectors(GSA* gsa);

/**
 * Frees the memory used by the GSA.
 * @param gsa the gravitational search algorithm.
 * @return the cost.
 */
int gsa_cost_function(GSA* gsa);

/**
 * Computes the heuristic.
 * @param gsa the gravitational search algorithm.
 * @return the solution.
 */
int gsa_heuristic(GSA* gsa);
