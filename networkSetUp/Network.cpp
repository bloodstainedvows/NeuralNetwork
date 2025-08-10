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
                for (size_t i = 0; i < outputLayer.)
                sdriktguje0p9ortiga-opreujiedrjg
            }

};