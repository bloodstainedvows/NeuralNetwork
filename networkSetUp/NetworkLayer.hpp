#pragma once 

#include "Neuron.hpp"
#include <vector>

using std::vector;

class NetworkLayer{
    private:
        vector<Neuron> neurons;
    
    public:
        NetworkLayer(const vector<Neuron>& newNeurons);

        vector<double> totalOutput() const;
        vector<double> activateNeurons(const vector<double>& inputs);
        double totalDelta(int previousLayer) const;
};