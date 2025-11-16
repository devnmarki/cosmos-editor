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
        ${CMAKE_SOURCE_DIR}/vendor/SDL2/include
)

target_link_libraries(Core
    PUBLIC
        SDL2
        SDL2main
)

add_custom_command(TARGET Core POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:SDL2>
    $<TARGET_FILE_DIR:Core>
)