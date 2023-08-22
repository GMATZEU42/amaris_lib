file(GLOB INCLUDES_LIST "include/*.h" )
file(GLOB SOURCES_LIST "src/*.cpp" )

include_directories(../amaris/include)

add_executable(ComNucleoApp main.cpp com_nucleo.cpp)

# add link to the lib amaris
target_link_libraries(ComNucleoApp PUBLIC amaris)

target_compile_features(ComNucleoApp PUBLIC cxx_std_17)
