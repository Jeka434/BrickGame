cmake_minimum_required(VERSION 3.5)

project(BrickGame_desktop VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 COMPONENTS Widgets Core Gui REQUIRED)

set(PROJECT_SOURCES
        mainwindow.h mainwindow.cc mainwindow.ui
        gamewidget.cc gamewidget.h
        tetriswidget.h tetriswidget.cc
        snakewidget.h snakewidget.cc
        racewidget.cc racewidget.h
        main.cc

        ../../brick_game/tetris/inc/figures.h
        ../../brick_game/tetris/inc/fsm.h
        ../../brick_game/tetris/inc/objects.h
        ../../brick_game/tetris/inc/tetris.h
        ../../brick_game/tetris/figures.c
        ../../brick_game/tetris/fsm.c
        ../../brick_game/tetris/tetris.c

        ../../brick_game/snake/controller/controller.h ../../brick_game/snake/controller/controller.cc
        ../../brick_game/snake/model/model.h ../../brick_game/snake/model/model.cc

        ../requests/race_requests.cc ../requests/race_requests.h
)

add_executable(BrickGame_desktop ${PROJECT_SOURCES})
target_include_directories(BrickGame_desktop PRIVATE
    ../../brick_game/snake/controller
    ../../brick_game/snake/model
    ../../brick_game/tetris/inc
    ../../brick_game/common)
target_link_libraries(BrickGame_desktop Qt::Widgets Qt::Core Qt::Gui)

if(WIN32)
    target_link_libraries(BrickGame_desktop wsock32 ws2_32)
endif()

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
    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()
