#include <vector>
#include "Neuron.hpp"
#include "NetworkLayer.hpp"

using std::vector;

/*this is to organize each neuron into layers, thats the essence of neural networks :3*/

NetworkLayer::NetworkLayer(const vector<Neuron>& newNeurons) : neurons(newNeurons) {}

vector<Neuron> NetworkLayer::getNeurons() {
    return neurons;
}

vector<double> NetworkLayer::totalOutput() const {
    vector<double> outputs;
    outputs.reserve(neurons.size());
    for (auto& neuron : neurons){
        outputs.push_back(neuron.getOutput());
    }
    return outputs;
}

vector<double> NetworkLayer::activateNeurons(const vector<double>& inputs) {
    vector<double> activations;
    activations.reserve(neurons.size());
    for (auto& neuron : neurons){
        activations.push_back(neuron.activationFunction(inputs));
    }
    return activations;
}

double NetworkLayer::totalDelta(int previousLayer) const {
    double totalSum = 0.0;
    for (auto& neuron : neurons){
        totalSum += neuron.getWeights()[previousLayer] * neuron.getDelta();
    }
    return totalSum;

}
