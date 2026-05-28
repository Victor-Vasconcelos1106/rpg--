# Trabalho Prático - Programação Orientada a Objetos
**Aluno:** [Victor Hugo Araújo de Vasconcelos]  
**Matrícula:** [20250019250]  
**Turma:** 2026.1 - Prof. Carlos Eduardo C. F. Batista  

## ⚔️ Domínio Escolhido: RPG Engine
O sistema consiste num motor simplificado de gestão para jogos de RPG (Role-Playing Games). A arquitetura lida com o ciclo de vida e encapsulamento de personagens (`Character`), os seus equipamentos ativos de combate (`Item`), a organização de heróis em equipas dinâmicas (`Party`) e o rastreamento de missões com as suas respetivas recompensas através de um diário de jornadas (`QuestLog`).

---

## 🗺️ Diagrama de Classes UML (Mermaid)

```mermaid
classDiagram
    class Character {
        -string name_
        -int health_
        -int strength_
        -unique_ptr~Item~ equipped_item_
        +name() string
        +health() int
        +equipped_item() Item*
        +heal_points(int amount) void
    }
    class Item {
        -string name_
        -int bonus_damage_
        +name() string
        +bonus_damage() int
        +calculate_stat_scaling(int attribute_points) int
    }
    class Party {
        -string party_name_
        -vector~Character*~ members_
        +join_party(Character* hero) void
        +show_status() void
    }
    class QuestLog {
        -string active_quest_
        -int experience_reward_
        +active_quest() string
        +accept_quest(string title, int xp) void
    }

    Character "1" *-- "1" Item : Composição (O item pertence exclusivamente ao herói)
    Party "1" o-- "0..*" Character : Agregação (O grupo referencia heróis independentes)
