#include <cmath>
#include "Network.hpp"


vector<NetworkLayer> Network::getLayers() const {
    vector<NetworkLayer> allLayers = hiddenLayers;
    allLayers.push_back(outputLayer);
    return allLayers;
}

vector<double> Network::feedForward(vector<double>& inputs) {
    /*this handles the feed forwarding as the outputs are updated with every input as we go*/
    for (auto& i : hiddenLayers){
        inputs = i.activateNeurons(inputs);
    }
    return outputLayer.activateNeurons(inputs);
}

vector<double> Network::errorCalculation(vector<double>& givenValue, vector<double>& expectedValue){
    vector<double> errorDifferences;
    for (size_t i = 0; i < givenValue.size(); i++){
        errorDifferences.push_back(givenValue[i] - expectedValue[i]);
    }
    return errorDifferences;
}

void Network::backPropagate(vector<double>& inputs, vector<double>& errors){
    /*okay cuties, so the whole delta of the output layer is just e'(x) assuming thats the error func * relu'(x) YEA I CAN CALL THESE FUNCTIONS WHAT I WANT
    that way, when going backwards, output is ready to be used :3*/
    for (size_t i = 0; i < outputLayer.getNeurons().size(); i++){
        outputLayer.getNeurons()[i].setDelta(errors[i]);
    }

    for (int layerIndex = hiddenLayers.size() - 1; layerIndex >= 0; --layerIndex){
        NetworkLayer& layer = hiddenLayers[layerIndex];
        NetworkLayer& nextLayer = (layerIndex == hiddenLayers.size() - 1) ? outputLayer : hiddenLayers[layerIndex + 1];

        for (size_t i = 0; i < layer.getNeurons().size(); ++i){
            Neuron& neuron = layer.getNeurons()[i];
            double nextError = nextLayer.totalDelta(i);
            neuron.setDelta(nextError);
        }
    }
    updateAllWeights(inputs);
    
}

void Network::updateAllWeights(vector<double>& inputs){
    for (size_t layerIndex = 0; layerIndex < hiddenLayers.size(); layerIndex++){
        NetworkLayer& layer = hiddenLayers[layerIndex];
        vector<double> previousOutputs = (layerIndex == 0) ? inputs : hiddenLayers[layerIndex - 1].totalOutput();
        for(Neuron& i : layer.getNeurons()){
            updateSingleWeights(previousOutputs, i);
        }
    }
    for (size_t i = 0; i < outputLayer.getNeurons().size(); i++){
        updateSingleWeights(hiddenLayers.back().totalOutput(), outputLayer.getNeurons()[i]);
    }
}

void Network::updateSingleWeights(vector<double>& previousOutputs, Neuron neuron){
    /*
    ∂Error/∂weight
    delta: how much the error changes with respect to neuron's output
    input: how much neuron's output changes with respect to specific weight
    */
    for (size_t i = 0; i < previousOutputs.size(); i++){
        neuron.UpdateWeights(i, (rate * neuron.getDelta() * previousOutputs[i]), true);
        neuron.updateBiases(this->rate, neuron.getDelta());
    }
}

double Network::meanSquaredError(vector<double>& prediction, vector<double>& expected){
    double totalError = 0.0;
    for (size_t i = 0; i < prediction.size(); i++){
        totalError += pow((prediction[i] - expected[i]), 2);
    }
    return totalError / prediction.size();
}

void Network::trainModel(int epochNumber, int outputNumber, vector<vector<double>>& trainingSet, vector<double>& trainingOutput){
    for (int i = 0; i < epochNumber; i++){
        double sumError = 0.0;
        vector<double> expectedValues;
        for (size_t j = 0; j < trainingSet.size(); j++){
            for (int k = 0; k < outputNumber; k++){
                expectedValues.push_back(0.0);
            }
            expectedValues[trainingOutput[j]] = 1.0;
            vector<double> prediction = feedForward(trainingSet[j]);
            vector<double> error = errorCalculation(prediction, expectedValues);
            backPropagate(trainingSet[j], error);
            sumError += meanSquaredError(prediction, trainingOutput);
        }
    }
}
int Network::predictInfo(vector<double>& inputs) const {
    vector<double> allOutputs = feedForward(inputs);
    return std::max_element(allOutputs.begin(), allOutputs.end()) - allOutputs.begin();
}
