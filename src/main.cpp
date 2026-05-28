#include <iostream>
#include "rpg_engine.hpp"

int main() {
    std::cout << "=== INICIANDO SIMULACAO RPG ===\n\n";

    // 1. Teste de Logica Basica (QuestLog)
    QuestLog diary;
    diary.accept_quest("Matar os Ratos no Porao", 150);
    std::cout << "\n";

    // 2. Teste de AGREGACOES (Objetos independentes do grupo)
    Character* legendary_hero = new Character("Aragorn", 120, 18, "Anduril", 25);
    
    {
        std::cout << "\n--- Entrando no Escopo da Guilda ---\n";
        Party fellowship("Sociedade do Anel");
        
        fellowship.join_party(legendary_hero);
        fellowship.show_status();
        
        std::cout << "--- Saindo do Escopo da Guilda ---\n";
    } // O objeto 'fellowship' morre aqui.
    
    std::cout << "\nFora do escopo da Guilda:\n";
    // Confirmacao de que Aragorn sobreviveu de forma independente à destruicao da Party
    std::cout << "Verificando sobrevivente: " << legendary_hero->name() << " continua vivo.\n\n";

    // 3. Teste de COMPOSICAO (Item morre colado com o Character)
    {
        std::cout << "--- Entrando no Escopo do Combate ---\n";
        Character goblin("Goblin Saqueador", 30, 8, "Adaga Enferrujada", 4);
        
        int scaling = goblin.equipped_item()->calculate_stat_scaling(10);
        std::cout << "Dano escalado da arma do Goblin: " << scaling << "\n";
        goblin.heal_points(15);
        
        std::cout << "--- Saindo do Escopo do Combate ---\n";
    } // 'goblin' sai de escopo: suas mensagens de destruicao e do 'Item' aparecem juntas aqui!

    // Limpeza da memoria alocada para o heroi independente
    delete legendary_hero;

    std::cout << "\n=== FIM DA SIMULACAO RPG ===\n";
    return 0;
}
