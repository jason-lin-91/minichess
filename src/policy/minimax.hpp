#pragma once
#include "../state/state.hpp"
#include <climits>

/**
 * @brief Policy class for random policy, 
 * your policy class should have get_move method
 */
class Minimax{
public:
  static Move get_move(State *state, int depth,int player);
  
};
int Mini_max(State* state,int depth,bool is_max_player,int who);