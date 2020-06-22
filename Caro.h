#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

using namespace sf;
using namespace std;

class Caro_Board
{
private:
    vector<vector<char>> G;
    vector<int> List_Point;
    int size;
    Texture XO_Texture;
    Sprite X;
    Sprite O;
    Sprite Ground;
    Texture Ground_Texture;
    int MaxDeep;
    vector<pair<int, int>> List_Node;
    vector<vector<bool>> Listed;
    bool win;
    bool lose;
    bool draw;
public:
    Caro_Board(int size);
    void Display(RenderWindow &window);
    void Tick_X(int x, int y);
    void Tick_O(int x, int y);
    bool isEmpty(int x, int y);
    int get_size();
    void Del(int x, int y);
    int Cal_Point(int x, int y);
    int Class_Max(int deep, vector<pair<int, int>> Nodes, vector<vector<bool>> In_List);
    int Class_Min(int deep, vector<pair<int, int>> Nodes, vector<vector<bool>> In_List);
    bool MiniMax();
    bool isWin();
    bool isLose();
};
