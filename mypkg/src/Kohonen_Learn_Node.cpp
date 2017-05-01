#include "ros/ros.h"
#include "sensor_msgs/Image.h"

#include <cv_bridge/cv_bridge.h>

#include "includes/macro.hpp"
#include "includes/kohonen.hpp"
#include "includes/psc_utils.hpp"
#include "includes/heatmap.hpp"
#include "includes/imagefeatures.hpp"
#include <fstream>
#include <iostream>

using namespace psc_utils;

int count = 0;
Kohonen map;
cv_bridge::CvImageConstPtr cv_ptr;
float deltaAlpha = 0.1;
float deltaR = 0.1;



void featureCallback(const sensor_msgs::Image::ConstPtr& msg)
{
	Kohonen map2("myKohonenMap.bv", 0);

	std::cout << "Checkpoint 6.1" << std::endl;
	cv_ptr = cv_bridge::toCvShare(msg);
	std::cout << "Checkpoint 6.2" << std::endl;

	ImageFeatures image(cv_ptr->image, cv_ptr->header.stamp.sec);
	std::cout << "Checkpoint 6.3" << std::endl;

	 for (int i = 0; i < FEATURES_SIZE_X; i++)
	{
				for (int j = 0; j < FEATURES_SIZE_Y; j++)
				{
					Vecteur v = image.getVector(i, j);
					
/*
					std::cout << "v_10" << v.get_value(10) << std::endl;
					std::cout << "v_100" << v.get_value(100) << std::endl;
					std::cout << "v_300" << v.get_value(300) << std::endl;
					std::cout << "v_400" << v.get_value(400) << std::endl;
					std::cout << "v_500" << v.get_value(500) << std::endl;					
*/
					map2.evolution(v, deltaAlpha, deltaR);
					//std::cout << "Checkpoint 6.4" << std::endl;

				}
	 }

	map.changeParam(DELTA_ALPHA, DELTA_R);
	std::cout << "Checkpoint 7" << std::endl;
	count++;
	map2.save("myKohonenMap");
	std::cout << "Checkpoint 8 : " <<  count << std::endl;


}


int main(int argc, char **argv)
{

	std::ifstream ifile("myKohonenMap.bv");
	std::cout << "Checkpoint 1" << std::endl;
	if (ifile)
	{
		Kohonen map1("myKohonenMap.bv", 0);
		std::cout << "Checkpoint 2.1" << std::endl;
		//map.print(2);
		//Kohonen aa("aa.bv", 0);
		//aa.print(0);
		map = map1;

	}
	else
	{
		Kohonen map1(2, ALPHA_INIT, R_INIT, 0);
		map1.randomInit();
		map1.save("myKohonenMap");
		// map.remplirCarteRand();
		std::cout << "Checkpoint 2.2" << std::endl;
		map1.print(0);
		map = map1;
		map.randomInit();

	}
	map.print(0);

	ros::init(argc, argv, "KohonenLearner_Listener");
	std::cout << "Checkpoint 3" << std::endl;

	ros::NodeHandle n;

	std::cout << "Checkpoint 4" << std::endl;

	ros::Subscriber sub = n.subscribe("deep_feature_extractor", 1, featureCallback);

	std::cout << "Checkpoint 5" << std::endl;

	ros::spin();

	return 0;

}
