cmake_minimum_required(VERSION 3.15)
project(RpgEngine_TP2 VERSION 2.0 LANGUAGES CXX)

# Exige o padrao C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Exporta comandos de compilacao (util para autocompletar e LSPs)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# -----------------------------------------------------------------------------
# 1. EXECUTÁVEL PRINCIPAL (Aplicação do Jogo/Simulação)
# -----------------------------------------------------------------------------
add_executable(meu_sistema
    src/main.cpp
    src/rpg_engine.cpp
)

# Diretorio de inclusao de cabecalhos
target_include_directories(meu_sistema PRIVATE src)

# Flags de compilacao estritas obrigatorias (-Wall -Wextra)
target_compile_options(meu_sistema PRIVATE -Wall -Wextra)

# Configuração do AddressSanitizer para o modo Debug (Questao 2 / Teste 6)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Modo Debug ativado: Habilitando AddressSanitizer e UndefinedBehaviorSanitizer")
    target_compile_options(meu_sistema PRIVATE -g -fsanitize=address,undefined)
    target_link_options(meu_sistema PRIVATE -fsanitize=address,undefined)
endif()

# -----------------------------------------------------------------------------
# 2. QUESTÃO 4 (EXTRA): TESTES AUTOMATIZADOS COM CATCH2 V3 (+1,0 ponto)
# -----------------------------------------------------------------------------
# Para compilar os testes, execute: cmake -B build -DBUILD_TESTS=ON
option(BUILD_TESTS "Habilitar compilacao dos testes automatizados com Catch2" OFF)

if(BUILD_TESTS)
    message(STATUS "Baixando e configurando Catch2 v3.5.2 via FetchContent...")
    
    include(FetchContent)
    FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.5.2
    )
    FetchContent_MakeAvailable(Catch2)

    # Executavel dos testes unitarios
    add_executable(testes
        tests/test_tp2.cpp
        src/rpg_engine.cpp
    )

    target_include_directories(testes PRIVATE src)
    target_compile_options(testes PRIVATE -Wall -Wextra)
    
    # Adiciona Sanitizers aos testes em modo Debug
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_compile_options(testes PRIVATE -g -fsanitize=address,undefined)
        target_link_options(testes PRIVATE -fsanitize=address,undefined)
    endif()

    # Linka com a biblioteca principal do Catch2 com main() automatico
    target_link_libraries(testes PRIVATE Catch2::Catch2WithMain)

    # Integracao com CTest
    include(CTest)
    include(Catch)
    catch_discover_tests(testes)
endif()