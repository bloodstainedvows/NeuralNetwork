#pragma once

#include "NetworkLayer.hpp"
#include "Neuron.hpp"
#include <vector>
#include <algorithm>

using std::vector;

class Network{
    private:
        vector<NetworkLayer> hiddenLayers;
        NetworkLayer outputLayer;
        double rate;

    public:
        vector<NetworkLayer> getLayers() const;
        vector<double> feedForward(vector<double>& inputs);
        vector<double> errorCalculation(vector<double>& givenValue, vector<double>& expectedValue);
        void backPropagate(vector<double>& inputs, vector<double>& errors);
        void updateAllWeights(vector<double>& inputs);
        void updateSingleWeights(vector<double>& previousOutputs, Neuron neuron);
        double meanSquaredError(vector<double>& prediction, vector<double>& expected);
        void trainModel(int epochNumber, int outputNumber, vector<vector<double>>& trainingSet, vector<double>& trainingOutput);
        int predictInfo(vector<double>& inputs) const;
};
