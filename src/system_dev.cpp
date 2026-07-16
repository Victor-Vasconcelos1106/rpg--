#include <string>
#include <iostream>

using namespace std;

typedef struct character
{

	private:
		
		string name;
		int life;
		int damage;

	public:

		int get_life(){ return life; }
		void set_life(int i){ life = i; }

		int get_damage(){ return damage; }
		void set_damege(int i){ damage = i; }
		
		string get_name()
		{
		
			return name;
		
		}

		void battle_message()
		{
		
			cout << name << " attacks" << endl;	
		
		}
		void death_message()
		{
		
			cout << name << " dies" << endl;	
		
		}
		void battle_status()
		{

			cout << "\n" << name << "\nlife: " << life << "\n"  << endl;

		}

		character( string nome )
		{
			name = nome;
			damage = 2;
			life = 10;
		
		}

		~character()
		{
		
			cout << "fim de character" << endl;
		
		}


} character;
int main()
{

	bool running = true;

	character Hero("The Legendary Hero");
	character* Enemy = new character("The Goblin");
	int b;
	while(running)
	{
	
		Hero.battle_status();
		Enemy->battle_status();


		cout << "options:\n\n" << "1. attack" << endl;
		cout << endl;
	       	cin >>  b;
		cout << endl;
	
		
		system("clear");	
		if( b == 1)
		{
	
			Hero.battle_message();	
			Enemy->set_life( Enemy->get_life() - Hero.get_damage()  );

		}	
		if(Enemy->get_life() >  0)
		{
		
			Enemy->battle_message();
			Hero.set_life( Hero.get_life() - Enemy->get_damage() );

		} else{ Enemy->death_message(); }
	
		if( ( Enemy->get_life() <=  0 ) || ( Hero.get_life() ) <= 0 )
		{
			Hero.battle_status();
			Enemy->battle_status();	
			running = false;
			delete Enemy;	
		}	
	
	}

}









