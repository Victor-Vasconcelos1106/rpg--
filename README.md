# Trabalho Prático 2 - Programação Orientada a Objetos
**Aluno:** [Seu Nome]  
**Matrícula:** [Sua Matrícula]  
**Turma:** 2026.1 - Prof. Carlos Eduardo C. F. Batista  

## ⚔️ Domínio Escolhido: RPG Engine (Continuação TP1)
O projeto estende o motor de RPG do TP1 adicionando hierarquias de herança, despacho polimórfico dinâmico e interfaces puras.

---

## 🗺️ Diagrama de Classes UML (Mermaid)

```mermaid
classDiagram
    class Character {
        <<abstract>>
        -string name_
        -int health_
        -unique_ptr~Item~ equipped_item_
        +calculate_power()* int
        +show_status() void
    }

    class Attackable {
        <<interface>>
        +take_damage(int amount)* void
    }

    class Warrior {
        -int armor_rating_
        +calculate_power() int
        +show_status() void
        +take_damage(int amount) void
    }

    class Mage {
        <<final>>
        -int mana_points_
        +calculate_power() int
        +show_status() void
        +take_damage(int amount) void
    }

    class Item {
        -string name_
        -int bonus_damage_
    }

    Character <|-- Warrior : Herança
    Attackable <|.. Warrior : Realização
    Character <|-- Mage : Herança
    Attackable <|.. Mage : Realização
    Character "1" *-- "1" Item : Composição