#pragma once
#include "matrice.hpp"
#include <opencv2/opencv.hpp>
namespace psc_utils
{
	class ImageFeatures : public Matrice
	{
	private:
	
	public:
	   	ImageFeatures(const std::string& namefile, int time);
	    ImageFeatures(cv::Mat mat, int time);
	    ~ImageFeatures();
	};
}