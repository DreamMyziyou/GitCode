find_package(Vulkan REQUIRED COMPONENTS glslc)
find_program(glslc_executable NAMES glslc HINTS Vulkan::glslc)

set(MODULE_NAME ShaderCompiler)
set(SHADER_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR})
set(SHADER_BINARY_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Shader)

file(GLOB SHADERS
        ${SHADER_SOURCE_DIR}/*.vert
        ${SHADER_SOURCE_DIR}/*.frag
        ${SHADER_SOURCE_DIR}/*.comp
        ${SHADER_SOURCE_DIR}/*.geom
        ${SHADER_SOURCE_DIR}/*.tesc
        ${SHADER_SOURCE_DIR}/*.tese
        ${SHADER_SOURCE_DIR}/*.mesh
        ${SHADER_SOURCE_DIR}/*.task
        ${SHADER_SOURCE_DIR}/*.rgen
        ${SHADER_SOURCE_DIR}/*.rchit
        ${SHADER_SOURCE_DIR}/*.rmiss)

add_custom_command(
        COMMAND ${CMAKE_COMMAND} -E make_directory ${SHADER_BINARY_DIR}
        OUTPUT ${SHADER_BINARY_DIR}
        COMMENT "Creating ${SHADER_BINARY_DIR}"
)

foreach (SOURCE_SHADER IN LISTS SHADERS)
    get_filename_component(FILENAME ${SOURCE_SHADER} NAME)
    add_custom_command(
            COMMAND ${glslc_executable} -o ${SHADER_BINARY_DIR}/${FILENAME}.spv ${SOURCE_SHADER}
            OUTPUT ${SHADER_BINARY_DIR}/${FILENAME}.spv
            DEPENDS ${source} ${SHADER_BINARY_DIR}
            COMMENT "Compiling ${FILENAME}"
    )
    list(APPEND SPV_SHADERS ${SHADER_BINARY_DIR}/${FILENAME}.spv)
endforeach ()

add_custom_target(${MODULE_NAME} ALL DEPENDS ${SPV_SHADERS})