#include <iostream>
#include <algorithm>
#include <vector>
#include <optional>

using 
std::vector,
std::optional,
std::cout,
std::cin
;

double reluSingle(double x){
    return std::max(0.0, x);
}

double reluVector(vector<double>& values){
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

double reluVectorDerivative(vector<double>& inputVector, vector<double>& outputVector){
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

struct Neuron {
    /*
    for each private attribute when I self-taught myself, I pretty much intuitively understood:

   - weights are each edge between vertices that have a weight associated which define each input's significance
   - biases are some arbitrary value typically unique per vertex to allow the output to adjust irrespective of the input, e.g. if the weights were 0 since w*value=output
   - delta is used during backpropogation via representing an error's derivative, respect to the weighted sum
   - output is the neuron's activation func
   */
    private:
        vector<double> weights;
        double bias;
        optional<double> delta;
        optional<double> output;

        void setOutput(float output){
            this->output = output;
        }

    public:
        Neuron() : delta(0.0), output(0.0) {}
        
        void setDelta(double error){
            /*delta = error x f'(z)
            Z : activation function
            */
            if(output.has_value()){
                delta = error * reluSingleDerivative(output.value());
            }
        }


}