cmake_minimum_required(VERSION 3.5)

project(Ray-tracing VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(GLEW 2.0 REQUIRED)
find_package(glfw3 REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        Hittable.hpp
        Utilities.hpp
        Utilities.cpp
        Ray.cpp
        Ray.hpp
        Triangle.h
        Triangle.cpp
        Camera.hpp
        Camera.cpp
        ImageRenderer.cpp
        ImageRenderer.h
        ecs.h
        engine.h
        engineCamera.h
        engine.cpp
        shader.h
        imconfig.h

        imgui/imgui.cpp
        imgui/imgui_demo.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_tables.cpp
        imgui/imgui_widgets.cpp
        imgui/backends/imgui_impl_glfw.cpp
        imgui/backends/imgui_impl_opengl3.cpp
        imgui/imgui.h
        imgui/imconfig.h
        imgui/imgui_internal.h
        imgui/imstb_rectpack.h
        imgui/imstb_textedit.h
        imgui/imstb_truetype.h
        imgui/backends/imgui_impl_glfw.h
        imgui/backends/imgui_impl_opengl3.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Ray-tracing
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Ray-tracing APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Ray-tracing SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Ray-tracing
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Ray-tracing PRIVATE Qt${QT_VERSION_MAJOR}::Widgets GLEW::GLEW glfw)


# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Ray-tracing)
endif()
set_target_properties(Ray-tracing PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Ray-tracing
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Ray-tracing)
endif()
