#include "random.h"


using std::vector;


RandomNumbers::RandomNumbers(unsigned long int opt_seed) {
  seed = opt_seed != 0
    ? opt_seed
    : std::random_device()();

  rng = std::mt19937(seed);
}


void RandomNumbers::normal(vector<double>& values, double mean, double sd) {
  fill_with_distribution<double>(values, std::normal_distribution<double>(mean, sd));
}

double RandomNumbers::normal(double mean, double sd) {
  return std::normal_distribution<double>(mean, sd)(rng);
}


void RandomNumbers::poisson(vector<int>& values, double mean) {
  fill_with_distribution<int>(values, std::poisson_distribution<int>(mean));
}

int RandomNumbers::poisson(double mean) {
  return std::poisson_distribution<int>(mean)(rng);
}


void RandomNumbers::uniform_double(vector<double>& values, double lower, double upper) {
  fill_with_distribution<double>(values, std::uniform_real_distribution<double>(lower, upper));
}

double RandomNumbers::uniform_double(double lower, double upper) {
  return std::uniform_real_distribution<double>(lower, upper)(rng);
}


template <class T>
void RandomNumbers::fill_with_distribution(std::vector<T>& values, std::function<T(std::mt19937&)> distribution) {
  for (size_t index = 0; index < values.size(); index++) {
    values[index] = distribution(rng);
  }
}

