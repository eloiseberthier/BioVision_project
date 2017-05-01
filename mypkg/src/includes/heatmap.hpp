#pragma once
#include "psc_utils.hpp"
#include "kohonen.hpp"
#include <string>

namespace psc_utils
{
	class HeatMap : raw_matrix<float>
	{
	public:
	    float cooling_rate;
		HeatMap(float c_rate);
		HeatMap();
		HeatMap(const std::string& n, float rate);
	   ~HeatMap();
	   	float get_value(int i, int j) const;
	   	void set_value(int i, int j, float v);
	    void heat(Vecteur v, const Kohonen & khn);
	    void cool(float taux);	
	    void save(const std::string& namefile) const;
		void print() const;
		HeatMap& operator= (const HeatMap& other);

	};
}
