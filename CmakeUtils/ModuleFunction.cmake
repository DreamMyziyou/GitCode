function(make_static_module MODULE_NAME MODULE_DIR)
    # add library
    file(GLOB_RECURSE CPP_SOURCES ${MODULE_DIR} "*.h" "*.cpp")
    add_library(${MODULE_NAME} STATIC ${CPP_SOURCES})
endfunction()

function(make_shared_module MODULE_NAME MODULE_DIR)
    # add build definition
    set(BUILD_DEFINITION "${MODULE_NAME}_build")
    string(TOUPPER ${BUILD_DEFINITION} BUILD_DEFINITION)
    add_compile_definitions(${BUILD_DEFINITION})
    # add library
    file(GLOB_RECURSE CPP_SOURCES ${MODULE_DIR} "*.h" "*.cpp")
    add_library(${MODULE_NAME} SHARED ${CPP_SOURCES})
endfunction()