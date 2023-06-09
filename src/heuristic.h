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

#include <stdlib.h>

/**
 * The Agent opaque structure.
 */
typedef struct _Agent Agent;

/**
 * The Input Parser opaque structure.
 */
typedef struct _Input_parser Input_parser;

/**
 * The GSA opaque structure.
 */
typedef struct _GSA GSA;

/**
 * The GCP opaque structure.
 */
typedef struct _GCP GCP;

/**
 * The Graph opaque structure.
 */
typedef struct _Graph Graph;

/**
 * The Color opaque structure.
 */
typedef struct _Color Color;

/**
 * The Vector opaque structure.
 */
typedef struct _Vector Vector;

#include "agent.h"
#include "input_parser.h"
#include "gsa.h"
#include "gcp.h"
#include "graph.h"
#include "color.h"
#include "vector.h"
