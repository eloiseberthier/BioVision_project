#include <vector>
#include <list>
#include <string>
#include <iostream>
#include <cstdio>
#include <random>

#include "includes/psc_utils.hpp"
#include "includes/heatmap.hpp"
#include "includes/macro.hpp"
#include "includes/matrice.hpp"


namespace psc_utils
{

//Point
	Point::Point(int X, int Y)
	{
		x = X;
		y = Y;
	}

	Point::Point()
	{
		x = 0;
		y = 0;
	}


	Point::~Point()
	{
		//nothing to do here

	}

    Point Point::operator+(const Point& other) const
	{
		int n_x = x + other.getX();
		int n_y = y + other.getY();

		Point newPoint = Point(n_x, n_y);
		return newPoint;
	}

	Point Point::operator-(const Point& other) const
	{
		Point newPoint = Point(x - other.getX(), y - other.getY());
		return newPoint;
	}

    int Point::getX() const
	{
		return x;
	}

    int Point::getY() const
	{
		return y;
	}

	std::list<Point> Point::voisins(int r, int largest_x, int largest_y)
	{
    	std::list<Point> vois = std::list<Point>();
    	int I = getX();
    	int J = getY();
    	for(int i = (I - r); i <= I + r; i++)
    	{
        	for(int j = (J - r) ; j <= (J+r) ; j++)
        	{
        	    if ((((i - I) * (i - I)) + ((j - J) * (j - J)) <= (r * r)) && (i < largest_x) && (j < largest_y))
        	    {
        	        if ((i >= 0) && (j >= 0))
        			{
        	        	vois.push_back(Point(i,j));
        	    	}
        	    }
        	}
    	}
    	return vois;
	}



//Kohonen


	Kohonen::Kohonen(int numDis, float alphaInit, float r, int timestamp)
		:  Matrice(MAX_X, MAX_Y, timestamp, 0.0)
	{
	    typeDistance = numDis;
	    alpha = alphaInit;
	    voisinage = r;
	    randomInit();
	}

	Kohonen::Kohonen()
		:  Matrice(MAX_X, MAX_Y, 0, 0.0)
	{
	    typeDistance = 0;
	    alpha = 0.0;
	    voisinage = 0.1;
	    randomInit();

	}

	Kohonen::Kohonen(const std::string& namefile, int t)
		:  Matrice(namefile, t)

	{
		std::string f = namefile + ".par";
		FILE* fs;
		fs = fopen(f.c_str(), "rb");
		int td = 0;
		fread(&td, sizeof(int), 1, fs);
		float a = 0.0;
		fwrite(&a, sizeof(float), 1, fs);
		float v = 0.0;
		fwrite(&v, sizeof(float), 1, fs);
		fclose(fs);
		typeDistance = td;
		alpha = a;
		voisinage = v;
	}


	Kohonen::~Kohonen()
	{
	    //dtor
	}

	Point Kohonen::plusProchePoint(const Vecteur& v) const
	{
			std::random_device r;
			std::default_random_engine generator(r());
  		std::uniform_int_distribution<int> distributionX(0, MAX_X - 1);
			std::uniform_int_distribution<int> distributionY(0, MAX_Y - 1);
			//int x_0 = distributionX(generator);
	    //int y_0 = distributionY(generator);
			int x_0 = 0;
			int y_0 = 0;

			int x = x_0;
			int y = y_0;
	    Vecteur vpp = getVector(x, y);
	    float dMin = v.distance(typeDistance, vpp);

	   // std::cout << "dMin : "<< dMin << std::endl;

	    for(int i = 0 ; i < MAX_X; i++)
	    {
	        for (int j = 0; j < MAX_Y; j++)
	       	{
						if ((x != x_0) && (y != y_0))
						{
							Vecteur vp = getVector(i, j);
	          	float d = v.distance(typeDistance, vp);
	           // std::cout << "d : "<< d << " : " ;
	    		//std::cout << "dMin : "<< dMin << std::endl;
	            if(d < dMin)
	            {
	            	//std::cout << i << " : " << j << std::endl;
	                dMin = d;
	                x = i;
	                y = j;
	            }
						}
						}
	        }

	    //std::cout << x <<  " : " << y << " | ";
	    Point res(x, y);
	    return res;
	}

	void Kohonen::randomInit()
	{
		std::random_device r;
		std::default_random_engine generator(r());
  	std::normal_distribution<float> distribution(PARAM_DISTRIBUTION_MEAN, PARAM_DISTRIBUTION_SIGMA);
		for(int i = 0 ; i < MAX_X; i++)
	    {
	        for (int j = 0; j < MAX_Y; j++)
	       	{
	       		Vecteur v(Point(i, j), 0.0, 0);
	       		for(int k = 0 ; k < N_CARAC ; ++k)
	       		{
	       			float r = distribution(generator);
	       			//std::cout << r ;
	       			v.set_value(k, r);
	       		}
	       		replaceVector(i, j, v);
	        }
	    }
	   // print(0);
	}




	void Kohonen::modifierVoisin(Vecteur v, Point pointProche){
	    std::list<Point> voisins = pointProche.voisins(voisinage, MAX_X, MAX_Y);
	    for(std::list<Point>::iterator it = voisins.begin(); it != voisins.end(); ++it)
	    {
	      	int i = it->getX();
	      	int j = it->getY();
	        replaceVector(i, j, getVector(i, j) * (1.0 - alpha) + v * alpha);
	    }
	}

	void Kohonen::print(int layer) const
    {
        for (int i = 0; i < MAX_X ; i++)
        {
        	std::cout << "[" ;
            for (int j=0 ; j < MAX_Y ; j++)
            {
            	std::cout << get_value(i, j, layer) << "; ";
            }
            std::cout << "]" << std::endl;
        }
    }
	void Kohonen::changeParam(float deltaAlpha, float deltaR)
	{
	    alpha = alpha * (1.0 - deltaAlpha);
	    voisinage = voisinage - deltaR;
	}


	void Kohonen::evolution(Vecteur v, float deltaAlpha, float deltaR)
	{
		Point h = plusProchePoint(v);
	    modifierVoisin(v, h);
	}

	void Kohonen::resetMap()
	{
	    //well...
	}

	void Kohonen::resetTempsMap()
	{
	    Matrice::resetTimestamp();
	}

	void Kohonen::save(const std::string& namefile) const
	{
		std::string filename_1 = namefile + ".bv";
		std::string filename_2 = namefile + ".bv.par";
		Matrice::save_in_file(filename_1);
		FILE* fs;
		fs = fopen(filename_2.c_str(), "wb");
		fwrite(&typeDistance, sizeof(int), 1, fs);
		fwrite(&alpha, sizeof(float), 1, fs);
		fwrite(&voisinage, sizeof(float), 1, fs);
		fclose(fs);
	}
}
