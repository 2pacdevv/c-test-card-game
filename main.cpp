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
    int damage_give;
    bool damage_itself;
    
public:
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
    heal_atack atack2; 
    defense_atack atack3;

    person() : passiv_name("Passiva Básica") {}

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

    // Função virtual para polimorfismo
    virtual void passiv() {
        cout <<"passiv";
    }
    
    virtual ~person() {}
};

class assassin : public person {
    public:
        damage_atack atack4;
        int assassin_factor;
    
        assassin() : assassin_factor(0) {}  // Inicializar o fator do assassino
    
        // Implementação polimórfica da passiva
        void passiv() override {
            assassin_factor++;
            cout << "Assassin factor increased to: " << assassin_factor << endl;
            // Nota: A passiva original tentava acessar um inimigo, o que não é possível aqui
            // pois a função passiv() na classe base não tem parâmetros
        }
    
        // Função adicional para aplicar dano quando necessário
        void apply_assassin_damage(person& enemy) {
            if (assassin_factor >= 3) {
                enemy.lostlife(50);
                assassin_factor = 0;
                cout << "Assassin passive triggered! Dealt 50 damage." << endl;
            }
        }
    };


// Implementações dos ataques
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

int main() {
    
    return 0;
}