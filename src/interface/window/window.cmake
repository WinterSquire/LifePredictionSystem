# ui文件需要被编译成.h文件，所以ui文件发生的改变需要运行两次才能应用

set(SRC_INTERFACE_WINDOW_FILES
        ${CMAKE_SOURCE_DIR}/src/interface/window/mainWindow/MainWindow.ui
        ${CMAKE_SOURCE_DIR}/src/interface/window/mainWindow/MainWindow.h
        ${CMAKE_SOURCE_DIR}/src/interface/window/mainWindow/MainWindow.cpp

        ${CMAKE_SOURCE_DIR}/src/interface/window/test/window1/Window1.ui
        ${CMAKE_SOURCE_DIR}/src/interface/window/test/window1/Window1.h
        ${CMAKE_SOURCE_DIR}/src/interface/window/test/window1/Window1.cpp
)