cmake_minimum_required(VERSION 3.0.2)
project(array)

option(USE_BOOST "Using <boost> to access c++11 features" OFF)

add_executable(${PROJECT_NAME}
	main.cpp
	CRandom.cpp
	CArrayException.cpp
)

if(USE_BOOST)
	target_compile_definitions(${PROJECT_NAME}
		PRIVATE USE_BOOST
	)
	find_package(Boost REQUIRED)

	target_include_directories(${PROJECT_NAME}
		PRIVATE	${Boost_INCLUDE_DIRS}
			${Boost_INCLUDE_DIRS}/boost
	)
endif(USE_BOOST)

target_include_directories(${PROJECT_NAME}
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/
)