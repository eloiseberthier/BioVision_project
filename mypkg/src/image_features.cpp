#include "includes/imagefeatures.hpp"
#include "includes/macro.hpp"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <sstream>
#include <string>



namespace psc_utils
{
   ImageFeatures::ImageFeatures(const std::string& namefile, int time) 
   		: Matrice(FEATURES_SIZE_X, FEATURES_SIZE_Y, time, 0.0)
	{
		cv::FileStorage fs(namefile, cv::FileStorage::READ);
		cv::Mat features;
		fs["deep_features"] >> features;
		features = features.reshape(N_CARAC, FEATURES_SIZE_X);
		//cv::Mat features = (float)fs["deep_features"];
		std ::vector<cv ::Mat> vec_mat3D ;
		cv ::split(features, vec_mat3D) ;
		
		for(int k = 0 ; k < N_CARAC ; k++)
		{
			for(int i = 0 ; i < FEATURES_SIZE_X ; i++)
			{
				for(int j = 0 ; j < FEATURES_SIZE_Y ; j++)
				{
					float d = vec_mat3D[k].at<float>(i, j);
					set_value(i, j, k, d);

				}
			}	
		}
		
		for(int k = 0 ; k < N_CARAC ; k++)
		{
			std::cout << get_value(1, 1, k) << std::endl;
		}
	}

	ImageFeatures::ImageFeatures(cv::Mat mat, int time)
		: Matrice(FEATURES_SIZE_X, FEATURES_SIZE_Y, time, 0.0)
	{
		cv::Mat features;
		features = mat.reshape(N_CARAC, FEATURES_SIZE_X);	
		std::vector<cv ::Mat> vec_mat3D ;
		cv::split(features, vec_mat3D) ;
		//cv::Mat b = vec_mat3D[0].clone();
		//cv::imshow("piou", b);
		//cv::waitKey(10);
		//std::cout << b << std::endl;

		for(int k = 0 ; k < N_CARAC ; k++)
		{
			cv::Mat a = vec_mat3D[k];
			for(int i = 0 ; i < FEATURES_SIZE_X ; i++)
			{
				for(int j = 0 ; j < FEATURES_SIZE_Y ; j++)
				{
//					std::cout << " PSC UTILS : Checkpoint 2 : " << i << ":" << j << ":" << k << std::endl;
					//cv::imshow("piou", a);
					//cv::waitKey(10);
					float d = a.at<float>(i, j);
					set_value(i, j, k, d);
				}
			}	
		}

		//int coord[] = {12, 12, 500};
		//std::cout << get_value(12, 12, 500) << std::endl;
		//std::cout << (float)(mat.at<float>(coord)) << std::endl;

	}

    ImageFeatures::~ImageFeatures()
	{	
		//implement the fonction here and describe its use 
	}
}




