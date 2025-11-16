file(GLOB_RECURSE CORE_SOURCES CONFIGURE_DEPENDS
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
)

add_library(Core STATIC ${CORE_SOURCES})

target_compile_definitions(Core PRIVATE 
    PROJECT_SOURCE_DIR="${CMAKE_SOURCE_DIR}"
)

set_target_properties(Core PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED ON)

target_include_directories(Core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)