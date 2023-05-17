file(GLOB INCLUDES_LIST "include/*.h" )
file(GLOB SOURCES_LIST "src/*.cpp" )


include_directories(../amaris/include)

add_executable(test main.cpp)

# add link to the lib amaris
target_link_libraries(test PUBLIC amaris)

target_compile_features(test PUBLIC cxx_std_17)
