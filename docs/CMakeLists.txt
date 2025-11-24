find_package(Sphinx)

if(Sphinx_FOUND)
  add_sphinx_document(
      documentation
      CONF_FILE "${CMAKE_CURRENT_LIST_DIR}/src/conf.py"
      SKIP_PDF
      "${CMAKE_CURRENT_LIST_DIR}/src/_ext/requirement.py"
      "${CMAKE_CURRENT_LIST_DIR}/src/_static/css/custom.css"
      "${CMAKE_CURRENT_LIST_DIR}/src/assets/logo.svg"
      "${CMAKE_CURRENT_LIST_DIR}/src/assets/favicon.ico"
      "${CMAKE_CURRENT_LIST_DIR}/src/assets/wishbone-read.svg"
      "${CMAKE_CURRENT_LIST_DIR}/src/assets/wishbone-write.svg"
      "${CMAKE_CURRENT_LIST_DIR}/src/assets/traceability.svg"
      "${CMAKE_CURRENT_LIST_DIR}/src/index.rst"
      "${CMAKE_CURRENT_LIST_DIR}/src/spec/index.rst"
      "${CMAKE_CURRENT_LIST_DIR}/src/spec/1_introduction.rst"
      "${CMAKE_CURRENT_LIST_DIR}/src/spec/2_overall-description.rst"
      "${CMAKE_CURRENT_LIST_DIR}/src/spec/3_requirements.rst"
      "${CMAKE_CURRENT_LIST_DIR}/src/spec/4_configuration.rst"
      "${CMAKE_CURRENT_LIST_DIR}/src/spec/5_architecture.rst"
    )
else()
  message(WARNING "No Sphinx found. Documentation target not available.")
endif()
