#pragma once

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
    double delta;
    double output;

    void setOutput(double output);

public:
    Neuron();

    double getOutput() const;
    vector<double> getWeights() const;
    double getDelta() const;
    void setDelta(double error);
    double calculateWeightedSum(const vector<double>& inputs);
    double activationFunction(const vector<double>& inputs);
};