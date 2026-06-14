# ============================================================================
# QGroundControl Custom Branding Plugin
# ============================================================================

message(STATUS "QGC: Adding custom branding plugin")

# Multi-config generators (Visual Studio/Xcode) should not use CMAKE_BUILD_TYPE.
# Keeping it empty ensures upstream MockLink debug-only gating behaves correctly.
if(CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE STREQUAL "")
    message(STATUS "QGC: Clearing CMAKE_BUILD_TYPE for multi-config generator: ${CMAKE_BUILD_TYPE}")
    set(CMAKE_BUILD_TYPE "" CACHE STRING "Build type (single-config generators only)" FORCE)
endif()

# Custom Android package overlay.
if(ANDROID)
    set(CUSTOM_ANDROID_DIR "${CMAKE_SOURCE_DIR}/custom/android")
    if(EXISTS "${CUSTOM_ANDROID_DIR}")
        file(GLOB CUSTOM_ANDROID_FILES "${CUSTOM_ANDROID_DIR}/*")
        if(CUSTOM_ANDROID_FILES)
            set(DEFAULT_ANDROID_DIR "${CMAKE_SOURCE_DIR}/android")
            set(FINAL_ANDROID_DIR "${CMAKE_BINARY_DIR}/custom/android")

            file(COPY "${DEFAULT_ANDROID_DIR}/." DESTINATION "${FINAL_ANDROID_DIR}")
            execute_process(COMMAND ${CMAKE_COMMAND} -E copy_directory "${CUSTOM_ANDROID_DIR}" "${FINAL_ANDROID_DIR}")

            set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS
                "${DEFAULT_ANDROID_DIR}/"
                "${CUSTOM_ANDROID_DIR}/"
            )

            set(QGC_ANDROID_PACKAGE_SOURCE_DIR "${FINAL_ANDROID_DIR}" CACHE PATH "Path to a custom Android package template" FORCE)
            message(STATUS "QGC: Android package template path set to: ${QGC_ANDROID_PACKAGE_SOURCE_DIR}")
        endif()
    endif()
endif()

# Add custom Qt resources.
list(APPEND QGC_RESOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/custom.qrc
)
set(QGC_RESOURCES ${QGC_RESOURCES} CACHE STRING "Paths to .qrc Resources" FORCE)

# Custom plugin sources.
set(CUSTOM_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/CustomPlugin.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/CustomPlugin.h
    CACHE INTERNAL "" FORCE
)

# No extra libraries are required for branding-only customization.
set(CUSTOM_LIBRARIES
    CACHE INTERNAL "" FORCE
)

set(CUSTOM_INCLUDE_DIRECTORIES
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    CACHE INTERNAL "" FORCE
)

set(CUSTOM_DEFINITIONS
    QGC_CUSTOM_BUILD
    CUSTOMHEADER="CustomPlugin.h"
    CUSTOMCLASS=CustomPlugin
    CACHE INTERNAL "" FORCE
)

set(CUSTOM_QT_COMPONENTS
    Core
    CACHE INTERNAL "" FORCE
)
