file(GLOB INCLUDES_LIST "include/*.h" )
file(GLOB SOURCES_LIST "src/*.cpp" )


include_directories(include)

add_library(amaris SHARED ${SOURCES_LIST} ${INCLUDES_LIST})

add_compile_definitions(AMARIS_EXPORT)

target_compile_features(amaris PUBLIC cxx_std_17)
