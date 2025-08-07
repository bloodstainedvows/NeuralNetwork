#ifndef NEURON_HPP
#define NEURON_HPP

#include <vector>
#include <optional>

using std::vector;
using std::optional;


double reluSingle(double x);
void reluVector(vector<double>& values);
double reluSingleDerivative(double x);
void reluVectorDerivative(vector<double>& inputVector, vector<double>& outputVector);

struct Neuron {
private:
    vector<double> weights;
    double bias;
    optional<double> delta;
    optional<double> output;

    void setOutput(double output);

public:
    Neuron();

    void setDelta(double error);
    double calculateWeightedSum(const vector<double>& inputs);
    double activationFunction(const vector<double>& inputs);
};

#endif