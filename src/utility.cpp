#include "utility.h"
#include <cmath>
#include<vector>

double gauss(int x, double sigma)
{
	double A = 1 / (sigma * sqrt(2 * 3.1415922653));
	double index = -1.0 * (x * x) / (2 * sigma * sigma);
	return A * exp(index);
}

std::vector<double> getKernel(int r, double sigma)
{
	std::vector<double> weights(2 * r + 1);
	double sum = 0;

	for (int i = 0; i < 2 * r + 1; ++i)
	{
		weights[i] = gauss(i - r, sigma);
		sum += weights[i];
	}

	for (int i = 0; i < 2 * r + 1; ++i)
	{
		weights[i] /= sum;
	}

	return weights;
}