#include <cstdlib>

#include "../state/state.hpp"
#include "./alphabeta.hpp"


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move Alphabeta::get_move(State *state, int depth,int player){
  if(!state->legal_actions.size())
    state->get_legal_actions();
    
  auto actions = state->legal_actions;
  int last_value=INT_MIN;
  int alpha=INT_MIN;
  int beta=INT_MAX;

  Move best_move;
  for(auto action:actions)
  {
    State* nextstate=state->next_state(action); 
    
    
    int value= alpha_beta(nextstate,depth,false,player,alpha,beta);
    if (value > last_value) {
        last_value = value;
        best_move=action;

      } 
    alpha=std::max(alpha,value);
  }
  
  return best_move;
  
}
int alpha_beta(State* state,int depth,bool is_max_player,int who,int alpha,int beta)
{
    if (depth==0||state->legal_actions.size()==0)
      return state->evaluate(who);
    if(is_max_player)
    {
      int max_value=INT_MIN;
      auto actions=state->legal_actions;

      for(auto action:actions)
      {
        State* nextstate=state->next_state(action);
        int eval=alpha_beta(nextstate,depth-1,false,who,alpha,beta);
        max_value=std::max(max_value,eval);
        alpha=std::max(alpha,eval);
        if(beta<=alpha)
            break;
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
        int eval=alpha_beta(nextstate,depth-1,true,who,alpha,beta);
        min_value=std::min(min_value,eval);
        beta=std::min(beta,eval);
        if(beta<=alpha)
            break;
      }
      return min_value;
    }
}