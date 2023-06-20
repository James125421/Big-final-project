#pragma once
#include "../state/state.hpp"


/**
 * @brief Policy class for random policy, 
 * your policy class should have get_move method
 */
class Alpha_beta_Basic{
public:
  static Move get_move(State *state, int depth,int step);
  static int get_value(State *state, int depth,int alpha,int beta,bool player);
};