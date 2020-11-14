#include "neural_math.h"

class Layer {
	public:
		Layer(int input_size, int output_size);
		void generate_biases(int output_size);
		void generate_weights(int input_size, int output_size);
	private:
		int input_size;
		int output_size;
		double** weights;
		double biases[];
};

Layer::Layer(int input_size, int output_size) {
	Layer::input_size = input_size;
	Layer::output_size = output_size;
	Layer::generate_biases(output_size);
	Layer::generate_weights(input_size, output_size);
}

void Layer::generate_biases(int output_size) {

}

void Layer::generate_weights(int input_size, int output_size) {

}