cmake_minimum_required(VERSION 2.8)

#package and needed includes
project(psc_livrable)
add_definitions(-std=c++11)
find_package(OpenCV REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} )




#setting up the sources


set(source_learn
	kohonen_learn.cpp
	)

set(source_test
	main_test_heat.cpp
)

set(source_psc_utils
	psc_utils.cpp
	matrice.cpp
	image_features.cpp
)

add_library(psc_utils
	${source_psc_utils})

#targets & executable(s)
add_executable(kohonen_learn ${source_learn})
add_executable(kohonen_heat_test ${source_test})

target_link_libraries(kohonen_heat_test ${OpenCV_LIBS} psc_utils)
target_link_libraries(kohonen_learn ${OpenCV_LIBS} psc_utils)
