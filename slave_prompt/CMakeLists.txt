file(GLOB INCLUDES_LIST "include/*.h" )
file(GLOB SOURCES_LIST "src/*.cpp" )

include_directories(../amaris/include)

add_executable(SlavePrompt main.cpp slave_prompt.cpp)

# add link to the lib amaris
target_link_libraries(SlavePrompt PUBLIC amaris)

target_compile_features(SlavePrompt PUBLIC cxx_std_17)
