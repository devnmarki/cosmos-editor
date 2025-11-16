file(GLOB_RECURSE COSMOS_SOURCES CONFIGURE_DEPENDS 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
)

add_executable (CosmosEditor ${COSMOS_SOURCES})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CosmosEditor PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Core
)
