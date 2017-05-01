#include "ros/ros.h"
#include "std_msgs/Float64MultiArray.h"

#include "includes/macro.hpp"
#include "includes/kohonen.hpp"
#include "includes/psc_utils.hpp"
#include "includes/heatmap.hpp"
#include "includes/imagefeatures.hpp"

#include <fstream>
#include <vector>
#include <cmath>
#include <math.h>

#include "opennn/opennn.h"

using namespace OpenNN;

NeuralNetwork network;
int count = 0;

void heatmapCallback(const std_msgs::Float64MultiArray::ConstPtr& msg)
{
    std::cout << "Checkpoint 4" << std::endl;

	/*
	* SOMEHOW GET THE ARRAY INTO A MATRIX USABLE BY OpenNN
	*/
	Matrix<double> inputs;
	std::vector< std::vector<float> > input_data(MAX_X);

	for (int i = 0; i < MAX_X; i++)
	{
		for (int j = 0; j < MAX_Y; j++)
		{
      std::cout << "Checkpoint 4.1" << std::endl;				
      input_data.at(i).push_back(msg->data[i*MAX_Y + j]);
		}
	}
    std::cout << "Checkpoint 5" << std::endl;        

	for (int i = 0; i < MAX_X; i++)
	{
    std::cout << "Checkpoint 5.1" << std::endl;        
		Vector<double> row(input_data.at(i).begin(), input_data.at(i).end());
		inputs.set_row(i, row);
	}

  std::cout << "Checkpoint 6" << std::endl;        

	Vector<double> input_vector = inputs.to_vector();
  std::cout << "Checkpoint 6.1" << std::endl;        

	//Matrix<double> modif = network.calculate_Jacobian(input_vector);
  
  std::cout << "Checkpoint 6.2" << std::endl;        

	//Vector<double> modif_vector = modif.to_vector();
      std::cout << "Checkpoint 6.3" << std::endl;        

	Vector<double> param = network.arrange_parameters();
  
  std::cout << "Checkpoint 7" << std::endl;        
	//param += modif_vector * LEARNING_RATE;

	network.set_parameters(param);
  std::cout << "Checkpoint 8" << std::endl;        

	if (count%15 == 0)
		{
			network.save("myNN.xml");
			count++;
		}
}


int main(int argc, char **argv)
{

	std::ifstream ifile1("myNN.xml");
	std::string s = "myNN.xml";
  std::cout << "Checkpoint 1" << std::endl;

  if (ifile1)
	{
    std::cout << "Checkpoint 1.1" << std::endl;
		NeuralNetwork network(s);
	
    std::cout << "Checkpoint 1.1.1" << std::endl;

	}
  
	else
	{
   
  std::cout << "Checkpoint 1.2" << std::endl;
	NeuralNetwork network(FEATURES_SIZE_X * FEATURES_SIZE_Y, FEATURES_SIZE_X * FEATURES_SIZE_Y, NB_CONTEXTS);

	// Add a probabilistic layer at the end of the network
	network.construct_probabilistic_layer();
	ProbabilisticLayer* probabilistic_layer_pointer = network.get_probabilistic_layer_pointer();
	probabilistic_layer_pointer->set_probabilistic_method(ProbabilisticLayer::Probability);
	std::cout << "Checkpoint 1.2.1" << std::endl;
	}

  std::cout << "Checkpoint 2" << std::endl;
	ros::init(argc, argv, "NeuralNetworkLearner_Listener");

	ros::NodeHandle n;

	ros::Subscriber sub = n.subscribe("heat_map", 1, heatmapCallback);
  std::cout << "Checkpoint 3" << std::endl;

	ros::spin();

	return 0;

}
