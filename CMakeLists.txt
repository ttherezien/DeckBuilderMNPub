cmake_minimum_required(VERSION 3.27)
project(DeckBuilderMN)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        Network
        REQUIRED
)

add_executable(untitled5 main.cpp
        MainWindows.cpp
        DataLoader.cpp
        DataLoader.h
        DeckBuilder.cpp
        DeckBuilder.h
        VisuCarte.cpp
        VisuCarte.h
)

target_link_libraries(untitled5
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Network
)
