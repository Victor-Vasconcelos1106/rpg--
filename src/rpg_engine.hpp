#ifndef RPG_ENGINE_HPP
#define RPG_ENGINE_HPP

#include <string>
#include <vector>
#include <memory>

// ==========================================
// Q1 & TP1: Item (Composição do Personagem)
// ==========================================
class Item {
private:
    std::string name_;
    int bonus_damage_;

public:
    Item(const std::string& name, int bonus);
    ~Item();

    std::string name() const;
    int bonus_damage() const;
    int calculate_stat_scaling(int attribute_points) const;
};

// ==========================================
// Q3: Interface Pura (Attackable)
// ==========================================
// Modela a capacidade de receber dano em combate (sem estado, apenas contrato)
class Attackable {
public:
    virtual void take_damage(int amount) = 0; // Método virtual puro
    virtual ~Attackable() = default;          // Destrutor virtual obrigatório
};

// ==========================================
// Q1: Classe Base Abstrata (Character)
// ==========================================
class Character {
private:
    std::string name_;
    int health_;
    std::unique_ptr<Item> equipped_item_; // Composição via Smart Pointer

public:
    Character(const std::string& name, int health, const std::string& item_name, int item_bonus);
    virtual ~Character(); // Q1(A): Destrutor virtual obrigatório

    std::string name() const;
    int health() const;
    void set_health(int health);
    const Item* equipped_item() const;

    // Q1(A): Método virtual puro - obriga implementação nas derivadas
    virtual int calculate_power() const = 0;

    // Q1(A): Método virtual não-puro - provê implementação padrão
    virtual void show_status() const;
};

// ==========================================
// Q1 & Q3: Derivada Concreta 1 (Warrior)
// ==========================================
class Warrior : public Character, public Attackable {
private:
    int armor_rating_;

public:
    Warrior(const std::string& name, int health, int armor, const std::string& item_name, int item_bonus);
    ~Warrior() override;

    // Métodos sobrescritos de Character
    int calculate_power() const override;
    void show_status() const override; // Q1(B): Chama a versão da base via Character::show_status()

    // Método sobrescrito da interface Attackable
    void take_damage(int amount) override;
};

// ==========================================
// Q1 & Q3: Derivada Concreta 2 (Mage - final)
// ==========================================
// Q3(C): Aplicado 'final' na classe para bloquear herança adicional
class Mage final : public Character, public Attackable {
private:
    int mana_points_;

public:
    Mage(const std::string& name, int health, int mana, const std::string& item_name, int item_bonus);
    ~Mage() override;

    // Métodos sobrescritos de Character
    int calculate_power() const override;
    void show_status() const override;

    // Método sobrescrito da interface Attackable
    void take_damage(int amount) override;
};

// ==========================================
// Q2: Função Livre Polimórfica
// ==========================================
// Q2(D): Retorna ponteiro não-proprietário para o elemento com maior poder
const Character* get_strongest_character(const std::vector<std::unique_ptr<Character>>& list);

// ==========================================
// Q3(D): Função Livre que opera sobre a Interface
// ==========================================
void apply_combat_strike(Attackable& target, int damage_amount);

// ==========================================
// TP1: Party (Agregação de Personagens)
// ==========================================
class Party {
private:
    std::string party_name_;
    std::vector<const Character*> members_;

public:
    Party(const std::string& name);
    ~Party();

    void join_party(const Character* hero);
    void show_party_status() const;
};

#endif // RPG_ENGINE_HPP