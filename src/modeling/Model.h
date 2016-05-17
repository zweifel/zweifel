#ifndef MODEL_H
#define MODEL_H

#include"stdlib.h"

class Model
{
	public:

		//It models the samples passed, with the expected system's responses (modeling phase)
		//
		virtual void model(double** input_samples, double** expected_output, int number_of_samples, int number_of_inputs, int number_of_outputs, double** accuracy=NULL) = 0;

		//send a signal and receive the model's output (testing phase or just using the model)
		virtual void signal(double* input_signal, double* model_output) = 0;
		
		//test the accuracy of the model on a given set of samples and expected_outputs
		//the initial_index and the final_index of the testing samples are passed
		virtual double testAccuracy(double** input_samples, double ** expected_output, int initial_index, int final_index, double** accuracy=NULL) = 0;
};

#endif

