#include <iostream>
#include <string>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>

#include "includes/macro.hpp"
#include "includes/matrice.hpp"
#include "includes/psc_utils.hpp"
#include "includes/heatmap.hpp" 

namespace psc_utils
{
	template<typename T>
	raw_matrix<T>::raw_matrix()
	{
		data = new T[1];
		number_of_fields = 0;
		sizes = new int[1];
		sizes[0] = 1;
		total_size = 1;
	}

	template<typename T>
	raw_matrix<T>::raw_matrix(const raw_matrix<T>& other)
	{
		number_of_fields = other.number_of_fields;
		sizes = new int[other.number_of_fields];
		data = new T[other.total_size];
		total_size = other.total_size;
		memcpy(sizes, other.sizes, number_of_fields);
		memcpy(data, other.data, total_size);
	}

	
	template<typename T>
	raw_matrix<T>::raw_matrix(int n, int s[], const T& d_val)
	{
		sizes = new int[number_of_fields];
		int sp = 1;
		for(int i = 0 ; i < n ; ++i)
		{
			sp *= s[i];
			sizes[i] = s[i];
		}
		data = new T[sp];
		number_of_fields = n;
		total_size = sp;
		for (int i = 0; i < sp; i++) {
			data[i] = d_val;	
		}
	}

	template<typename T>
	raw_matrix<T>::raw_matrix(int s_x, int s_y, int s_z, const T& d_val)
	{

		sizes = new int[3];
		sizes[0] = s_x;
		sizes[1] = s_y;
		sizes[2] = s_z;
		int sp = s_x * s_y * s_z;
		number_of_fields = 3;
		data = new T[sp];
		total_size = sp;
		for (int i = 0; i < sp; i++) {
			data[i] = d_val;	
		}
	}

	template<typename T>
	raw_matrix<T>::raw_matrix(int s_x, int s_y, const T& d_val)
	{
		sizes = new int[2];
		sizes[0] = s_x;
		sizes[1] = s_y;
		int sp = s_x * s_y;
		number_of_fields = 2;
		data = new T[sp];
		total_size = sp;
		for (int i = 0; i < sp; i++) {
			data[i] = d_val;	
		}
	}
	
	template<typename T>
	raw_matrix<T>& raw_matrix<T>::operator= (const raw_matrix<T>& other)
	{
		if(this != &other)
		{
			number_of_fields = other.number_of_fields;
			sizes = new int[other.number_of_fields];
			data = new T[other.total_size];
			total_size = other.total_size;
			memcpy(sizes, other.sizes, number_of_fields);
			memcpy(data, other.data, total_size);
		}
		else
		{
			return	*this;
		}
	}


	template<typename T>
	raw_matrix<T>::raw_matrix(int s, const T& d_val)
	{
		sizes = new int[1];
		sizes[0] = s;
		data = new T[s];
		number_of_fields = 1;
		total_size = s;
		for (int i = 0; i < s; i++) {
			data[i] = d_val;	
		}
	}


	template<typename T>
	raw_matrix<T>::raw_matrix(const std::string& namefile)
	{
		FILE* fs;
		fs = fopen(namefile.c_str(), "rb");
		int n_fields = 0;
		fread(&n_fields, sizeof(int), 1, fs);
		number_of_fields = n_fields;
		int* s_fields = new int[n_fields];
		fread(s_fields, sizeof(int), n_fields, fs);
		sizes = s_fields;
		int t_size = 0;
		fread(&t_size, sizeof(int), 1, fs);
		total_size = t_size;
		T* d = new T[t_size];
		fread(d, sizeof(T), t_size, fs);
		data = d;
		fclose(fs);	
	}
	



	template<typename T>
	raw_matrix<T>::~raw_matrix()
	{
		delete[] sizes;
		delete[] data;	
	}



	template<typename T>
	void raw_matrix<T>::set_value(int coor[], const T& value)
	{
		int pointer = 0;
		int width = total_size;
		for(int i = 0 ; i < number_of_fields ; ++i)
		{
			if(i != (number_of_fields - 1))
			{
				width /= sizes[i];
				pointer +=  (coor[i]) * width;
			}
			else
			{
				pointer += coor[i];
			}
		}
		data[pointer] = value;
	}
	
	template<typename T>
	T raw_matrix<T>::get_value(int coor[]) const
	{
		if(number_of_fields == 1)
		{
			return data[coor[0]];
		}

		int pointer = 0;
		int width = total_size;
		for(int i = 0 ; i < number_of_fields ; ++i)
		{
			if(i != (number_of_fields - 1))
			{
				width /= sizes[i];
				pointer +=  (coor[i]) * width;
			}
			else
			{
				pointer += coor[i];
			}
		}
		return data[pointer];
	}

	template<typename T>
	void raw_matrix<T>::save_in_file(const std::string& namefile) const
	{	
		FILE* fs;
		fs = fopen(namefile.c_str(), "wb");
		fwrite(&number_of_fields, sizeof(int), 1, fs);
		fwrite(sizes, sizeof(int), number_of_fields, fs);
		fwrite(&total_size, sizeof(int), 1, fs);
		fwrite(data, sizeof(T), total_size, fs);
		fclose(fs);
	}

	template<typename T>
	void raw_matrix<T>::save_in_file(FILE* fs) const
	{	

		fwrite(&number_of_fields, sizeof(int), 1, fs);
		fwrite(sizes, sizeof(int), number_of_fields, fs);
		fwrite(&total_size, sizeof(int), 1, fs);
		fwrite(data, sizeof(T), total_size, fs);
	}

//Vecteur

	Vecteur::Vecteur(Point p, float d_value, int t)
		: raw_matrix<float> (N_CARAC, d_value) 
	{
		position = p;
		timestamp = t;
	}
	
	
	
	Vecteur::Vecteur(float* c, Point p, int t) 
		: raw_matrix<float> (N_CARAC, 0.0) 
	{
		for(int i = 0 ; i < N_CARAC ; ++i)
		{
			set_value(i ,c[i]);
		}
		position = p;
		timestamp = t;
	}
	

	Vecteur::~Vecteur()
	{
	}
	
	Vecteur::Vecteur(const Vecteur& other)
		: raw_matrix<float>(other)
	{
		timestamp = other.timestamp;
	}


	void Vecteur::print() const
	{
		for(int i = 0 ; i < N_CARAC ; i++)
		{
			std::cout << i << ":" << get_value(i) << std::endl;
		}
	}

	float Vecteur::get_value(int k) const
	{
		int v[] = {k};
		return raw_matrix::get_value(v);
	}

	void Vecteur::set_value(int k, float value)
	{
		int v[] = {k};
		return raw_matrix::set_value(v, value);
	}
	
	Point Vecteur::getPosition() const
	{
		return position;
	}

	int Vecteur::getTime() const
	{
		return timestamp;
	}

	
	float Vecteur::distance(int numDistance, const Vecteur& other) const
	{
		float res = 0.0;
		switch(numDistance)
		{
			case 0:
				res = norm1(other);
				break;
			case 1:
				res = norm2(other);
				break;
			case 2:
				res = dist_cos(other);
				break;
			case 3:
				res = dist_temp(other);
				break;
			default:
				res = 0.0;												
		}
		return res;
	}
	
	Vecteur Vecteur::operator*(float c) const
	{
		Vecteur res(position, 0, timestamp);
		for(int k = 0 ; k < N_CARAC ; ++k)
		{
			res.set_value(k, c*get_value(k));
		}
		return res;
	}
	
	Vecteur Vecteur::operator+(const Vecteur& other) const
	{
		Vecteur res(position - other.getPosition(), 0, timestamp);
		for(int k = 0 ; k < N_CARAC ; ++k)
		{
			res.set_value(k, get_value(k) + other.get_value(k));
		}
		return res;
	}
	
	Vecteur Vecteur::operator-(const Vecteur& other) const
	{
		Vecteur res(position - other.getPosition(), 0, timestamp);
		for(int k = 0 ; k < N_CARAC ; ++k)
		{
			res.set_value(k, get_value(k) - other.get_value(k));
		}
		return res;
	}
	
	float Vecteur::norm1(const Vecteur& b) const 
	{
		float res = 0;
		
		for(int i = 0 ; i < N_CARAC ; ++i)
		{
			res = res + abs(get_value(i) - b.get_value(i));
		}
		
		return res;	
	}
	
	
	float Vecteur::norm2(const Vecteur& b) const 
	{
		float norm2_square = 0;

		for(int i = 0 ; i < N_CARAC ; ++i)
		{
			norm2_square = norm2_square + pow(get_value(i) - b.get_value(i),2);
		}
		
		float res = pow(norm2_square, 0.5);
		
		return res;	
	}
	
	float Vecteur::dist_cos(const Vecteur& b) const 
	{
		float norm_a_square = 0;
		float norm_b_square = 0;
		float scalar_product_square = 0;
		
		for(int i = 0 ; i < N_CARAC ; ++i)
		{
			norm_a_square = norm_a_square + pow(get_value(i), 2);
			norm_b_square = norm_b_square + pow(b.get_value(i), 2);
			scalar_product_square = scalar_product_square + get_value(i)*b.get_value(i);
		}
		
		float norm_a = pow(norm_a_square, 0.5);
		float norm_b = pow(norm_b_square, 0.5);
		float scalar_product = pow(scalar_product_square, 0.5);
		float res = 1 - abs(scalar_product / (norm_a * norm_b));
		
		return res;	
	}
	
	float Vecteur::dist_temp(const Vecteur& b) const 
	{
		return abs(getTime() - b.getTime());
	}



//Matrice
	
	Matrice::Matrice(int size_x, int size_y, int t, float value) 
		: raw_matrix<float>(size_x, size_y, N_CARAC, value)
	{
		timestamp = t;
	}
	
	Matrice::Matrice(const std::string& namefile, int t)
		: raw_matrix<float>(namefile)
	{
		timestamp = t;
	}

	Matrice::~Matrice()
	{
		//okqy
	}
	

	Matrice& Matrice::operator= (const Matrice& other)
	{
		if(this != &other)
		{
			number_of_fields = other.number_of_fields;
			sizes = new int[other.number_of_fields];
			data = new float[other.total_size];
			total_size = other.total_size;
			memcpy(sizes, other.sizes, number_of_fields);
			memcpy(data, other.data, total_size);
		}
		else
		{
			return	*this;
		}
	}

	int Matrice::get_timestamp() const
	{
		return timestamp;
	}


	float Matrice::get_value(int i, int j, int k) const
	{
		int coor[] = {i, j, k};
		return raw_matrix<float>::get_value(coor);
	}
	
	void Matrice::set_value(int i, int j, int  k, float value)
	{
		int coor[] = {i, j, k};
		raw_matrix<float>::set_value(coor, value);
	}
	
	Vecteur Matrice::getVector(int i, int j) const
	{
		Point p(i, j);
		Vecteur res(p, 0.0, timestamp);
		for(int k = 0 ; k < N_CARAC ; k++)
		{
			res.set_value(k, get_value(i, j , k));
			//std::cout << res.get_value(k) << std::endl;
		}
		return res;
	}
	
	void Matrice::replaceVector(int i, int j, const Vecteur& v)
	{
	
		for(int k = 0 ; k < N_CARAC ; k++)
		{
			set_value(i, j, k,  v.get_value(k));
		//	std::cout << v.get_value(k) << "::" << get_value(i, j, k) << std::endl;
		}
	}

	void Matrice::save_in_file(const std::string& namefile) const
	{
		FILE* fs;
		fs = fopen(namefile.c_str(), "wb+");
		raw_matrix::save_in_file(fs);
		fwrite(&timestamp, sizeof(int), 1, fs);
		fclose(fs);
	}

	void Matrice::resetTimestamp()
	{
		timestamp = 0;
	}

//HeatMap

    HeatMap::HeatMap(float c_rate) : 
    	raw_matrix<float>(MAX_X, MAX_Y, 1.0)
    {
    	cooling_rate = c_rate;
    }

    
    HeatMap::HeatMap(const std::string& n, float rate) : 
    	raw_matrix<float>(n)
    {
    	cooling_rate = rate;
    }

    HeatMap::HeatMap() : 
    	raw_matrix<float>(MAX_X, MAX_Y, 1.0)
    {
    	cooling_rate = 0.1;
    }

    HeatMap::~HeatMap()
    {
    	//nothing to do here
    }

    void HeatMap::heat(Vecteur v, const Kohonen & khn_map)
    {
        Point p = khn_map.plusProchePoint(v);
        int i = p.getX();
        int j = p.getY();
        set_value(i, j, get_value(i, j) + 1);
    }

    void HeatMap::cool(float taux)
    {
        for (int i = 0; i < MAX_X ; i++)
        {
            for (int j=0 ; j < MAX_Y ; j++)
            {
                if (get_value(i, j) - cooling_rate > 0)
                {
                	set_value(i, j, get_value(i, j) - cooling_rate);
                }
                else
                {
					set_value(i, j, 0.0); 
				}
            }
        }
    }

    void HeatMap::print() const
    {
        for (int i = 0; i < MAX_X ; i++)
        {
        	std::cout << "[" ;
            for (int j=0 ; j < MAX_Y ; j++)
            {
            	std::cout << get_value(i, j) << "; ";
            }
            std::cout << "]" << std::endl;
        }
    }


  	float HeatMap::get_value(int i, int j) const
  	{
  		int coordonnees[] = {i, j};
  		return raw_matrix<float>::get_value(coordonnees);
  	}

  	void HeatMap::set_value(int i, int j, float v)
  	{
  		int coordonnees[] = {i, j};
  		raw_matrix<float>::set_value(coordonnees, v);
  	}

  	void HeatMap::save(const std::string& namefile) const
  	{
  		FILE* fs;
		fs = fopen(namefile.c_str(), "wb+");
		raw_matrix::save_in_file(fs);
		fwrite(&cooling_rate, sizeof(float), 1, fs);
		fclose(fs);
  	}

  	HeatMap& HeatMap::operator= (const HeatMap& other)
	{
		if(this != &other)
		{
			number_of_fields = other.number_of_fields;
			sizes = new int[other.number_of_fields];
			data = new float[other.total_size];
			total_size = other.total_size;
			memcpy(sizes, other.sizes, number_of_fields);
			memcpy(data, other.data, total_size);
			cooling_rate = other.cooling_rate;
		}
		else
		{
			return	*this;
		}
	}
}