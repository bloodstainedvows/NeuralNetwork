#include "Neuron.hpp"
#include <algorithm>

double reluSingle(double x){
    return std::max(0.0, x);
}

void reluVector(vector<double>& values){
    for (double& x : values){
        x = std::max(0.0, x);
    }
}

double reluSingleDerivative(double x){
    if(x > 0){
        return 1.0;
    }
    return 0.0;
}
void reluVectorDerivative(vector<double>& inputVector, vector<double>& outputVector){
     outputVector.resize(inputVector.size());
     for(size_t i = 0; i < inputVector.size(); i++){
        if (inputVector[i] > 0){
            outputVector[i] = 1.0;
        }
        else{
            outputVector[i] = 0.0;
        }
     }
}
 /*
   - weights are each edge between vertices that have a weight associated which define each input's significance
   - biases are some arbitrary value typically unique per vertex to allow the output to adjust irrespective of the input, e.g. if the weights were 0 since w*value=output
   - delta is used during backpropogation via representing an error's derivative, respect to the weighted sum
   - output is the neuron's activation func
   */
Neuron::Neuron() : delta(0.0), output(0.0) {}

double Neuron::getOutput() const {
    return output;
}

vector<double> Neuron::getWeights() const {
    return weights;
}

void Neuron::UpdateWeights(int index, double weightCalculation, bool backpropogate) {
    if (backpropogate){
        weights[index] -= weightCalculation;
        return;
    }
    weights[index] = weightCalculation;
}

void Neuron::updateBiases(double rate, double delta){
    bias -= rate * delta;
}

double Neuron::getDelta() const {
    return delta;
}

void Neuron::setDelta(double error){
            /*delta = error x f'(z)
            z : activation function
            */
            delta = error * reluSingleDerivative(output);
        }

double Neuron::calculateWeightedSum(const vector<double>& inputs){
            /*need to use da reLU to normalize dis ya okai bai*/
            double weightedSum = this->bias;
            for (size_t i = 0; i < weights.size(); ++i){
                weightedSum += weights[i] * inputs[i];
            }
            return weightedSum;
        }

double Neuron::activationFunction(const vector<double>& inputs) {
            double newOutput = reluSingle(calculateWeightedSum(inputs));
            setOutput(newOutput);
            return newOutput;
        }