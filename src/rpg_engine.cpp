#include "rpg_engine.hpp"
#include <iostream>

// ==========================================
// IMPLEMENTACAO: Item
// ==========================================
Item::Item(const std::string& name, int bonus) 
    : name_(name), bonus_damage_(bonus) { // Lista de inicializacao
    std::cout << "Item (" << name_ << ") forjado.\n";
}

Item::~Item() {
    std::cout << "~Item(\"" << name_ << "\") destruido.\n";
}

std::string Item::name() const { return name_; }
int Item::bonus_damage() const { return bonus_damage_; }

int Item::calculate_stat_scaling(int attribute_points) const {
    if (attribute_points <= 0) return bonus_damage_; // Caso limite
    return bonus_damage_ + (attribute_points * 2);
}

// ==========================================
// IMPLEMENTACAO: Character
// ==========================================
Character::Character(const std::string& name, int health, int strength, const std::string& item_name, int item_bonus)
    : name_(name), health_(health), strength_(strength),
      equipped_item_(std::make_unique<Item>(item_name, item_bonus)) { // Criacao da Composicao
    std::cout << "Heroi (" << name_ << ") entrou na taverna.\n";
}

Character::~Character() {
    std::cout << "~Character(\"" << name_ << "\") partiu desta vida.\n";
}

std::string Character::name() const { return name_; }
int Character::health() const { return health_; }
const Item* Character::equipped_item() const { return equipped_item_.get(); }

void Character::heal_points(int amount) {
    if (amount <= 0) return;
    health_ += amount;
    std::cout << name_ << " foi curado em " << amount << " HP. Vida atual: " << health_ << "\n";
}

// ==========================================
// IMPLEMENTACAO: QuestLog
// ==========================================
QuestLog::QuestLog() : active_quest_("Nenhuma"), experience_reward_(0) {
    std::cout << "Diario de Missoes ativado.\n";
}

QuestLog::~QuestLog() {
    std::cout << "~QuestLog arquivado.\n";
}

std::string QuestLog::active_quest() const { return active_quest_; }

void QuestLog::accept_quest(const std::string& title, int xp) {
    if (title.empty() || xp <= 0) return;
    active_quest_ = title;
    experience_reward_ = xp;
    std::cout << "Nova missao aceita: " << active_quest_ << " (" << experience_reward_ << " XP)\n";
}

// ==========================================
// IMPLEMENTACAO: Party
// ==========================================
Party::Party(const std::string& name) : party_name_(name) {
    std::cout << "Grupo \"" << party_name_ << "\" foi formado!\n";
}

Party::~Party() {
    std::cout << "~Party(\"" << party_name_ << "\") foi dissolvido.\n";
    // Nota: Nao deleta os membros do vetor (Regra da Agregacao)
}

void Party::join_party(const Character* hero) {
    if (hero != nullptr) {
        members_.push_back(hero);
        std::cout << hero->name() << " juntou-se ao grupo " << party_name_ << ".\n";
    }
}

void Party::show_status() const {
    std::cout << "--- STATUS DO GRUPO: " << party_name_ << " ---\n";
    if (members_.empty()) {
        std::cout << "Grupo vazio.\n";
        return;
    }
    for (const auto& member : members_) {
        std::cout << " -> Guerreiro: " << member->name() << " | Status: " << member->health() << " HP\n";
    }
}
