include(${CMAKE_SOURCE_DIR}/src/core/core.cmake)
include(${CMAKE_SOURCE_DIR}/src/python/python.cmake)
include(${CMAKE_SOURCE_DIR}/src/interface/interface.cmake)

set (SRC_FILES
        ${SRC_PYTHON_FILES}
        ${SRC_CORE_FILES}
        ${SRC_INTERFACE_FILES}
)