#pragma once
#include "psc_utils.hpp"
#include <cstdio>
#include <string>

namespace psc_utils
{
	template<typename T>
	class raw_matrix
	{
	protected:
		T* data;
		int number_of_fields;
		int* sizes;
		int total_size;
	
	public:
		raw_matrix();
		raw_matrix(const raw_matrix<T>& other);
		raw_matrix(int n, int s[], const T& d_val);
		raw_matrix(int s_x, int s_y, int s_z,const T& d_val);
		raw_matrix(int s_x, int s_y, const T& d_val);
		raw_matrix(int s, const T& d_val);
		raw_matrix(const std::string& namefile);
		raw_matrix<T>& operator= (const raw_matrix<T>& other);
		~raw_matrix();
		T get_value(int coor[]) const;
		void set_value(int coor[], const T& value);
		void save_in_file(const std::string& namefile) const;
		void save_in_file(FILE* fs) const;

	};
	
	
	class Vecteur : public raw_matrix<float>
	{
	private: 
		Point position;
		int timestamp;
	public:
		Vecteur(Point p, float d_value, int t);
		Vecteur(float* c, Point p, int t);
	    ~Vecteur();
	    Vecteur(const Vecteur& other);
	    void print() const;
	    float get_value(int k) const;
	    void set_value(int coor, float value);
	    Point getPosition() const;
	    int getTime() const;
	    Vecteur difference(const Vecteur& other);
	    float distance(int numDistance, const Vecteur& other) const;
	    Vecteur operator*(float c) const;
	    Vecteur operator+(const Vecteur& other) const;
		Vecteur operator-(const Vecteur& other) const;
		float norm1(const Vecteur& b) const;
		float norm2(const Vecteur& b) const;
		float dist_cos(const Vecteur& b) const;
		float dist_temp(const Vecteur& b) const;
	};
	
	
	class Matrice : public raw_matrix<float>
	{
	private:
		int timestamp;
	
	public:
		Matrice(int size_x, int size_y, int t, float value);
		Matrice(const std::string& namefile, int t);
		~Matrice();
		int get_timestamp() const;
		float get_value(int i, int j, int  k) const;
		void set_value(int i, int j, int  k, float value);
		Vecteur getVector(int i, int j) const;
		void replaceVector(int i, int j, const Vecteur&  v); 
		void resetTimestamp();
		void save_in_file(const std::string& namefile) const;
		void save_in_file(FILE* fs) const;
		Matrice& operator= (const Matrice& other);


	};
}