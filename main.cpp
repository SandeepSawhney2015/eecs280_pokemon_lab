#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <string>

#include "Pokemon.hpp"
#include "Trainer.hpp"

using namespace std;

class League {
private:
  // TODO: Add member variables here
  Trainer* player;
  vector<Trainer*> gymLeaders;
  int wins = 0;
  vector<Trainer*> defeated;
public:

  // TODO: Add constructor here to initialize members
  League(Trainer* player_in, vector<Trainer*> gymLeader_in){
    player = player_in;
    gymLeaders = gymLeader_in;
  }



  // TODO: Add member functions here
  void play_fullRound(){
    for(int i = 0; i < gymLeaders.size(); i++){
      player->reset();
      playRound(player, gymLeaders[i]);
      wins = 0;
    }
    cout << player->get_name() << " won " << defeated.size() << " matches by defeating:" << endl;
    for(int i = 0; i < defeated.size(); ++i) {
      cout << defeated[i]->get_name() << endl;
    }
  }

  void playRound(Trainer* player, Trainer* current_gym_leader){
    cout << "-----" << *player << " vs. " << *current_gym_leader << "-----" << endl;
    for(int i = 0; i < 5; ++i) {
      // Each individual pokemon battle
      Pokemon enemy = current_gym_leader->choose_pokemon();
      cout << *current_gym_leader << " chooses " << enemy << endl;
      Pokemon p = player->choose_pokemon(enemy.get_type());
      cout << *player << " chooses " << p << endl;
      if (Pokemon_battle(p, enemy)) {
        cout << p << " defeats " << enemy << endl << endl;
        ++wins;
      }
      else {
        cout << enemy << " defeats " << p << endl << endl;
      }
    }
    cout << "Result: " << *player << "=" << wins << ", "
         << *current_gym_leader << "=" << 5 - wins << endl;
         
    if (wins >= 3) {
      defeated.push_back(current_gym_leader);
    }
    if (wins == 0 || wins == 5) {
      cout << "It's a clean sweep!" << endl;
    }
    cout << endl;
  }


  

  ~League() {
    // TODO: put code here to clean up by deleting all Trainer objects
    delete player;
    for(size_t i = 0; i < gymLeaders.size(); ++i) {
      delete gymLeaders[i];
    }
    
  }
  
};

int main(int argc, char *argv[]) {

  // TODO: Add code to read command line args and open file streams here
  if (argc != 3) {
    cout << "Usage: battle.exe PLAYER_FILE GYM_LEADERS_FILE" << endl;
    return 1;
  }

  string player_in_name = argv[1];
  string gym_leaders_in_name = argv[2];

  ifstream player_in(player_in_name);
  if ( !player_in.is_open() ) {
    cout << "Unable to open " << player_in_name << endl;
    return 1;
  }
  ifstream gym_in(gym_leaders_in_name);
  if ( !gym_in.is_open() ) {
    cout << "Unable to open " << gym_leaders_in_name << endl;
    return 1;
  }

  Trainer *player = Trainer_factory(player_in);

  vector<Trainer*> gym_leaders;

  int num_gym_leaders;
  string ignore;
  gym_in >> num_gym_leaders;
  gym_in >> ignore; // read in the word "leaders"

  for(int i = 0; i < num_gym_leaders; ++i) {
    gym_leaders.push_back(Trainer_factory(gym_in));
  }

  // TODO: Create a League object, call function to run the simulation
  League  league(player, gym_leaders);
  league.play_fullRound();

  
}