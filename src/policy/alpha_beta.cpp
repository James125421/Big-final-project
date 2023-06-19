#include <cstdlib>
#include <set>
#include <cstring>
#include "../state/state.hpp"
#include "./alpha_beta.hpp"


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move Alpha_beta::get_move(State *state, int depth){
    int Value=-1e8;
    if(!state->legal_actions.size())
        state->get_legal_actions();
  
    auto actions = state->legal_actions;
    int id=-1;
    int multans[20];
    int multnum=0;
    memset(multans,-1,20);
    for(auto it=actions.begin();it!=actions.end();it++){
        id++;
        int tmpValue=get_value(state->next_state(*it),depth,-1e8,1e8,false);
        if(Value < tmpValue){
            multnum=0;
            memset(multans,-1,20);
            Value=tmpValue;
            multans[multnum++]=id;
        }
        else if(Value == tmpValue){
            multans[multnum++]=id;
        }
    }
    int ans=rand()%multnum;
    return actions[multans[ans]];
    //return actions[(rand()+depth)%actions.size()];
}

int Alpha_beta::get_value(State *state, int depth,int alpha,int beta,bool player){
    int value;
    if(!depth || !state->legal_actions.size())
        return state->evaluate();
    if(player){
        value=-1e8;
        auto actions = state->legal_actions;
        for(auto it=actions.begin();it!=actions.end();it++){
            value=std::max(value,get_value(state->next_state(*it),depth-1,alpha,beta,false));
            alpha=std::max(alpha,value);
            if(alpha>=beta)
                break;
        }
        return value;
    }
    else{
        value=1e8;
        auto actions = state->legal_actions;
        for(auto it=actions.begin();it!=actions.end();it++){
            value=std::min(value,get_value(state->next_state(*it),depth-1,alpha,beta,true));
            beta=std::min(beta,value);
            if(alpha>=beta)
                break;
        }
        return value;
    }
}