# find_package(Flatbuffers REQUIRED)
set(FLATBUFFERS_FLATC_EXECUTABLE "C:/Users/spggo/.conan/data/flatbuffers/1.11.0/_/_/package/f26537b056c9ff213dcc2874372b233408a3e04e/bin/bin/flatc")

function(FLATBUFFERS_GENERATE_C_HEADERS Name)
  set(FLATC_OUTPUTS)
  foreach(FILE ${ARGN})
    get_filename_component(FLATC_OUTPUT ${FILE} NAME_WE)
    set(FLATC_OUTPUT
      "${CMAKE_CURRENT_BINARY_DIR}/${FLATC_OUTPUT}_generated.h")
    list(APPEND FLATC_OUTPUTS ${FLATC_OUTPUT})
  
    add_custom_command(OUTPUT ${FLATC_OUTPUT}
      COMMAND ${FLATBUFFERS_FLATC_EXECUTABLE}
      ARGS -c -o "${CMAKE_CURRENT_BINARY_DIR}/" ${FILE}
      DEPENDS ${FILE}
      COMMENT "Building C++ header for ${FILE}"
      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
  endforeach()
  set(${Name}_OUTPUTS ${FLATC_OUTPUTS} PARENT_SCOPE)
endfunction()
