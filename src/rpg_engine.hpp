#ifndef RPG_ENGINE_HPP
#define RPG_ENGINE_HPP

#include <string>
#include <vector>
#include <memory>

// ==========================================
// CLASSE 1: Item (Equipamento)
// ==========================================
class Item {
private:
    std::string name_;
    int bonus_damage_; // Membros privados com sufixo "_"

public:
    Item(const std::string& name, int bonus); // Construtor
    ~Item(); // Destrutor observavel

    // Getters const
    std::string name() const;
    int bonus_damage() const;
    
    // Logica real
    int calculate_stat_scaling(int attribute_points) const;
};

// ==========================================
// CLASSE 2: Character (Personagem)
// ==========================================
class Character {
private:
    std::string name_;
    int health_;
    int strength_;
    std::unique_ptr<Item> equipped_item_; // Q4: unique_ptr para Composicao

public:
    Character(const std::string& name, int health, int strength, const std::string& item_name, int item_bonus);
    ~Character();

    std::string name() const;
    int health() const;
    const Item* equipped_item() const;
    
    // Logica real
    void heal_points(int amount);
};

// ==========================================
// CLASSE 3: QuestLog (Registro de Missoes)
// ==========================================
class QuestLog {
private:
    std::string active_quest_;
    int experience_reward_;

public:
    QuestLog();
    ~QuestLog();

    std::string active_quest() const;
    
    // Logica real
    void accept_quest(const std::string& title, int xp);
};

// ==========================================
// CLASSE 4: Party (Grupo de Aventureiros)
// ==========================================
class Party {
private:
    std::string party_name_;
    std::vector<const Character*> members_; // Agregacao (ponteiros observadores)

public:
    Party(const std::string& name);
    ~Party();

    void join_party(const Character* hero);
    
    // Logica real
    void show_status() const;
};

#endif // RPG_ENGINE_HPP
