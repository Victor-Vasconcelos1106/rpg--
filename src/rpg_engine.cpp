#include "rpg_engine.hpp"
#include <iostream>

// ==========================================
// Item (Implementação)
// ==========================================
Item::Item(const std::string& name, int bonus) 
    : name_(name), bonus_damage_(bonus) {
    std::cout << "  [Item] (" << name_ << ") forjado.\n";
}

Item::~Item() {
    std::cout << "  [~Item] (\"" << name_ << "\") destruido.\n";
}

std::string Item::name() const { return name_; }
int Item::bonus_damage() const { return bonus_damage_; }

int Item::calculate_stat_scaling(int attribute_points) const {
    if (attribute_points <= 0) return bonus_damage_;
    return bonus_damage_ + (attribute_points * 2);
}

// ==========================================
// Character (Implementação da Base)
// ==========================================
Character::Character(const std::string& name, int health, const std::string& item_name, int item_bonus)
    : name_(name), health_(health),
      equipped_item_(std::make_unique<Item>(item_name, item_bonus)) {
    std::cout << " [Character Base] (" << name_ << ") inicializado.\n";
}

Character::~Character() {
    std::cout << " [~Character Base] (\"" << name_ << "\") desalocado.\n";
}

std::string Character::name() const { return name_; }
int Character::health() const { return health_; }
void Character::set_health(int health) { health_ = health; }
const Item* Character::equipped_item() const { return equipped_item_.get(); }

void Character::show_status() const {
    std::cout << "Heroi: " << name_ << " | HP: " << health_ 
              << " | Arma: " << equipped_item_->name();
}

// ==========================================
// Warrior (Implementação Derivada 1)
// ==========================================
Warrior::Warrior(const std::string& name, int health, int armor, const std::string& item_name, int item_bonus)
    : Character(name, health, item_name, item_bonus), armor_rating_(armor) {
    std::cout << "[Warrior] Guerreiro " << name << " pronto para a batalha.\n";
}

Warrior::~Warrior() {
    std::cout << "[~Warrior] Guerreiro " << name() << " caiu em combate.\n";
}

int Warrior::calculate_power() const {
    return (health() * 2) + armor_rating_ + equipped_item()->bonus_damage();
}

void Warrior::show_status() const {
    // Q1(B): Chama explicitamente o método da base antes de complementar
    Character::show_status();
    std::cout << " | Armadura: " << armor_rating_ 
              << " | Poder Total: " << calculate_power() << " (Classe: Guerreiro)\n";
}

void Warrior::take_damage(int amount) {
    int effective_damage = amount - (armor_rating_ / 2);
    if (effective_damage < 0) effective_damage = 0;
    
    set_health(health() - effective_damage);
    if (health() < 0) set_health(0);
    std::cout << name() << " (Guerreiro) absorveu dano com armadura. Recebeu " 
              << effective_damage << " de dano real. HP restante: " << health() << "\n";
}

// ==========================================
// Mage (Implementação Derivada 2)
// ==========================================
Mage::Mage(const std::string& name, int health, int mana, const std::string& item_name, int item_bonus)
    : Character(name, health, item_name, item_bonus), mana_points_(mana) {
    std::cout << "[Mage] Mago " << name << " dominou os arcanos.\n";
}

Mage::~Mage() {
    std::cout << "[~Mage] Mago " << name() << " virou poeira magica.\n";
}

int Mage::calculate_power() const {
    return health() + (mana_points_ * 3) + equipped_item()->bonus_damage();
}

void Mage::show_status() const {
    Character::show_status();
    std::cout << " | Mana: " << mana_points_ 
              << " | Poder Total: " << calculate_power() << " (Classe: Mago)\n";
}

void Mage::take_damage(int amount) {
    int effective_damage = amount;
    // O Mago usa mana para mitigar dano se tiver mana suficiente
    if (mana_points_ > 0) {
        effective_damage /= 2;
        mana_points_ -= 10;
        if (mana_points_ < 0) mana_points_ = 0;
    }
    
    set_health(health() - effective_damage);
    if (health() < 0) set_health(0);
    std::cout << name() << " (Mago) utilizou barreira arcana. Recebeu " 
              << effective_damage << " de dano. HP restante: " << health() << "\n";
}

// ==========================================
// Funções Livres Polimórficas
// ==========================================
const Character* get_strongest_character(const std::vector<std::unique_ptr<Character>>& list) {
    if (list.empty()) return nullptr;
    
    const Character* strongest = list[0].get();
    for (const auto& hero : list) {
        if (hero->calculate_power() > strongest->calculate_power()) {
            strongest = hero.get();
        }
    }
    return strongest;
}

void apply_combat_strike(Attackable& target, int damage_amount) {
    std::cout << "-> Desferindo golpe de teste pela Interface Attackable...\n";
    target.take_damage(damage_amount); // Despacho dinâmico via vtable da interface
}

// ==========================================
// Party (Agregação)
// ==========================================
Party::Party(const std::string& name) : party_name_(name) {
    std::cout << "\n[Party] Guilda \"" << party_name_ << "\" formada.\n";
}

Party::~Party() {
    std::cout << "[~Party] Guilda \"" << party_name_ << "\" dissolvida (integrantes persistem).\n";
}

void Party::join_party(const Character* hero) {
    if (hero != nullptr) {
        members_.push_back(hero);
    }
}

void Party::show_party_status() const {
    std::cout << "--- INTEGRANTES DA GUILDA: " << party_name_ << " ---\n";
    for (const auto& member : members_) {
        std::cout << " -> ";
        member->show_status();
    }
}