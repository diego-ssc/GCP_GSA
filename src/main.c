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

#include <stdio.h>

#include "heuristic.h"


/* Executes the main thread of the program. */
int main(int argc, char** argv) {
  struct drand48_data *buffer = malloc(sizeof(struct drand48_data));
  long int seedval = 1;
  srand48_r(seedval, buffer);
  Input_parser* parser = input_parser_new("file.txt", buffer);
  Graph* graph = input_parser_parse(parser);

  int i;
  for (i = 0; i < graph_n(graph); ++i)
    printf("%s\n", vertex_to_string(*(graph_vertices(graph) + i)));
  
  graph_free(graph);
  free(buffer);
  input_parser_free(parser);
}
