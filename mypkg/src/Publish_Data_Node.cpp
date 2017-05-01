#include "ros/ros.h"
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <sstream>
#include <string>
#include <list>
#include <chrono>
#include <thread>
#include <iostream>


std::string dirname = "/home/john/data_test/";
std::string namefiles [] = {"sequence_0000001.png.yml",
"sequence_0000002.png.yml",
"sequence_0000003.png.yml",
"sequence_0000004.png.yml",
"sequence_0000005.png.yml",
"sequence_0000006.png.yml",
"sequence_0000007.png.yml",
"sequence_0000008.png.yml",
"sequence_0000009.png.yml", 
"sequence_0000010.png.yml", 
"sequence_0000011.png.yml", 
"sequence_0000012.png.yml", 
"sequence_0000013.png.yml", 
"sequence_0000014.png.yml", 
"sequence_0000015.png.yml", 
"sequence_0000016.png.yml", 
"sequence_0000017.png.yml", 
"sequence_0000020.png.yml", 
"sequence_0000021.png.yml", 
"sequence_0000022.png.yml", 
"sequence_0000023.png.yml", 
"sequence_0000024.png.yml", 
"sequence_0000025.png.yml", 
"sequence_0000026.png.yml", 
"sequence_0000027.png.yml", 
"sequence_0000028.png.yml", 
"sequence_0000029.png.yml", 
"sequence_0000030.png.yml", 
"sequence_0000031.png.yml", 
"sequence_0000032.png.yml", 
"sequence_0000033.png.yml", 
"sequence_0000034.png.yml", 
"sequence_0000035.png.yml", 
"sequence_0000036.png.yml", 
"sequence_0000037.png.yml", 
"sequence_0000038.png.yml", 
"sequence_0000039.png.yml", 
"sequence_0000040.png.yml", 
"sequence_0000041.png.yml", 
"sequence_0000042.png.yml", 
"sequence_0000043.png.yml", 
"sequence_0000045.png.yml", 
"sequence_0000046.png.yml", 
"sequence_0000047.png.yml", 
"sequence_0000048.png.yml", 
"sequence_0000049.png.yml", 
"sequence_0000050.png.yml",
"sequence_0000101.png.yml",
"sequence_0000102.png.yml",
"sequence_0000103.png.yml",
"sequence_0000104.png.yml",
"sequence_0000105.png.yml",
"sequence_0000106.png.yml",
"sequence_0000107.png.yml",
"sequence_0000108.png.yml",
"sequence_0000109.png.yml", 
"sequence_0000110.png.yml", 
"sequence_0000111.png.yml", 
"sequence_0000112.png.yml", 
"sequence_0000113.png.yml", 
"sequence_0000114.png.yml", 
"sequence_0000115.png.yml", 
"sequence_0000116.png.yml", 
"sequence_0000117.png.yml", 
"sequence_0000120.png.yml", 
"sequence_0000121.png.yml", 
"sequence_0000122.png.yml", 
"sequence_0000123.png.yml", 
"sequence_0000124.png.yml", 
"sequence_0000125.png.yml", 
"sequence_0000126.png.yml", 
"sequence_0000127.png.yml", 
"sequence_0000128.png.yml", 
"sequence_0000129.png.yml", 
"sequence_0000130.png.yml", 
"sequence_0000131.png.yml", 
"sequence_0000132.png.yml", 
"sequence_0000133.png.yml", 
"sequence_0000134.png.yml", 
"sequence_0000135.png.yml", 
"sequence_0000136.png.yml", 
"sequence_0000137.png.yml", 
"sequence_0000138.png.yml", 
"sequence_0000139.png.yml", 
"sequence_0000140.png.yml", 
"sequence_0000141.png.yml", 
"sequence_0000142.png.yml", 
"sequence_0000143.png.yml", 
"sequence_0000145.png.yml", 
"sequence_0000146.png.yml", 
"sequence_0000147.png.yml", 
"sequence_0000148.png.yml", 
"sequence_0000149.png.yml", 
"sequence_0000150.png.yml",
"sequence_0000201.png.yml",
"sequence_0000202.png.yml",
"sequence_0000203.png.yml",
"sequence_0000204.png.yml",
"sequence_0000205.png.yml",
"sequence_0000206.png.yml",
"sequence_0000207.png.yml",
"sequence_0000208.png.yml",
"sequence_0000209.png.yml", 
"sequence_0000210.png.yml", 
"sequence_0000211.png.yml", 
"sequence_0000212.png.yml", 
"sequence_0000213.png.yml", 
"sequence_0000214.png.yml", 
"sequence_0000215.png.yml", 
"sequence_0000216.png.yml", 
"sequence_0000217.png.yml", 
"sequence_0000220.png.yml", 
"sequence_0000221.png.yml", 
"sequence_0000222.png.yml", 
"sequence_0000223.png.yml", 
"sequence_0000224.png.yml", 
"sequence_0000225.png.yml", 
"sequence_0000226.png.yml", 
"sequence_0000227.png.yml", 
"sequence_0000228.png.yml", 
"sequence_0000229.png.yml", 
"sequence_0000230.png.yml", 
"sequence_0000231.png.yml", 
"sequence_0000232.png.yml", 
"sequence_0000233.png.yml", 
"sequence_0000234.png.yml", 
"sequence_0000235.png.yml", 
"sequence_0000236.png.yml", 
"sequence_0000237.png.yml", 
"sequence_0000238.png.yml", 
"sequence_0000239.png.yml", 
"sequence_0000240.png.yml", 
"sequence_0000241.png.yml", 
"sequence_0000242.png.yml", 
"sequence_0000243.png.yml", 
"sequence_0000245.png.yml", 
"sequence_0000246.png.yml", 
"sequence_0000247.png.yml", 
"sequence_0000248.png.yml", 
"sequence_0000249.png.yml", 
"sequence_0000250.png.yml",
"sequence_0000301.png.yml",
"sequence_0000302.png.yml",
"sequence_0000303.png.yml",
"sequence_0000304.png.yml",
"sequence_0000305.png.yml",
"sequence_0000306.png.yml",
"sequence_0000307.png.yml",
"sequence_0000308.png.yml",
"sequence_0000309.png.yml", 
"sequence_0000310.png.yml", 
"sequence_0000311.png.yml", 
"sequence_0000312.png.yml", 
"sequence_0000313.png.yml", 
"sequence_0000314.png.yml", 
"sequence_0000315.png.yml", 
"sequence_0000316.png.yml", 
"sequence_0000317.png.yml", 
"sequence_0000320.png.yml", 
"sequence_0000321.png.yml", 
"sequence_0000322.png.yml", 
"sequence_0000323.png.yml", 
"sequence_0000324.png.yml", 
"sequence_0000325.png.yml", 
"sequence_0000326.png.yml", 
"sequence_0000327.png.yml", 
"sequence_0000328.png.yml", 
"sequence_0000329.png.yml", 
"sequence_0000330.png.yml", 
"sequence_0000331.png.yml", 
"sequence_0000332.png.yml", 
"sequence_0000333.png.yml", 
"sequence_0000334.png.yml", 
"sequence_0000335.png.yml", 
"sequence_0000336.png.yml", 
"sequence_0000337.png.yml", 
"sequence_0000338.png.yml", 
"sequence_0000339.png.yml", 
"sequence_0000340.png.yml", 
"sequence_0000341.png.yml", 
"sequence_0000342.png.yml", 
"sequence_0000343.png.yml", 
"sequence_0000345.png.yml", 
"sequence_0000346.png.yml", 
"sequence_0000347.png.yml", 
"sequence_0000348.png.yml", 
"sequence_0000349.png.yml", 
"sequence_0000350.png.yml",
"sequence_0000401.png.yml",
"sequence_0000402.png.yml",
"sequence_0000403.png.yml",
"sequence_0000404.png.yml",
"sequence_0000405.png.yml",
"sequence_0000406.png.yml",
"sequence_0000407.png.yml",
"sequence_0000408.png.yml",
"sequence_0000409.png.yml", 
"sequence_0000410.png.yml", 
"sequence_0000411.png.yml", 
"sequence_0000412.png.yml", 
"sequence_0000413.png.yml", 
"sequence_0000414.png.yml", 
"sequence_0000415.png.yml", 
"sequence_0000416.png.yml", 
"sequence_0000417.png.yml", 
"sequence_0000420.png.yml", 
"sequence_0000421.png.yml", 
"sequence_0000422.png.yml", 
"sequence_0000423.png.yml", 
"sequence_0000424.png.yml", 
"sequence_0000425.png.yml", 
"sequence_0000426.png.yml", 
"sequence_0000427.png.yml", 
"sequence_0000428.png.yml", 
"sequence_0000429.png.yml", 
"sequence_0000430.png.yml", 
"sequence_0000431.png.yml", 
"sequence_0000432.png.yml", 
"sequence_0000433.png.yml", 
"sequence_0000434.png.yml", 
"sequence_0000435.png.yml", 
"sequence_0000436.png.yml", 
"sequence_0000437.png.yml", 
"sequence_0000438.png.yml", 
"sequence_0000439.png.yml", 
"sequence_0000440.png.yml", 
"sequence_0000441.png.yml", 
"sequence_0000442.png.yml", 
"sequence_0000443.png.yml", 
"sequence_0000445.png.yml", 
"sequence_0000446.png.yml", 
"sequence_0000447.png.yml", 
"sequence_0000448.png.yml", 
"sequence_0000449.png.yml", 
"sequence_0000450.png.yml"
};



cv::Mat get_image(const std::string& namefile)
{
  std::cout << "Checkpoint 2" << std::endl;
  cv::FileStorage fs(namefile, cv::FileStorage::READ);
  cv::Mat features;
  fs["deep_features"] >> features;
  return features;
}

/*
std::list<std::string> list_of_files(int n)
{
  std::cout << "Piou" << std::endl;
  std::list<std::string> list;
  int np;
  if (n > 101)
  {
    np = 80;
  }
  else 
  {
    np = n;
  }
  for (int i = 10 ; i < np ; np++)
  {
    std::string s = dirname + "sequence_00000";
    s += ".png.yml";
    list.push_back(s);
  }
  for(std::list<std::string>::iterator it = list.begin() ; it != list.end(); ++it)
  {
    std::cout << *it << std::endl;
  }
  return list;
}

*/

int main(int argc, char **argv)
{
  ros::init(argc, argv, "image_publisher");
  std::cout << "Checkpoint 0" << std::endl;

  ros::NodeHandle n;
  image_transport::ImageTransport it(n);
  std::cout << "Checkpoint 1" << std::endl;

  image_transport::Publisher pub = it.advertise("deep_feature_extractor", 100);
  //std::list<std::string> list = list_of_files(number_of_files);

  //ros::Rate loop_rate(10);
  for(int i = 0; i < 2 ; i++)
  {
    for(int j = 0; j < 200 ; j++)
    {
      std::string namefile = dirname + namefiles[j];
      int count = 0;
      std::cout << "**--- About to publish :  " << namefile << "  ---**" << std::endl;
      cv::Mat mat = get_image(namefile);
      sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(), "32FC1", mat).toImageMsg();
      pub.publish(msg);

      auto start = std::chrono::high_resolution_clock::now();
      std::chrono::duration<int, std::ratio<1, 100000000>> sleep_duration(1000000000);
      std::this_thread::sleep_for(sleep_duration);
      auto end = std::chrono::high_resolution_clock::now();
      std::chrono::duration<double, std::milli> elapsed = end-start;
      std::cout << "Waited " << elapsed.count() << " ms\n";
    }
  }
  ros::spin();
  return 0;
}