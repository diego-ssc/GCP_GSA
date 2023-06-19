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
 * Creates a new Input Parser.
 * @param file_n the file name.
 * @param buffer the RNG buffer.
 */
Input_parser* input_parser_new(char* file_n, struct drand48_data *buffer);

/**
 * Frees the memory used by the Input parser.
 * @param parser the parser.
 */
void input_parser_free(Input_parser* parser);

/**
 * Parses the input.
 * @param parser the parser.
 * @param the graph dimension.
 * @return the graph.
 */
Graph* input_parser_parse(Input_parser* parser, double d);
