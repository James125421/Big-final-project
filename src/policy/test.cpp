#include <cstdlib>
#include <set>
#include "../state/state.hpp"
#include "./test.hpp"


//測試用，內容為 state value function 「未」依據棋子所在位置做加權的 alphabeta

Move Test::get_move(State *state, int depth){
    int Value=-1e8;
    if(!state->legal_actions.size())
        state->get_legal_actions();
  
    auto actions = state->legal_actions;
    int id=-1;
    int ans=id;
    for(auto it=actions.begin();it!=actions.end();it++){
        id++;
        int tmpValue=get_value(state->next_state(*it),depth,-1e8,1e8,false);
        if(Value <= tmpValue){
            Value=tmpValue;
            ans=id;
        }
    }
    return actions[id];
    //return actions[(rand()+depth)%actions.size()];
}

int Test::get_value(State *state, int depth,int alpha,int beta,bool player){
    int value;
    if(!depth || !state->legal_actions.size())
        return state->evaluate2();
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