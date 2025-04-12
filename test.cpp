#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>
using namespace std;

int turn = 0;

// Forward declarations
class person;
class atack;

// Base attack class
class atack {
public:
    string name;
    int value;
    int turns_cooldown;
    int current_cooldown;
    bool damage_itself;
    int damage_give;

    atack() : turns_cooldown(0), current_cooldown(0), damage_itself(false), damage_give(0) {}

    bool can_attack() {
        return current_cooldown == 0;
    }

    void start_cooldown() {
        current_cooldown = turns_cooldown;
    }

    void update_cooldown() {
        if (current_cooldown > 0) {
            current_cooldown--;
        }
    }

    void setvalue(int value) {
        this->value = value;
    }

    void set_cooldown(int cooldown) {
        this->turns_cooldown = cooldown;
    }
    
    virtual void execute(person& user, person& enemy) = 0;
    virtual ~atack() {} 
};

// Damage attack
class damage_atack : public atack {
public:
    void give_damage(person& enemy);
    void damage_user(person& user);
    
    void execute(person& user, person& enemy) override {
        if (can_attack()) {
            give_damage(enemy);
            if (damage_itself) {
                damage_user(user);
            }
            start_cooldown();
        } else {
            cout << name << " is on cooldown! (" << current_cooldown << " turns left)\n";
        }
    }
};

// Heal attack
class heal_atack : public atack {
public:
    void give_heal(person& user); 
    
    void execute(person& user, person& enemy) override { 
        if (can_attack()) {
            give_heal(user);
            start_cooldown();
        } else {
            cout << name << " is on cooldown! (" << current_cooldown << " turns left)\n";
        }
    }
};

// Defense atack
class defense_atack : public atack {
public:
    void give_armor(person& user); 
    
    void execute(person& user, person& enemy) override { 
        if (can_attack()) {
            give_armor(user);
            start_cooldown();
        } else {
            cout << name << " is on cooldown! (" << current_cooldown << " turns left)\n";
        }
    }
};

// Base Person class
class person {
public:
    string name;
    int life;
    int armor;
    float speed;
    string passiv_name;
    damage_atack atack1;
    defense_atack atack2;
    damage_atack atack3;
    damage_atack atack4;
    damage_atack atack5;
    heal_atack atack6;

    person() : passiv_name("Basic Passive"), life(100), armor(0), speed(10) {}

    void setName(string name) {
        this->name = name;
    }

    void lostlife(int life_losted) {
        life = life - life_losted;
        if (life < 0) life = 0;
    }

    void heallife(int life_healed) {
        life = life + life_healed;
    }

    void getarmor(int armor_retrived) {
        armor = armor_retrived;
    }

    void lostarmor() {
        armor = 0;
    }

    virtual void passiv() {
        cout << "Basic passive effect\n";
    }

    void update_attacks_cooldown() {
        atack1.update_cooldown();
        atack2.update_cooldown();
        atack3.update_cooldown();
        atack4.update_cooldown();
        atack5.update_cooldown();
        atack6.update_cooldown();
    }
    
    virtual ~person() {}
};

class assassin : public person {
public:
    int assassin_factor;
    
    assassin() : assassin_factor(0) {
        passiv_name = "Assassin's Mark";
        life = 80;
        armor = 5;
        speed = 30;
    }
    
    void passiv() override {
        assassin_factor++;
        cout << "Assassin factor increased to: " << assassin_factor << endl;
        if (assassin_factor >= 3) {
            cout << "Assassin is ready for a lethal strike!\n";
        }
    }
    
    void apply_assassin_damage(person& enemy) {
        if (assassin_factor >= 3) {
            enemy.lostlife(50);
            assassin_factor = 0;
            cout << "Assassin passive triggered! Dealt 50 damage to " << enemy.name << endl;
        }
    }
};

void damage_atack::give_damage(person& enemy) {
    int actual_damage = value - (enemy.armor / 2);
    if (actual_damage < 0) actual_damage = 0;
    enemy.lostlife(actual_damage);
    cout << name << " dealt " << actual_damage << " damage to " << enemy.name << endl;
}

void damage_atack::damage_user(person& user) {
    user.lostlife(damage_give);
    cout << name << " recoil dealt " << damage_give << " damage to user" << endl;
}

void heal_atack::give_heal(person& user) { 
    user.heallife(value);
    cout << name << " healed " << value << " HP" << endl;
}

void defense_atack::give_armor(person& user) { 
    user.getarmor(value);
    cout << name << " granted " << value << " armor" << endl;
}

class menu {
public: 
    void start() {
        cout << "Welcome to the Assassin Battle Game!\n";
    }
    
    int character_select() {
        int choice;
        cout << "Choose your assassin: \n"
             << "1 - Shadow Night\n"
             << "2 - Blood Moon\n"
             << "Choice: ";
        cin >> choice;
        return choice;
    }
    
    void show_attacks(person& p) {
        cout << "\nAvailable attacks for " << p.name << ":\n";
        cout << "1 - " << p.atack1.name << (p.atack1.can_attack() ? "" : " (Cooldown)") << "\n";
        cout << "2 - " << p.atack2.name << (p.atack2.can_attack() ? "" : " (Cooldown)") << "\n";
        cout << "3 - " << p.atack3.name << (p.atack3.can_attack() ? "" : " (Cooldown)") << "\n";
        cout << "4 - " << p.atack4.name << (p.atack4.can_attack() ? "" : " (Cooldown)") << "\n";
        cout << "5 - " << p.atack5.name << (p.atack5.can_attack() ? "" : " (Cooldown)") << "\n";
        cout << "6 - " << p.atack6.name << (p.atack6.can_attack() ? "" : " (Cooldown)") << "\n";
    }
};

void create_assassin_attacks(person& p) {
    // Basic Attack
    p.atack1.name = "Quick Strike";
    p.atack1.value = 10;
    p.atack1.set_cooldown(0);
    p.atack1.damage_itself = false;

    // Defensive Move
    p.atack2.name = "Shadow Dodge";
    p.atack2.value = 10;
    p.atack2.set_cooldown(2);

    // Strong Attack
    p.atack3.name = "Lethal Blow";
    p.atack3.value = 25;
    p.atack3.set_cooldown(3);
    p.atack3.damage_itself = true;
    p.atack3.damage_give = 5;

    // Special Attack 1
    p.atack4.name = "Poisoned Dagger";
    p.atack4.value = 15;
    p.atack4.set_cooldown(4);
    p.atack4.damage_itself = false;
    p.atack4.damage_give = 0;

    // Special Attack 2
    p.atack5.name = "Shadow Clone";
    p.atack5.value = 18;
    p.atack5.set_cooldown(3);
    p.atack5.damage_itself = false;

    // Healing Move
    p.atack6.name = "Dark Regeneration";
    p.atack6.value = 20;
    p.atack6.set_cooldown(5);
}

person* create_assassin(int choice, const string& name) {
    assassin* p = new assassin();
    p->setName(name);
    
    if (choice == 2) {  // Blood Moon variant
        p->life = 70;  // Slightly less health
        p->speed = 35; // But faster
        p->atack4.name = "Blood Ritual";  // Different attack name
        p->atack4.value = 20;  // More damage
        p->atack4.set_cooldown(5);  // Longer cooldown
    }
    
    create_assassin_attacks(*p);
    return p;
}

void battle_loop(person& player1, person& player2) {
    menu m;
    int current_player = 1;
    
    while (player1.life > 0 && player2.life > 0) {
        turn++;
        cout << "\n=== Turn " << turn << " ===\n";
        
        person& current = (current_player == 1) ? player1 : player2;
        person& enemy = (current_player == 1) ? player2 : player1;
        
        cout << current.name << "'s turn!\n";
        cout << current.name << " HP: " << current.life << " | Armor: " << current.armor << "\n";
        cout << enemy.name << " HP: " << enemy.life << " | Armor: " << enemy.armor << "\n";
        
        m.show_attacks(current);
        
        int choice;
        cout << "Choose your attack (1-6): ";
        cin >> choice;
        
        switch(choice) {
            case 1: current.atack1.execute(current, enemy); break;
            case 2: current.atack2.execute(current, enemy); break;
            case 3: current.atack3.execute(current, enemy); break;
            case 4: current.atack4.execute(current, enemy); break;
            case 5: current.atack5.execute(current, enemy); break;
            case 6: current.atack6.execute(current, enemy); break;
            default: cout << "Invalid choice, skipping turn\n";
        }
        
        current.passiv();
        current.update_attacks_cooldown();
        
        // Apply assassin passive if applicable
        static_cast<assassin&>(current).apply_assassin_damage(enemy);
        
        current_player = (current_player == 1) ? 2 : 1;
    }
    
    cout << "\n=== Game Over ===\n";
    if (player1.life > 0) {
        cout << player1.name << " wins!\n";
    } else {
        cout << player2.name << " wins!\n";
    }
}

int main() {
    menu m;
    m.start();
    
    // Player 1 selection
    cout << "\nPlayer 1:\n";
    int p1_choice = m.character_select();
    string p1_name;
    cout << "Enter Player 1 name: ";
    cin >> p1_name;
    person* player1 = create_assassin(p1_choice, p1_name);
    
    // Player 2 selection
    cout << "\nPlayer 2:\n";
    int p2_choice = m.character_select();
    string p2_name;
    cout << "Enter Player 2 name: ";
    cin >> p2_name;
    person* player2 = create_assassin(p2_choice, p2_name);
    
    // Start battle
    battle_loop(*player1, *player2);
    
    // Cleanup
    delete player1;
    delete player2;
    
    return 0;
}