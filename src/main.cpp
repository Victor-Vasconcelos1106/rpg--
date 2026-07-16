#include <iostream>
#include <vector>
#include <memory>
#include "rpg_engine.hpp"

int main() {
    std::cout << "===============================================\n";
    std::cout << "   TESTES DO TRABALHO PRATICO 2 - POO (RPG)    \n";
    std::cout << "===============================================\n\n";

    // ----------------------------------------------------
    // Q1(C) - DEMONSTRAÇÃO DO DESTRUTOR VIRTUAL
    // ----------------------------------------------------
    std::cout << "--- [Q1] Teste do Destrutor Virtual ---\n";
    {
        // Ponteiro para base apontando para objeto derivado
        Character* base_ptr = new Warrior("Thorin", 100, 15, "Machado de Guerra", 20);
        std::cout << "Deletando objeto derivado via ponteiro para a Base:\n";
        delete base_ptr; // Deve chamar ~Warrior() e depois ~Character()
    }
    std::cout << "Destruicao encadeada confirmada com sucesso!\n\n";

    // ----------------------------------------------------
    // Q2 - POLIMORFISMO DINÂMICO E VECTOR DE UNIQUE_PTR
    // ----------------------------------------------------
    std::cout << "--- [Q2] Polimorfismo Dinamico com vector<unique_ptr<Character>> ---\n";
    std::vector<std::unique_ptr<Character>> roster;

    // Q2(A): Adicionando instâncias derivadas usando make_unique
    roster.push_back(std::make_unique<Warrior>("Conan", 150, 20, "Espada Bastarda", 35));
    roster.push_back(std::make_unique<Mage>("Gandalf", 80, 100, "Cajado da Luz", 40));
    roster.push_back(std::make_unique<Warrior>("Arthur", 120, 18, "Excalibur", 50));

    std::cout << "\nIterando o vetor e chamando metodos virtuais:\n";
    // Q2(B): Iteração polimórfica via referência constante
    for (const auto& hero : roster) {
        hero->show_status(); // Despacho dinâmico correto para Warrior ou Mage
    }

    // Q2(D): Função livre polimórfica que retorna o herói mais forte
    const Character* strongest = get_strongest_character(roster);
    if (strongest) {
        std::cout << "\n-> Heroi mais forte detectado: " << strongest->name() 
                  << " com " << strongest->calculate_power() << " de Poder.\n";
    }

    // ----------------------------------------------------
    // Q3 - DEMONSTRAÇÃO DA INTERFACE PURA POR REFERÊNCIA
    // ----------------------------------------------------
    std::cout << "\n--- [Q3] Interface Pura (Attackable) e Heranca Multipla ---\n";
    Warrior tank_warrior("Guts", 200, 30, "Dragonslayer", 60);
    
    // Q3(D): Passa o objeto derivado para uma função que só aceita a Interface Attackable
    apply_combat_strike(tank_warrior, 50);

    // ----------------------------------------------------
    // DEMONSTRAÇÃO DA AGREGAÇÃO (PARTY) DO TP1 MANTIDA
    // ----------------------------------------------------
    {
        Party guild("Os Vingadores de Arda");
        guild.join_party(&tank_warrior);
        guild.join_party(roster[1].get()); // Gandalf
        guild.show_party_status();
    }

    // Q2(C): Limpeza automática e segura do vetor de unique_ptr
    std::cout << "\n--- [Q2(C)] Encerrando vetor e destruindo objetos polimorficos ---\n";
    roster.clear(); // Invoca destrutores das derivadas e da base limpos e sem leak!

    std::cout << "\n===============================================\n";
    std::cout << "   SIMULACAO CONCLUIDA COM SUCESSO!            \n";
    std::cout << "===============================================\n";

    return 0;
}