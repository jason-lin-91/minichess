#include <cstdlib>

#include "../state/state.hpp"
#include "./minimax.hpp"


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move Minimax::get_move(State *state, int depth,int player){
  if(!state->legal_actions.size())
    state->get_legal_actions();
    
  auto actions = state->legal_actions;
  int last_value=INT_MIN;
  int black_value=INT_MAX;
  std::vector<Move> best_move;
  for(auto action:actions)
  {
    State* nextstate=state->next_state(action); 
    if(player==0)
    {
      int value= Mini_max(nextstate,depth-1,true);
    if (value > last_value) {
        last_value = value;
        best_move.clear();
        best_move.push_back(action);
      } else if (value == last_value) {
        best_move.push_back(action);
      }
    }
    else
    {
      
      int value= Mini_max(nextstate,depth-1,false);
    if (value < black_value) {
        black_value = value;
        best_move.clear();
        best_move.push_back(action);
      } else if (value == black_value) {
        best_move.push_back(action);
      }
    }
    
  }
  
  
  return best_move[rand()%best_move.size()];
  
}
int Mini_max(State* state,int depth,bool is_max_player)
{
    if (depth==0)
      return state->evaluate();
    if(is_max_player)
    {
      int max_value=INT_MIN;
      auto actions=state->legal_actions;

      for(auto action:actions)
      {
        State* nextstate=state->next_state(action);
        int eval=Mini_max(nextstate,depth-1,false);
        max_value=std::max(max_value,eval);
      }
        return max_value;
    }
    else
    {
      int min_value=INT_MAX;
      auto actions=state->legal_actions;
      for(auto action:actions)
      {
        State* nextstate=state->next_state(action);
        int eval=Mini_max(nextstate,depth-1,true);
        min_value=std::min(min_value,eval);
      }
      return min_value;
    }
}