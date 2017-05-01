#include "ros/ros.h"
#include "std_msgs/Float64MultiArray.h"
#include "sensor_msgs/Image.h"

#include <cv_bridge/cv_bridge.h>
#include <fstream>


#include "includes/macro.hpp"
#include "includes/kohonen.hpp"
#include "includes/psc_utils.hpp"
#include "includes/heatmap.hpp"
#include "includes/imagefeatures.hpp"

using namespace psc_utils;

int count = 0;
HeatMap heatmap;
cv_bridge::CvImageConstPtr cv_ptr;
ros::Publisher kohonen_pub;
//Kohonen map;


void featureCallback(const sensor_msgs::Image::ConstPtr& msg)
{
  Kohonen map("myKohonenMap.bv", 0);
  std::cout << "Checkpoint 4" << std::endl;
  cv_ptr = cv_bridge::toCvShare(msg);
  ImageFeatures image(cv_ptr->image, cv_ptr->header.stamp.sec);
  std::cout << "Checkpoint 5" << std::endl;

   for (int i = 0; i < FEATURES_SIZE_X; i++)
   {
        for (int j = 0; j < FEATURES_SIZE_Y; j++)
        {
          Vecteur v = image.getVector(i, j);
          heatmap.heat(v, map);
        }
   }

  heatmap.cool(TAUX);
  std::cout << "Checkpoint 6" << std::endl;
  heatmap.print();

  if(count % 3 == 0)
  {
  std_msgs::Float64MultiArray dat;

  dat.layout.dim.push_back(std_msgs::MultiArrayDimension());
  dat.layout.dim.push_back(std_msgs::MultiArrayDimension());
  dat.layout.dim[0].size = MAX_X;
  dat.layout.dim[1].size = MAX_Y;
  dat.layout.data_offset = 0;

  std::cout << "Checkpoint 7" << std::endl;

  for (int i = 0; i < MAX_X; i++)
  {
      for (int j = 0; j < MAX_Y; j++)
      {
          dat.data.push_back(heatmap.get_value(i, j));
        }
    }
    kohonen_pub.publish(dat);
  }
    std::cout << "Checkpoint 8" << std::endl;

    count++;
    if (count%15 == 0)
    {
      count = 0;
      heatmap.save("MyHeatMap");
    }
}


int main(int argc, char **argv)
{

  std::ifstream ifile1("myKohonenMap.bv", std::ifstream::in);
  std::cout << "Checkpoint 1" << std::endl;

  if (ifile1)
   {
     // Kohonen map1("myKohonenMap.bv", 0);
      //map1.print(0);
      std::cout << "Piou" << std::endl;

      //map = map1;
      std::cout << "Piou" << std::endl;
     //map.print(0);
      std::ifstream ifile2("myHeatMap.bv", std::ifstream::in);
      std::cout << "Checkpoint 2" << std::endl;

      if (ifile2)
      {
        HeatMap heatmap1("MyHeatMap.bv", TAUX);
        heatmap = heatmap1;
      }
      else
      {
        HeatMap heatmap();
      }

      std::cout << "Checkpoint 2" << std::endl;

      ros::init(argc, argv, "KohonenRecog_Listener");

      ros::NodeHandle n;

      ros::Subscriber sub = n.subscribe("deep_feature_extractor", 1, featureCallback);

      kohonen_pub = n.advertise<std_msgs::Float64MultiArray>("heat_map", 1);
      std::cout << "Checkpoint 3" << std::endl;

      ros::spin();
   }

  return 0;

}
