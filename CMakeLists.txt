cmake_minimum_required(VERSION 3.15)
project(RpgEngine POO)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Apenas os dois arquivos .cpp sao necessários agora
add_executable(meu_exe 
    src/main.cpp
    src/rpg_engine.cpp
)

# Flags obrigatorias do roteiro de avaliacao
target_compile_options(meu_exe PRIVATE -Wall -Wextra)

# Ativacao do AddressSanitizer para checagem da Q4 Extra
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(meu_exe PRIVATE -fsanitize=address,undefined)
    target_link_options(meu_exe PRIVATE -fsanitize=address,undefined)
endif()
