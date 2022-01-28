cmake_minimum_required(VERSION 3.10)

set(GAME hag)

project(${GAME}
  VERSION 0.1.0
)

include(GNUInstallDirs)

find_package(gf REQUIRED COMPONENTS graphics)
find_package(SFML REQUIRED COMPONENTS audio)

if (UNIX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
endif ()

set(GAME_DATADIR "${CMAKE_INSTALL_PREFIX}/share/games/${GAME}" CACHE PATH "Game Data Dir")
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/code/config.h.in ${CMAKE_CURRENT_BINARY_DIR}/config.h @ONLY)

add_executable(${GAME}
  code/main.cc
  code/bits/AudioManager.cc
  code/bits/GameData.cc
  code/bits/GameHub.cc
  code/bits/GameState.cc
  code/bits/LayerEntity.cc
  code/bits/LevelScene.cc
  code/bits/StartScene.cc
  code/bits/TitleEntity.cc
)

target_include_directories(${GAME}
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/code
    ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(${GAME}
  PRIVATE
    gf::graphics
    sfml-audio
)

install(
  TARGETS ${GAME}
  RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
)

install(
  DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/data/${GAME}"
  DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/games"
)

# tools

add_executable(tiles code/tiles.cc)
target_link_libraries(tiles gf::core)
