#include <cstdlib>
#include <set>
#include "../state/state.hpp"
#include "./minimax.hpp"


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move Minimax::get_move(State *state, int depth){
    int Value=-1e8;
    if(!state->legal_actions.size())
        state->get_legal_actions();
  
    auto actions = state->legal_actions;
    int id=-1;
    int ans=id;
    for(auto it=actions.begin();it!=actions.end();it++){
        id++;
        int tmpValue=get_value(state->next_state(*it),depth,false);
        if(Value <= tmpValue){
            Value=tmpValue;
            ans=id;
        }
    }
    return actions[ans];
    //return actions[(rand()+depth)%actions.size()];
}

int Minimax::get_value(State *state, int depth,bool player){
    int value;
    if(!depth || !state->legal_actions.size())
        return state->evaluate2();
    if(player){
        value=-1e8;
        auto actions = state->legal_actions;
        for(auto it=actions.begin();it!=actions.end();it++){
            value=std::max(value,get_value(state->next_state(*it),depth-1,false));
        }
        return value;
    }
    else{
        value=1e8;
        auto actions = state->legal_actions;
        for(auto it=actions.begin();it!=actions.end();it++){
            value=std::min(value,get_value(state->next_state(*it),depth-1,true));
        }
        return value;
    }
}