
//
//  tictactoe.cpp
//
//
//  Created by nachiketbhagwat on 10/4/17.
//
//

#include <stdio.h>
#include<iostream>
#include <stdlib.h>
#include <vector>
#include <assert.h>
using namespace std;

class Board{
    
    int size;
    vector<vector<int> > vec;
    
public:
    Board(int n)
    {
        size = n;
        for(int j = 0 ; j < this->size ; j++){
            vector<int> t;
            for(int i = 0 ; i < this->size; i++)
                t.push_back(0);
            vec.push_back(t);
        }
    }
    
    void printBoard()
    {
      for(int i = 0 ; i < this->size ; i++)
      {
          for(int j = 0 ; j < this->size ; j++)
              cout << vec[i][j] << " " ;
          cout << endl;
      }
    }

    int getSize()
    {
        return size;
    }

    vector<vector<int> > getBoard()
    {
        return vec;
    }

    bool selectNew(int x, int y, int val)
    {
        if( x < 0 || x >= size || y <0 || y>=size || vec[x][y]!=0)
            return false;
        vec[x][y] = val;
        return true;
    }

    int isGameOver()
    {
        //rowcheck
        int flag = 0;
        for(int i = 0 ; i < this->size; i++)
        {
          flag = vec[i][0];
          for(int j = 0 ; j < this->size ; j++)
          {
              if(vec[i][j] != flag){
                  flag = 0;
                  break;
              }
          }
          if(flag != 0)
              return flag;
        }

        //columncheck
        for(int i = 0 ; i < this->size; i++)
        {
          flag = vec[0][i];
          for(int j = 0 ; j < this->size ; j++)
          {
              if(vec[j][i] != flag){
                  flag = 0;
                  break;
              }
          }
          if(flag != 0)
              return flag;
        }

        //diagonalcheck
        flag = vec[0][0];
        for(int i = 0 ; i < this->size; i++)
        {
          if(vec[i][i] != flag)
          {
              flag = 0;
              break;
          }
          if(flag != 0)
              return flag;
        }

        flag = vec[0][this->size - 1];
        for(int i = 0 ; i < this->size; i++)
        {
          if(vec[i][this->size - i - 1] != flag)
          {
              flag = 0;
              break;
          }
          if(flag != 0)
              return flag;
        }
        return 0;
    }
                          
};
                          
class Game{
    Board* myboard = new Board(3);
    int status = 0;
public:
    
    int getstatus()
    {
        return status;
    }
    
    void AddRandom()
    {
        int size = myboard->getSize();
        if(status)
        {
            cout << "Game Over Player " << status << " won " << endl;
            return;
        }
        vector<pair<int, int> > tempvec;
        vector<vector<int>> vec = myboard->getBoard();
        for(int i = 0 ; i < size; i++)
            for(int j = 0 ; j < size ; j++)
                if(vec[i][j] == 0)
                    tempvec.push_back(make_pair(i,j));
        pair<int,int> cur = tempvec[rand() % tempvec.size()];
        bool choice = myboard->selectNew(cur.first, cur.second, 2);
        assert(choice);
        status = myboard->isGameOver();
        if(status)
        {
            myboard->printBoard();
            cout << "game over player " << status << " won" << endl;
        }
    }
    
    void chooseRandom()
    {
        int size = myboard->getSize();
        if(status)
        {
            cout << "game over player " << status << " won" << endl;
            return;
        }
        
        myboard->printBoard();
        cout << "choose i, j" << endl;
        while(true)
        {
            int i, j;
            cin >> i;
            cin >> j;
            if(!myboard->selectNew(i,j, 1))
            {
                cout << "choose i, j" << endl;
                myboard->printBoard();
            }
            else
            {
                myboard->selectNew(i, j, 1);
                break;
            }
        }
        status = myboard->isGameOver();
        if(!status)
            AddRandom();
    }
    
};

int main()
{
    Game g;
    while(g.getstatus() == 0)
        g.chooseRandom();
    return 0;
}
