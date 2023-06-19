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
 * Creates a new Agent.
 * @param x the x coordinate.
 * @param y the y coordinate.
 * @param buffer the RNG buffer.
 * @param n the node.
 */
Agent* agent_new(double x, double y, struct drand48_data *buffer, int n);

/**
 * Frees the memory used by the agent.
 * @param agent the agent.
 */
void agent_free(Agent* agent);

/**
 * Computes the comfort of the agent.
 * @param agent the agent.
 * @return the color.
 */
int agent_comfort(Agent* agent);

/**
 * Returns the color of the agent.
 * @param agent the agent.
 * @return the color.
 */
Color* agent_color(Agent* agent);

/**
 * Returns the node of the agent.
 * @param agent the agent.
 * @return the node.
 */
int agent_node(Agent* agent);

/**
 * Returns the vector of the agent.
 * @param agent the agent.
 * @return the vector.
 */
Vector* agent_v(Agent* agent);

/**
 * Returns the x coordinate.
 * @param agent the agent.
 * @return the x coordinate.
 */
double agent_x(Agent* agent);

/**
 * Returns the y coordinate.
 * @param agent the agent.
 * @return the y coordinate.
 */
double agent_y(Agent* agent);

/**
 * Computes the vector of the agent.
 * @param agent the agent.
 * @param colors the colors.
 * @param color_n the number of colors.
 * @return the vector.
 */
Vector* agent_vector(Agent* agent, Color** colors,
                     int color_n);

/**
 * Sets the vector of the agent.
 * @param agent the agent.
 * @param vector the vector.
 */
void agent_set_vector(Agent* agent, Vector* vector);

/**
 * Computes the agent distance from the determined color.
 * @param agent the agent.
 * @param color the color.
 * @return the distance.
 */
double agent_distance(Agent* agent, Color* color);

/**
 * Sets the comfort of the agent.
 * @param agent the agent.
 * @param comfort the comfort.
 */
void agent_set_comfort(Agent* agent, int comfort);

/**
 * Computes the nearest color to the agent.
 * @param agent the agent.
 * @param colors the colors.
 * @param color_n the number of colors.
 * @return the nearest color.
 */
Color* agent_nearest_color(Agent* agent, Color** colors,
                           int color_n);

/**
 * Computes the new position of the vector.
 * @param agent the agent.
 */
void agent_new_pos(Agent* agent);
