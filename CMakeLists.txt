cmake_minimum_required(VERSION 3.29)

project(marioSokoban)

add_compile_options(-std=c99 -pedantic -W -Wall -Wextra -Wc++-compat -Werror) # -ggdb)

add_executable(marioSokoban fichiers.c editeur.c jeu.c main.c)

target_link_libraries(marioSokoban SDL SDL_image pthread)

install(TARGETS marioSokoban RUNTIME DESTINATION bin)
