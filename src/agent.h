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
 */
Agent* agent_new(int x, int y);

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