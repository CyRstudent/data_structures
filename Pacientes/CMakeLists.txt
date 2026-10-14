cmake_minimum_required(VERSION 3.20) # Version minima de cmake

project(examen_cola_pacientes C)

add_compile_options(-std=c17 -Wall -Wextra -Wpedantic)  # Para todo el proyecto, las opciones de compilacion

add_executable(main src/main.c src/cola.c) # Añadir ejecutable, tantos como tengas en tu workspace.
