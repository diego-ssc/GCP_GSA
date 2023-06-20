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
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "input_parser.h"

/* The Input parser structure. */
struct _Input_parser {
  /* The file pointer. */
  FILE* fp;
  /* The number of nodes. */
  int n;
  /* The number of edges. */
  int m;
  /* The RNG buffer. */
  struct drand48_data *buffer;
  /* The adjacency matrix. */
  int** edges;
};

/* Creates a new Input Parser. */
Input_parser* input_parser_new(char* file_n, struct drand48_data *buffer) {
  /* Heap allocation. */
  Input_parser* parser = malloc(sizeof(struct _Input_parser));

  /* Heap initialization. */
  parser->buffer = buffer;

  /* File opening. */
  parser->fp = fopen(file_n, "r");

  if (!parser->fp) {
    fprintf(stderr, "GCP_GSA:\tCould not open file: %s\n", file_n);
    exit(1);
  }

  return parser;
}

/* Frees the memory used by the Input parser. */
void input_parser_free(Input_parser* parser) {
  fclose(parser->fp);
  free(parser);
}

/* Parses the input. */
Graph* input_parser_parse(Input_parser* parser, double d) {
  char s[100];
  char* token;
  int* n = malloc(sizeof(int) * 2);
  int i = 0, j;

  /* The file must contain a problem line. */
  /* p FORMAT NODES EDGES */
  while (!feof(parser->fp))
    if (strstr(fgets(s, 100, parser->fp) ? s : "", "p edge") != 0)
      break;

  if (strstr(s, "p edge") == 0) {
    fprintf(stderr, "GCP_GSA: Wrong file format\n");
    exit(1);
  }

  token = strtok(s, "  \f\n\r\t\v");
  while(token != 0) {
    if (isdigit(*token)) {
      *(n + i) =  atoi(token);
      ++i;
    }
    token = strtok(0, "  \f\n\r\t\v");
  }

  /* Number of nodes. */
  parser->n = *(n);
  /* Number of edges. */
  parser->m = *(n + 1);
  free(n);

  /* The adjacency matrix initialization. */
  parser->edges = calloc(1, sizeof(int*)*(parser->n + 1));
  for(i = 0; i < parser->n + 1; i++)
    *(parser->edges + i) = calloc(1, (parser->n + 1) * sizeof(int));

  i = 0, j = 0;
  /* Edge and node parsing. */
  while (!feof(parser->fp)) {
    if (strstr(fgets(s, 100, parser->fp) ? s : "", "e") != 0) {
      token = strtok(s, "  \f\n\r\t\v");
      if (*token == 'c')
        continue;
      while(token != 0) {
        if (isdigit(*token)) {
          i = atoi(token);
          token = strtok(0, "  \f\n\r\t\v");
          j = atoi(token);
          *(*(parser->edges + i) + j) = 1;
          *(*(parser->edges + j) + i) = 1;
        }
        token = strtok(0, "  \f\n\r\t\v");
      }
    }
  }

  return graph_new(parser->buffer, parser->edges, parser->n, d);
}
