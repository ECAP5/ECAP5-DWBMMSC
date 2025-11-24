macro(add_dependency id)
  cmake_parse_arguments(ARG ""
                            "GIT;TAG;BINARY"
                            ""
                            ${ARGN})
  string(MAKE_C_IDENTIFIER "${id}" name)
  string(TOLOWER "${name}" name)

  FetchContent_Declare(${name}
    GIT_REPOSITORY https://github.com/${ARG_GIT}
    GIT_TAG ${ARG_TAG}
    SOURCE_SUBDIR __none__
  )
  FetchContent_MakeAvailable(${name})

  if(NOT DEFINED ${name}_EXECUTABLE)
    if(EXISTS "${${name}_SOURCE_DIR}/pyproject.toml")
      message(STATUS "Configuring ${name}")
      execute_process(COMMAND ${Python3_EXECUTABLE} -m pip install ${${name}_SOURCE_DIR} OUTPUT_QUIET RESULT_VARIABLE rv)
      if("${rv}" STREQUAL "0")
        set(${name}_EXECUTABLE ${VENV_DIR}/bin/${ARG_BINARY} CACHE STRING "path to the ${name} executable")
      endif()
    endif()
  endif()

endmacro()
