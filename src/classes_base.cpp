#include <iostream>
#include <string>
#include <vector>
#include <memory>

class Item {
private:
    std::string name_;
    int bonus_damage_;

public
    Item(const std::string& name, int bonus) 
        : name_(name), bonus_damage_(bonus) {
        std::cout << "Item (" << name_ << ") forjado.\n";
    }


    ~Item() {
        std::cout << "~Item(\"" << name_ << "\") destruido.\n";
    }

    std::string name() const { return name_; }
    int bonus_damage() const { return bonus_damage_; }


    int calculate_stat_scaling(int attribute_points) const {
        if (attribute_points <= 0) return bonus_damage_;
        return bonus_damage_ + (attribute_points * 2);
    }
};

class Character {
private:
    std::string name_;
    int health_;
    int strength_;
    std::unique_ptr<Item> equipped_item_; 

public:
    Character(const std::string& name, int health, int strength, const std::string& item_name, int item_bonus)
        : name_(name), health_(health), strength_(strength),
          equipped_item_(std::make_unique<Item>(item_name, item_bonus)) {
        std::cout << "Heroi (" << name_ << ") entrou na taverna.\n";
    }

    ~Character() {
        std::cout << "~Character(\"" << name_ << "\") partiu desta vida.\n";
    }

    std::string name() const { return name_; }
    int health() const { return health_; }
    const Item* equipped_item() const { return equipped_item_.get(); }

    void heal_points(int amount) {
        if (amount <= 0) return;
        health_ += amount;
        std::cout << name_ << " foi curado em " << amount << " HP. Vida atual: " << health_ << "\n";
    }
};

class QuestLog {
private:
    std::string active_quest_;
    int experience_reward_;

public:
    QuestLog() : active_quest_("Nenhuma"), experience_reward_(0) {
        std::cout << "Diario de Missoes ativado.\n";
    }

    ~QuestLog() {
        std::cout << "~QuestLog arquivado.\n";
    }

    std::string active_quest() const { return active_quest_; }

    // Metodo com logica real: aceita nova missao se valida
    void accept_quest(const std::string& title, int xp) {
        if (title.empty() || xp <= 0) return;
        active_quest_ = title;
        experience_reward_ = xp;
        std::cout << "Nova missao aceita: " << active_quest_ << " (" << experience_reward_ << " XP)\n";
    }
};

class Party {
private:
    std::string party_name_;
    // Q4: Ponteiros brutos observadores para AGREGACOES (sem posse de memoria)
    std::vector<const Character*> members_; 

public:
    Party(const std::string& name) : party_name_(name) {
        std::cout << "Grupo \"" << party_name_ << "\" foi formado!\n";
    }

    ~Party() {
        std::cout << "~Party(\"" << party_name_ << "\") foi dissolvido.\n";
        // Atendendo a Agregacao: os herois apontados NAO sao deletados aqui!
    }

    // Metodo de Agregacao: adiciona um heroi existente ao grupo
    void join_party(const Character* hero) {
        if (hero != nullptr) {
            members_.push_back(hero);
            std::cout << hero->name() << " juntou-se ao grupo " << party_name_ << ".\n";
        }
    }

    // Metodo com logica real: exibe status dos integrantes
    void show_status() const {
        std::cout << "--- STATUS DO GRUPO: " << party_name_ << " ---\n";
        if (members_.empty()) {
            std::cout << "Grupo vazio.\n";
            return;
        }
        for (const auto& member : members_) {
            std::cout << " -> Guerreiro: " << member->name() << " | Status: " << member->health() << " HP\n";
        }
    }
};
