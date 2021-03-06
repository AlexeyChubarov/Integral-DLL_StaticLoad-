// IntegralLib.cpp : Определяет экспортированные функции для приложения DLL.
//

#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <limits.h>
#include "Integral.h"


constexpr auto eps = (1e-20);

double SinPlusCos(double x)
{
	return sin(x) + cos(x);
}

double SinDivideId(double x)
{
	return sin(x) / x;
}

double SecMultiplyId(double x)
{
	return x / cos(x);
}


double dIntegral(double(*func)(double x), double from, double to, double step)
{
	int n, id_sign;
	double integral_summ, change;

	integral_summ = 0.;
	change = 0.;

	if (abs(step) < eps)
	{
		fprintf(stderr, "sorry, you divide on zero (number nearby zero).\n");
		return NAN;
	}

	if (step < 0)
	{
		fprintf(stderr, "sorry, you have written down step<0. It has no physical sense.\n");
		return NAN;
	}


	if ((abs(to - from) / step) > INT_MAX)
	{
		fprintf(stderr, "sorry, you have faced integer overflow.\n");
		return NAN;
	}

	id_sign = 1;

	if ((from - to) >= eps)
	{
		id_sign = -1;

		change = to;
		to = from;
		from = change;
	}

	n = (int)((to - from) / step);

	for (int i = 1; i < n; i++)
	{
		integral_summ += (*func)(from + i * step);
	}
	integral_summ = id_sign * (integral_summ + ((*func)(from) + (*func)(to)) / 2.)*step;
	return integral_summ;
}


