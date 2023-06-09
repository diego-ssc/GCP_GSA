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

#include "heuristic.h"

/**
 * Creates a new color.
 * @param x the x coordinate.
 * @param y the y coordinate.
 */
Color* color_new(int x, int y);

/**
 * Frees the memory used by the color.
 * @param color the color.
 */
void color_free(Color* color);

/**
 * Returns the x coordinate of the color.
 * @param color the color.
 * @return the x coordinate.
 */
int color_x(Color* color);

/**
 * Returns the y coordinate of the color.
 * @param color the color.
 * @return the y coordinate.
 */
int color_y(Color* color);

/**
 * Returns the color attraction related to the agent.
 * @param color
 * @param agent
 * @return
 */
double color_attraction(Color* color, Agent* agent);
