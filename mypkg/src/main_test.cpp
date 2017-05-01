#include <iostream>
#include "includes/psc_utils.hpp"
#include "includes/kohonen.hpp"
#include "includes/heatmap.hpp"
#include "includes/imagefeatures.hpp"

int main(int argc, char* argvc[])
{
	/*if(argc != 1)
	{
		return 1;
	}
*/
	psc_utils::ImageFeatures test_image(argvc[1], 0);
	psc_utils::Kohonen test_carte(1, 0.2, 1.1, 0);
	std::cout << "Kohonen was successfully created" << std::endl;
	//psc_utils::Vecteur v(psc_utils::Point(0,1), 1.0, 0);
	std::cout << "v is created" << std::endl;
//	psc_utils::Vecteur vv(psc_utils::Point(0,1), 1.0, 0);
	std::cout << "vv is created" << std::endl;
	test_carte.randomInit();
	psc_utils::Vecteur a = test_carte.getVector(2, 2);
	psc_utils::Vecteur aa = test_image.getVector(2, 3);
		//a.print();

	std::cout << "We can get a value somewhere" << std::endl;
	//test_carte.evolution(a, 0.1, 0.1);
	std::cout << "We can evolve" << std::endl;
	//test_carte.save("blabla");
	std::cout << "We can save it" << std::endl;

	return 0;
}