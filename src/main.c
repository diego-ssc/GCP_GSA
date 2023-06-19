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
#include <string.h>

#include "heuristic.h"

/* Prints the execution intructions of the program. */
static void usage() {
  fprintf(stderr, "Usage:\n\t./GCP_GSA"
          " -f [input file] [options]\n\n");
  fprintf(stderr, "Options:\n"
          "\t-s\n\t\tthe seed\n"
          "\t-n\n\t\tthe expected chromatic number\n"
          "\t-d\n\t\tthe graph dimension\n"
          "\t-i\n\t\tthe number of iterations\n"
          "\t-c\n\t\tthe comfort\n"
          "\t-v\n\t\tverbose\n");
  exit(1);
}

/* Parses the arguments passed to the program. */
void parse_arguments(int argc, char** argv) {
  if (argc < 3)
    usage();

  int n = 0, i = 0, c = 0, f = 0, v = 0;
  double d = 0;
  long int s = 0;
  char f_n[100];

  while (--argc > 0)
    if ((*++argv)[0] == '-')
      while ((c = *++argv[0]))
        switch (c) {
        case 'n':
          n = argc - 1 ? atoi(*(argv + 1)) : n;
          break;
        case 'f':
          if (argc - 1)
            strcpy(f_n, *(argv + 1));
          f++;
          break;
        case 's':
          s = argc - 1 ? atoi(*(argv + 1)) : s;
          break;
        case 'i':
          i = argc - 1 ? atoi(*(argv + 1)) : i;
          break;
        case 'c':
          c = argc - 1 ? atoi(*(argv + 1)) : c;
          break;
        case 'v':
          v = 1;
          break;
        case 'd':
          d = argc - 1 ? atof(*(argv + 1)) : d;
          break;
        default:
          fprintf(stderr, "GCP_GSA: illegal option %c\n", c);
          argc = 0;
          break;
        }

  if (!f)
    usage();

  GSA* gsa = gsa_new(f_n, s, n, d, i, c, v);
  printf("Solution found: %d\n", gsa_heuristic(gsa));
  gsa_free(gsa);
}

/* Executes the main thread of the program. */
int main(int argc, char** argv) {
  parse_arguments(argc, argv);
  return 0;
}
