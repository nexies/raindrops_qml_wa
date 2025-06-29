cmake_minimum_required(VERSION 3.16)

project(MathRaindrops VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(math_raindrops
    main.cpp
)

qt_add_qml_module(math_raindrops
    URI math_raindrops
    VERSION 1.0
    QML_FILES
        Main.qml
        SOURCES cpp/core/raindrops_game_engine.h cpp/core/raindrops_game_engine.cpp
        SOURCES cpp/core/t_math_expression.h cpp/core/t_math_expression.cpp
        SOURCES raindrops.h
        SOURCES cpp/qml_types/raindrops_drop.h cpp/qml_types/raindrops_drop.cpp
        SOURCES cpp/core/raindrops_qml_application_engine.h cpp/core/raindrops_qml_application_engine.cpp
)

target_include_directories(math_raindrops
    PRIVATE
        cpp/core
        cpp/qml_types
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(math_raindrops PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appWebAssemblyQML
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(math_raindrops
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS math_raindrops
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
