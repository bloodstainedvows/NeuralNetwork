#include <vector>
#include "NetworkLayer.hpp"

class Network{
    private:
        vector<NetworkLayer> hiddenLayers;
        NetworkLayer outputLayer;
        double rate;
    
        public:
            vector<NetworkLayer> getLayers() const {
                vector<NetworkLayer> allLayers = hiddenLayers;
                allLayers.push_back(outputLayer);
                return allLayers;
            }

            vector<double> feedForward(vector<double>& inputs) {
                /*this handles the feed forwarding as the outputs are updated with every input as we go*/
                for (auto& i : hiddenLayers){
                    inputs = i.activateNeurons(inputs);
                }
                return outputLayer.activateNeurons(inputs);
            }

            vector<double> errorCalculation(vector<double>& givenValue, vector<double>& expectedValue){
                vector<double> errorDifferences;
                for (auto& i : givenValue){
                    errorDifferences.push_back(givenValue[i] - expectedValue[i]);
                }
                return errorDifferences;
            }

            void backPropagate(vector<double>& inputs, vector<double>& errors){
                /*okay cuties, so the whole delta of the output layer is just e'(x) assuming thats the error func * relu'(x) YEA I CAN CALL THESE FUNCTIONS WHAT I WANT
                that way, when going backwards, output is ready to be used :3*/
                for (size_t i = 0; i < outputLayer; i++){
                    outputLayer.getNeurons()[i].setDelta(errors[i]);
                }

                for (int layerIndex = hiddenLayers.size() - 1; layerIndex >= 0; --layerIndex){
                    NetworkLayer layer = hiddenLayers[layerIndex];
                    NetworkLayer& nextLayer = (layerIndex == hiddenLayers.size() - 1) ? outputLayer : hiddenLayers[layerIndex + 1];

                    for (size_t i = 0; i < layer.getNeurons().size(); ++i){
                        Neuron neuron = layer.getNeurons()[i];
                        double nextError = nextLayer.totalDelta(i);
                        neuron.setDelta(nextError);
                    }
                }
                updateAllWeights(inputs);
                
            }

            void updateAllWeights(vector<double>& inputs){
                for (size_t layerIndex = 0; layerIndex < hiddenLayers.size(); layerIndex++){
                    NetworkLayer layer = hiddenLayers[layerIndex];
                    vector<double> previousOutputs = (layerIndex == 0) ? inputs : hiddenLayers[layerIndex - 1].totalOutput();
                    for(Neuron i : layer.getNeurons()){
                        updateSingleWeights(previousOutputs, i);
                    }
                }
                for (size_t i = 0; i < outputLayer.getNeurons().size(); i++){
                    updateSingleWeights(hiddenLayers[-1].totalOutput(), outputLayer.getNeurons()[i])
                }
            }

            void updateSingleWeights(vector<double> previousOutputs, Neuron neuron){
                /*
                ∂Error/∂weight
                delta: how much the error changes with respect to neuron's output
                input: how much neuron's output changes with respect to specific weight
                */
                for (size_t i = 0; i < previousOutputs.size(); i++){
                    neuron.UpdateWeights(i, (rate * neuron.getDelta() * previousOutputs[i]), true);
                    neuron.updateBiases(this->rate, neuron.getDelta())
                }
            }

};-