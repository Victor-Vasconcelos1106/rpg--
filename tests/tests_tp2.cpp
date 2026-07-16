#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include <memory>
#include <vector>
#include "rpg_engine.hpp"

// TEST_CASE 1 (Q1): Destruição encadeada em hierarquia de herança
TEST_CASE("Q1 - Construtores e Destrutores em Hierarquia", "[Q1][Herança]") {
    // Instancia via ponteiro para a base abstrata
    Character* hero_ptr = new Warrior("Arthur", 100, 15, "Excalibur", 20);
    
    REQUIRE(hero_ptr->name() == "Arthur");
    REQUIRE(hero_ptr->health() == 100);
    
    // Testa o destrutor virtual garantindo limpa segura
    delete hero_ptr;
}

// TEST_CASE 2 (Q2): Polimorfismo e Cálculo de Poder com Catch2
TEST_CASE("Q2 - Polimorfismo Dinamico e Vector de Unique Pointers", "[Q2][Polimorfismo]") {
    std::vector<std::unique_ptr<Character>> roster;
    
    roster.push_back(std::make_unique<Warrior>("Conan", 150, 20, "Espada Bastarda", 35));
    roster.push_back(std::make_unique<Mage>("Gandalf", 80, 100, "Cajado da Luz", 40));

    // Warrior: (150 * 2) + 20 + 35 = 355
    REQUIRE(roster[0]->calculate_power() == 355);

    // Mage: 80 + (100 * 3) + 40 = 420
    REQUIRE(roster[1]->calculate_power() == 420);

    // Testa a função livre polimórfica
    const Character* strongest = get_strongest_character(roster);
    REQUIRE(strongest != nullptr);
    REQUIRE(strongest->name() == "Gandalf");
}

// TEST_CASE 3 (Q3): Interface Pura por Referência
TEST_CASE("Q3 - Interface Pura Attackable", "[Q3][Interface]") {
    Warrior tank("Guts", 100, 20, "Dragonslayer", 50);

    // Usa a função livre que recebe const Attackable&
    apply_combat_strike(tank, 30); // 30 - (20 / 2) = 20 de dano efetivo

    REQUIRE(tank.health() == 80);
}