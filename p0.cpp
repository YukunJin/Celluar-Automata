/**
 * @fileoverview Project 0 <Celluar Automata> for PHYS498
 * @author Yukun Jin <yjin44@illinois.edu>
 */
#include <stdio.h>
#include <random>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
/*
 *  Class Grid
 */
class Grid{
      vector<vector<int > > state;
    public:
      void init(int val);
      int neighbor_select(int row, int column);
      void swap(int row, int column, int val);
      void print();
      vector<vector<int > > getState();
      void output(int number);
      void setState(vector<vector<int > > newState);
};
/**
  * Initialize the variable state of a new object
  */
void Grid::init(int val){
  state.resize(val);
  for (int i=0;i<state.size();i++){
    state[i].resize(val);
    std::fill(state[i].begin(),state[i].end(),0);
    for(int j=0;j<state[i].size();){
      state[i][j]=1;
      j+=2;
    }
  }
}
/**
  * Set the variable with a given state
  */
void Grid::setState(vector<vector<int > > newState){
  for(int i=0;i<newState.size();i++){
    for(int j=0;j<newState[i].size();j++){
      state[i][j] = newState[i][j];
    }
  }
}
/**
  * Output the state into a .txt file
  */
void Grid::output(int number){
  string filename = to_string(number);
  ofstream state_file;
  state_file.open("state_file/"+filename);
  if(state_file.is_open()){
    for(int i=0;i<state.size();i++){
      for(int j=0;j<state[i].size();j++){
        state_file << state[i][j];
        state_file << " ";
      }
      state_file << "\n";
    }
    state_file.close();
  }

}
/**
  * Swap the current site [row,column] with another site
  */
void Grid::swap(int row, int column,int val){
  int temp = state[row][column];
  for(int i=0;i<state.size();i++){
    for(int j=0;j<state[i].size();j++){
      if((state.size()*i+j+1) == val){
        state[row][column] =  state[i][j];
        state[i][j] = temp;
        break;
      }
    }
  }
}

/**
  * Print the current state for debugging
  */
void Grid::print(){
  for (int i=0; i<state.size();i++){
    for(int j=0; j<state[i].size();j++){
      cout << state[i][j] ;
    }
    cout << "\n" ;
  }
}
/**
  * Get the state of the given object
  */
vector<vector<int > > Grid::getState(){
    return state;
}
/**
  * Randomly select the neighbor of a given site [row,column]
  */
int Grid::neighbor_select(int row, int column){
  std::random_device rd0;
  std::mt19937 mt0(rd0());
  if (state.size()==0){
    return 999;
  }
  /*  Corner Cases
   *  UL(0,0) UR(0,state.size()-1) LL(state.size()-1,0) LR(state.size()-1,state.size()-1)
   */
  if(row == 0 && column == 0){
    uniform_real_distribution<double> dist(0.0,1.0);
    if((int)dist(mt0) == 0){
      return state.size()*row+(column+1)+1; //right
    }
    else{
      return state.size()*(row+1)+(column+1); //down
    }
  }
  else if(row == 0 && column == state.size()-1){
      uniform_real_distribution<double> dist(0.0,1.0);
      if((int)dist(mt0) == 0){
        return state.size()*row+(column+1)-1; //left
      }
      else{
        return state.size()*(row+1)+(column+1); //down
      }
  }
  else if(row == state.size()-1 && column == 0){
    uniform_real_distribution<double> dist(0.0,1.0);
    if((int)dist(mt0) == 0){
      return state.size()*(row-1)+(column+1); //up
    }
    else{
      return state.size()*row+(column+1)+1; //right
    }
  }
  else if(row == state.size()-1 && column == state.size()-1){
    uniform_real_distribution<double> dist(0.0,1.0);
    if((int)dist(mt0) == 0){
      return state.size()*row+(column+1)-1;
    }
    else{
      return state.size()*(row-1)+(column+1);
    }
  }
  /* Margin Cases
   */
  else if((row == 0 && (column != 0 || column != state.size()-1))){
    uniform_real_distribution<double> dist(0.0,2.0);
    if((int)dist(mt0) == 0){
      return state.size()*row+(column+1)-1;  //right
    }
    else if((int)dist(mt0) == 1){
      return state.size()*row+(column+1)+1; //left
    }
    else{
      return state.size()*(row+1)+(column+1); //down
    }
  }
  else if((row == state.size()-1 && (column != 0 || column != state.size()-1))){
    uniform_real_distribution<double> dist(0.0,2.0);
    if((int)dist(mt0) == 0){
      return state.size()*row+(column+1)-1;  //right
    }
    else if((int)dist(mt0) == 1){
      return state.size()*row+(column+1)+1; //left
    }
    else{
      return state.size()*(row-1)+(column+1); //down
    }
  }

  else if(((row != 0 || row != state.size()-1) && column == 0)){
    uniform_real_distribution<double> dist(0.0,2.0);
    if((int)dist(mt0) == 0){
      return state.size()*(row-1)+(column+1);; //up
    }
    else if((int)dist(mt0) == 1){
      return state.size()*row+(column+1)+1; //right
    }
    else{
      return state.size()*(row+1)+(column+1); //down
    }
  }
  else if(((row != 0 || row != state.size()-1) && column == state.size()-1)){
    uniform_real_distribution<double> dist(0.0,2.0);
    if((int)dist(mt0) == 0){
      return state.size()*(row-1)+(column+1); //up
    }
    else if((int)dist(mt0) == 1){
      return state.size()*row+(column+1)-1; //left
    }
    else{
      return state.size()*(row+1)+(column+1); //down
    }
  }
  /* General cases
   */
  else {
    uniform_real_distribution<double> dist(0.0,3.0);
    if((int)dist(mt0) == 0){
      return state.size()*row+(column+1)-1;  //right
    }
    else if((int)dist(mt0) == 1){
      return state.size()*row+(column+1)+1; //left
    }
    else if((int)dist(mt0) == 2){
      return state.size()*(row+1)+(column+1); //down
    }
    else{
      return state.size()*(row-1)+(column+1);
    }
  }
}
int main(){
   std::random_device rd;
   std::mt19937 mt(rd()); //seed the random value
   Grid celluar;
   celluar.init(100); //Initialize the state of the celluar to half empty
   int state_size = celluar.getState().size();
   int swap = 0 ; // variable to hold the # of swaps (steps)
   int file_id = 0; // variable to hold the file_id

   for(;file_id<10000;file_id++){

   while(swap < 10000){
     uniform_real_distribution<double> dist(0.0,10000.0);
     int rand_select_site = (int)dist(mt); //randomly select the site id
     for(int i=0;i<state_size;i++){
       for(int j=0;j<state_size;j++){
         if(state_size*i+(j+1) == rand_select_site){
           int rand_select_neighbor  = celluar.neighbor_select(i,j);
           celluar.swap(i,j,rand_select_neighbor);
         }
       }
     }
    swap++;
  }
  celluar.output(file_id);
  swap=0; // Reset the number of swaps (steps)
}

   return 0;
}
