/* -*- Mode: c++ -*- */
/* VER: $Id$ */
// copyright (c) 2004 by Christos Dimitrakakis <dimitrak@idiap.ch>
/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
#ifndef MATH_FUNCTIONS_H
#define MATH_FUNCTIONS_H

#include "real.h"

int ArgMin (int n, real* x);
int ArgMax (int n, real* x);
real SmoothMaxGamma (real f1, real f2, real lambda, real c);
real SmoothMaxPNorm (real f1, real f2, real p);
void SoftMax (int n, real* Q, real* p, real beta);
void SoftMin (int n, real* Q, real* p, real beta);
void Normalise (real* src, real* dst, int n_elements);
real EuclideanNorm (real* a, real* b, int n);
real SquareNorm (real* a, real* b, int n);
real LNorm (real* a, real* b, int n, real p);
real Sum (real* a, int n);

template<class T>
inline const T sign(const T& x)
{
	if (x>0) {
		return 1;
	} else if (x<0) {
		return -1;
	} else {
		return 0;
	}
} 

#endif
