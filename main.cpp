#include <iostream>
#include <string>
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
    int turns_cowndown;
    int definy_time;

    bool can_atack() {
        return turns_cowndown == 0;
    }
    
    void setvalue(int value) {
        this->value = value;
    }

    void setturns_cowndown(int turns_cowndown) {
        this->turns_cowndown = turns_cowndown;
    }
    
    virtual void execute(person& user, person& enemy) = 0;
    virtual ~atack() {} 
};

// Damage attack
class damage_atack : public atack {
public:
    int damage_give;
    bool damage_itself;
    
    void give_damage(person& enemy);
    void damage_user(person& user);
    
    void execute(person& user, person& enemy) override {
        give_damage(enemy);
        if (damage_itself) {
            damage_user(user);
        }
    }
};

// Heal attack
class heal_atack : public atack {
public:
    void give_heal(person& user); 
    
    void execute(person& user, person& enemy) override { 
        give_heal(user);
    }
};

// Defense atack
class defense_atack : public atack {
public:
    void give_armor(person& user); 
    
    void execute(person& user, person& enemy) override { 
        give_armor(user);
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

    person() : passiv_name("Passiva Básica") {}

    void setName(string name){
        this->name = name;
    }

    void lostlife(int life_losted) {
        life = life - life_losted;
    }

    void heallife(int life_healed) {
        life = life + life_healed;
    }

    void getarmor(int armor_retrived){
        armor = armor_retrived;
    }

    void lostarmor(){
        armor = 0;
    }

    virtual void passiv() {
        cout << "passiv";
    }
    
    virtual ~person() {}
};

class assassin : public person {
public:
    defense_atack atack2;
    damage_atack atack3;
    damage_atack atack4;
    damage_atack atack5;  // Novo ataque
    heal_atack atack6;    // Novo ataque
    int assassin_factor;
    
    assassin() : assassin_factor(0) {}
    
    void passiv() override {
        assassin_factor++;
        cout << "Assassin factor increased to: " << assassin_factor << endl;
    }
    
    void apply_assassin_damage(person& enemy) {
        if (assassin_factor >= 3) {
            enemy.lostlife(50);
            assassin_factor = 0;
            cout << "Assassin passive triggered! Dealt 50 damage." << endl;
        }
    }
};

void damage_atack::give_damage(person& enemy) {
    enemy.lostlife(value);
}

void damage_atack::damage_user(person& user) {
    user.lostlife(damage_give / 10);
}

void heal_atack::give_heal(person& user) { 
    user.heallife(value);
}

void defense_atack::give_armor(person& user) { 
    user.getarmor(value);
}

class menu {
    int* operacao = new int;

public: 
    void start() {
        cout << "Choose what you want do: "
             << "1 - Start a game";
    }
    
    void caracter_select() {
        cout << "Choose your caracter: \n"
             << "1 - Person 1\n"
             << "2 - Person 2\n"
             << "3 - Person 3\n"
             << "4 - Assassin\n"
             << "5 - Tank\n";
    }
    
    ~menu() {
        delete operacao;
    }
};

// Global attack pointers
damage_atack* shadow_atack = nullptr;
damage_atack* blood_knife = nullptr;
damage_atack* poison_dagger = nullptr;
heal_atack* shadow_heal = nullptr;

void create_attacks() {
    shadow_atack = new damage_atack();
    shadow_atack->name = "Shadow_Atack";
    shadow_atack->value = 10;
    shadow_atack->turns_cowndown = 3;
    shadow_atack->definy_time = shadow_atack->turns_cowndown;
    shadow_atack->damage_itself = 0;
    shadow_atack->damage_give = 0;

    blood_knife = new damage_atack();
    blood_knife->name = "Blood Knife";
    blood_knife->value = 20;
    blood_knife->turns_cowndown = 5;
    blood_knife->definy_time = blood_knife->turns_cowndown;
    blood_knife->damage_itself = 1;
    blood_knife->damage_give = 10;

    poison_dagger = new damage_atack();
    poison_dagger->name = "Poison Dagger";
    poison_dagger->value = 15;
    poison_dagger->turns_cowndown = 4;
    poison_dagger->definy_time = poison_dagger->turns_cowndown;
    poison_dagger->damage_itself = 0;
    poison_dagger->damage_give = 5; 

    shadow_heal = new heal_atack();
    shadow_heal->name = "Shadow Heal";
    shadow_heal->value = 25;
    shadow_heal->turns_cowndown = 6;
    shadow_heal->definy_time = shadow_heal->turns_cowndown;
}

void cleanup_attacks() {
    delete shadow_atack;
    delete blood_knife;
    delete poison_dagger;
    delete shadow_heal;
}

void creating_caracters(int id_person) {
    if(id_person == 1) {
        assassin user;
        user.setName("Shadow Night");
        user.life = 80;
        user.armor = 5;
        Shadow_of_night.speed = 30;
        
        // Initialize attacks first
        create_attacks();
        
        // Assign attacks to character
        Shadow_of_night.atack5 = *poison_dagger;
        Shadow_of_night.atack6 = *shadow_heal;
    }
}

int main() {
    creating_caracters(1);
    cout<<"Você selecionou o " {}
    cleanup_attacks();
    return 0;
}