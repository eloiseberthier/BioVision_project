#include "ros/ros.h"
#include "std_msgs/Float64MultiArray.h"

#include "includes/macro.hpp"
#include "includes/kohonen.hpp"
#include "includes/psc_utils.hpp"
#include "includes/heatmap.hpp"


#include <vector>
#include <fstream>
#include <math.h>
#include <cmath>


#include "opennn/opennn.h"

using namespace OpenNN;

NeuralNetwork network;
int count = 0;

ros::NodeHandle n;
ros::Subscriber sub;
ros::Publisher neuralNetwork_pub;

void heatmapCallback(const std_msgs::Float64MultiArray::ConstPtr& msg)
{

   Matrix<double> inputs;
   std::vector< std::vector<float> > input_data(MAX_X);

   for (int i = 0; i < MAX_X; i++)
   {
       for (int j = 0; j < MAX_Y; j++)
       {
           input_data.at(i).push_back(msg->data[i*MAX_Y + j]);
       }
   }

   for (int i = 0; i < MAX_X; i++)
   {
     Vector<double> row(input_data.at(i).begin(), input_data.at(i).end());
     inputs.set_row(i, row);
   }

   Vector<double> input_vector = inputs.to_vector();

   Vector<double> outputs = network.calculate_outputs(input_vector);

   std::vector<float> output_data(outputs.begin(), outputs.end());

   std_msgs::Float64MultiArray dat;

   dat.layout.dim.push_back(std_msgs::MultiArrayDimension());
   dat.layout.dim[0].label = "Contexts";
   dat.layout.dim[0].size = NB_CONTEXTS;
   dat.layout.data_offset = 0;

   for (int i = 0; i < NB_CONTEXTS; i++)
   {
       dat.data[i] = output_data[i];
   }

   neuralNetwork_pub.publish(dat);

   count++;
   if (count%15 == 0)
    {
      count = 0;
      network.save("myNN.txt");
    }

}


int main(int argc, char **argv)
{

  std::ifstream ifile1("myNN.xml");

  if (ifile1)
  {
    std::string s = "myNN.txt";

    NeuralNetwork network(s);

    ros::init(argc, argv, "NeuralNetworkClassifier_Listener");

    ros::NodeHandle n;

    ros::Subscriber sub = n.subscribe("heat_map", 1, heatmapCallback);

    ros::Publisher neuralNetwork_pub = n.advertise<std_msgs::Float64MultiArray>("classification", 1);

    ros::spin();

  }

  return 0;

}
