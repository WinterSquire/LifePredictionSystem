cmake_minimum_required(VERSION 3.26)
project(LifePredictionSystem LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_BUILD_TYPE Release)

# Output Path
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Qt libs
set(Qt6_LIB Core Gui Widgets Charts OpenGL OpenGLWidgets)

foreach (item ${Qt6_LIB})
    set(Qt6_Link ${Qt6_Link} Qt::${item})
endforeach (item)

find_package(Qt6 COMPONENTS ${Qt6_LIB} REQUIRED)

# Python Path
include_directories(${PYTHON_DIR}/include)
link_directories(${PYTHON_DIR}/libs)

# Python lib debug suffix
set(DEBUG_SUFFIX)
if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
    set(DEBUG_SUFFIX "_d")
endif ()

# build executable
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)

file(GLOB_RECURSE SRC_FILES ${SOURCE_DIR}/*.cpp ${SOURCE_DIR}/*.h ${SOURCE_DIR}/*.ui)

qt_add_resources(QRC_FILES ${CMAKE_SOURCE_DIR}/res/resource.qrc)

add_executable(LifePredictionSystem ${SRC_FILES} ${QRC_FILES})

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ${Qt6_Link} python${PYTHON_VER}${DEBUG_SUFFIX})

if (${CMAKE_GENERATOR} MATCHES "Visual Studio*")
        set(RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_BUILD_TYPE}")
else ()
        set(RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
endif ()

# copy script files
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory
        "${RUNTIME_OUTPUT_DIRECTORY}/script"
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/script"
        "${RUNTIME_OUTPUT_DIRECTORY}/script"
)

# copy ps script file
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_SOURCE_DIR}/install_package.bat"
        "${RUNTIME_OUTPUT_DIRECTORY}/"
)

# copy qt library
if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB ${Qt6_LIB})
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()
