#include "fisher_distribution.h"
#include <poincare/beta_function.h>
#include <poincare/regularized_incomplete_beta_function.h>
#include <cmath>
#include <float.h>

namespace Probability {

static inline double maxDouble(double x, double y) { return x > y ? x : y; }

float FisherDistribution::xMin() const {
  return -k_displayLeftMarginRatio * xMax();
}

float FisherDistribution::xMax() const {
  return 10.0f; //TODO LEA
}

float FisherDistribution::yMax() const {
  float maxAbscissa = m_parameter1;
  float result = evaluateAtAbscissa(maxAbscissa);
  if (std::isnan(result) || result <= 0.0f) {
    result = 1.0f;
  }
  return 1.0f; //TODO LEA
}

I18n::Message FisherDistribution::parameterNameAtIndex(int index) {
  if (index == 0) {
    return I18n::Message::D1;
  }
  assert(index == 1);
  return I18n::Message::D2;
}

I18n::Message FisherDistribution::parameterDefinitionAtIndex(int index) {
  if (index == 0) {
    return I18n::Message::D1FisherDefinition;
  }
  assert(index == 1);
  return I18n::Message::D2FisherDefinition;
}

float FisherDistribution::evaluateAtAbscissa(float x) const {
  if (x < 0.0f) {
    return NAN;
  }
  const float d1 = m_parameter1;
  const float d2 = m_parameter2;
  const float f = d1*x/(d1*x+d2);
  const float numerator = std::pow(f, d1/2.0f) * std::pow(1.0f - f, d2/2.0f);
  const float denominator = x * Poincare::BetaFunction(d1/2.0f, d2/2.0f);
  return numerator / denominator;
}

bool FisherDistribution::authorizedValueAtIndex(float x, int index) const {
  assert(index == 0 || index == 1);
  return x > FLT_MIN; // TODO LEA Add max limit? See NormalDistribution
}

void FisherDistribution::setParameterAtIndex(float f, int index) {
  TwoParameterDistribution::setParameterAtIndex(f, index);
  // TODO LEA Adjust parameter if max definition ? See NormalDistribution
}

double FisherDistribution::cumulativeDistributiveFunctionAtAbscissa(double x) const {
  const double d1 = m_parameter1;
  const double d2 = m_parameter2;
  return Poincare::RegularizedIncompleteBetaFunction(d1/2.0, d2/2.0, d1*x/(d1*x+d2));
}

double FisherDistribution::cumulativeDistributiveInverseForProbability(double * probability) {
  /* We have to compute the values of the interval in which to look for x.
   * We cannot put xMin because xMin is < 0 for display purposes, and negative
   * values are not accepted.
   * The maximum of the interval: we want */
  if (*probability < DBL_EPSILON) {
    return 0.0;
  }
  return cumulativeDistributiveInverseForProbabilityUsingIncreasingFunctionRoot(probability, DBL_EPSILON, maxDouble(xMax(), 100.0));  // Ad-hoc value;


}

}