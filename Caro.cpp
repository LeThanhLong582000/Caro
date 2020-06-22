#include "Caro.h"

using namespace sf;
using namespace std;

// Create Caro Board with size equal to size
Caro_Board::Caro_Board(int size)
{

    // Set Size for G
    this->G.resize(size);
    for (int i = 0; i < int (this->G.size()); ++i)
    {
        this->G[i].resize(size);
    }

    // Set status of Game
    this->win = false;
    this->lose = false;
    this->draw = false;

    // Set size for Listed
    this->Listed.resize(size);
    for (int i = 0; i < int (this->Listed.size()); ++i)
    {
        this->Listed[i].resize(size);
    }

    // Set Point for Minimax
    this->List_Point.resize(6);
    this->List_Point[0] = 0;
    this->List_Point[1] = 0;
    this->List_Point[2] = 15;
    this->List_Point[3] = 60;
    this->List_Point[4] = 100;
    this->List_Point[5] = 5000;

    // Set Deep for Minimax
    this->MaxDeep = 3;

    // Set Ground
    this->Ground_Texture.loadFromFile("Caro.png");
    this->Ground.setTexture(this->Ground_Texture);
    this->Ground.setPosition(0, 0);
    this->Ground.setScale(1.5, 1.5);

    // Set XO
    this->XO_Texture.loadFromFile("XO.png");

    // Set X
    this->X.setTexture(this->XO_Texture);
    this->X.setTextureRect(IntRect(0, 90, 90, 90));
    this->X.setScale(0.533, 0.533);

    // Set O
    this->O.setTexture(this->XO_Texture);
    this->O.setTextureRect(IntRect(0, 0, 90, 90));
    this->O.setScale(0.533, 0.533);
}

// Tick X in Caro Board
void Caro_Board::Tick_X(int x, int y)
{
    this->G[x][y] = 'X';

    // Add to List Node we want to use in Minimax
    // To reduce Nodes we must consider
    for (int i = max(0, x - 1); i < min(this->size, x + 2); ++i)
    {
        for (int j = max(0, y - 1); j < min(this->size, y + 2); ++j)
        {
            if (this->G[i][j] == 0 && !this->Listed[i][j])
            {
                this->List_Node.push_back(make_pair(i, j));
                this->Listed[i][j] = true;
            }
        }
    }

    // We lose
    if (this->Cal_Point(x, y) == 5000)
    {
        this->lose = true;
    }

    return ;
}

// Tick O in Caro Board
void Caro_Board::Tick_O(int x, int y)
{
    this->G[x][y] = 'O';

    // Add to List Node we want to use in Minimax
    // To reduce Nodes we must consider
    for (int i = max(0, x - 1); i < min(this->size, x + 2); ++i)
    {
        for (int j = max(0, y - 1); j < min(this->size, y + 2); ++j)
        {
            if (this->G[i][j] == 0 && !this->Listed[i][j])
            {
                this->List_Node.push_back(make_pair(i, j));
                this->Listed[i][j] = true;
            }
        }
    }

    // We win
    if (this->Cal_Point(x, y) == 5000)
    {
        this->win = true;
    }

    return ;
}

// Get size of Board
int Caro_Board::get_size()
{
    return this->size;
}

// Is AI win
bool Caro_Board::isWin()
{
    return this->win;
}

// Is Player win
bool Caro_Board::isLose()
{
    return this->lose;
}

// Check that this box is empty or not
bool Caro_Board::isEmpty(int x, int y)
{
    return this->G[x][y] == 0;
}

// Delete a box
void Caro_Board::Del(int x, int y)
{
    this->G[x][y] = 0;
    return ;
}

// Calculate Point will get
int Caro_Board::Cal_Point(int x, int y)
{
    // Point will get
    int Point = 0;

    // X or O
    char Type = this->G[x][y];

    // Calculate Point in Column
    int ansx = x, ansy = y;
    int Count = 0;
    while(ansx < this->size && this->G[ansx][ansy] == Type)
    {
        Count++;
        ansx++;
    }
    ansx = x - 1;
    while(ansx >= 0 && this->G[ansx][ansy] == Type)
    {
        Count++;
        ansx--;
    }
    Point += this->List_Point[min(Count, 5)];

    // Calculate Point in Row
    ansx = x, ansy = y;
    Count = 0;
    while(ansy < this->size && this->G[ansx][ansy] == Type)
    {
        Count++;
        ansy++;
    }
    ansy = y - 1;
    while(ansy >= 0 && this->G[ansx][ansy] == Type)
    {
        Count++;
        ansy--;
    }
    Point += this->List_Point[min(Count, 5)];

    // Calculate Point in main Diagonal
    ansx = x, ansy = y;
    Count = 0;
    while(ansx < this->size && ansy < this->size && this->G[ansx][ansy] == Type)
    {
        Count++;
        ansx++;
        ansy++;
    }
    ansx = x - 1, ansy = y - 1;
    while(ansx >= 0 && ansy >= 0 && this->G[ansx][ansy] == Type)
    {
        Count++;
        ansx--;
        ansy--;
    }
    Point+= this->List_Point[min(Count, 5)];

    // Calculate Point in extra Diagonal
    ansx = x, ansy = y;
    Count = 0;
    while(ansx < this->size && ansy >= 0 && this->G[ansx][ansy] == Type)
    {
        Count++;
        ansx++;
        ansy--;
    }
    ansx = x - 1, ansy = y + 1;
    while(ansx >= 0 && ansy < this->size && this->G[ansx][ansy] == Type)
    {
        Count++;
        ansx--;
        ansy++;
    }
    Point += this->List_Point[min(Count, 5)];

    return Point;
}

// Class Max in Minimax
int Caro_Board::Class_Max(int deep, vector<pair<int, int>> Nodes, vector<vector<bool>> In_List)
{
    // End Minimax
    if (deep > this->MaxDeep) return 0;

    // Set Point is -INF
    int Point = -100000;

    // Iterator over all Node and get Max score
    for (int i = 0; i < int (Nodes.size()); ++i)
    {
        int x = Nodes[i].first;
        int y = Nodes[i].second;
        if (this->G[x][y] != 0) continue;
        this->G[x][y] = 'O';
        int ans_Point = this->Cal_Point(x, y);

        // Skip if win
        if (ans_Point == 5000)
        {
            Point = 5000;
            this->Del(x, y);
            break ;
        }

        // Prepare List Node for next class of tree game and calculate point we will get
        vector<pair<int, int>> Node_Ans = Nodes;
        vector<vector<bool>> Ans_In_List = In_List;
        for (int i = max(0, x - 1); i < min(this->size, x + 2); ++i)
        {
            for (int j = max(0, y - 1); j < min(this->size, y + 2); ++j)
            {
                if (this->G[i][j] == 0 && !Ans_In_List[i][j])
                {
                    Node_Ans.push_back(make_pair(i, j));
                    Ans_In_List[i][j] = true;
                }
            }
        }
        Point = max(Point, ans_Point + this->Class_Min(deep + 1, Node_Ans, Ans_In_List));
        this->Del(x, y);
    }

    return Point;
}

// Class Min in Minimax
int Caro_Board::Class_Min(int deep, vector<pair<int, int>> Nodes, vector<vector<bool>> In_List)
{
    // End Minimax
    if (deep > this->MaxDeep) return 0;

    // Set Point equal INF
    int Point = 100000;

    // Iterator over all Node and get Min score
    for (int i = 0; i < int (Nodes.size()); ++i)
    {
        int x = Nodes[i].first;
        int y = Nodes[i].second;
        if (this->G[x][y] != 0) continue;
        this->G[x][y] = 'X';
        int ans_Point = - this->Cal_Point(x, y);

        // Skip if lose
        if (ans_Point == -5000)
        {
            Point = -5000;
            this->Del(x, y);
            break ;
        }

        // Prepare List Node for next class of tree game and calculate point we will get
        vector<pair<int, int>> Node_Ans = Nodes;
        vector<vector<bool>> Ans_In_List = In_List;
        for (int i = max(0, x - 1); i < min(this->size, x + 2); ++i)
        {
            for (int j = max(0, y - 1); j < min(this->size, y + 2); ++j)
            {
                if (this->G[i][j] == 0 && !Ans_In_List[i][j])
                {
                    Node_Ans.push_back(make_pair(i, j));
                    Ans_In_List[i][j] = true;
                }
            }
        }
        Point = min(Point, ans_Point + this->Class_Max(deep + 1, Node_Ans, Ans_In_List));
        this->Del(x, y);
    }

    return Point;
}

// AI
bool Caro_Board::MiniMax()
{
    srand(time(NULL));

    // Create vector to store status and Point of them
    vector<pair<pair<int, int>, int>> Res;

    // Set Point equal -INF
    int Point = -100000;

    // Iterator over all Node
    for(int i = 0; i < int (this->List_Node.size()); ++i)
    {
        int x = this->List_Node[i].first;
        int y = this->List_Node[i].second;
        if (this->G[x][y] != 0)
        {
            this->List_Node.erase(List_Node.begin() + i);
            i--;
            continue;
        }

        this->G[x][y] = 'O';
        int ans_Point = this->Cal_Point(x, y);

        // Skip if win
        if (ans_Point == 5000)
        {
            Point = 5000;
            Del(x, y);
            Res.push_back(make_pair(make_pair(x, y), Point));
            break ;
        }

        // Prepare List Node for next class of tree game and calculate point we will get
        vector<pair<int, int>> Node_Ans = this->List_Node;
        vector<vector<bool>> In_List = this->Listed;
        for (int i = max(0, x - 1); i < min(this->size, x + 2); ++i)
        {
            for (int j = max(0, y - 1); j < min(this->size, y + 2); ++j)
            {
                if (this->G[i][j] == 0 && !In_List[i][j])
                {
                    Node_Ans.push_back(make_pair(i, j));
                    In_List[i][j] = true;
                }
            }
        }
        int Point_Ans = ans_Point + this->Class_Min(2, Node_Ans, In_List);
        Point = max(Point, Point_Ans);
        this->Del(x, y);

        Res.push_back(make_pair(make_pair(x, y), Point_Ans));
    }

    // Create vector to store status will get Max score
    vector<pair<int, int>> Result;
    for (int i = 0; i < int (Res.size()); ++i)
    {
        if (Res[i].second == Point)
        {
            Result.push_back(Res[i].first);
        }
    }
    if (Result.size() == 0) return false;

    // Chose random a move will get Max score
    int C = rand() % int (Result.size());
    pair<int, int> Move = Result[C];
    this->Tick_O(Move.first, Move.second);
    cout << "Ticked\t" << Move.first + 1 << '\t' << Move.second + 1 << '\n';
    return true;
}

// Display everything in Caro Board
void Caro_Board::Display(RenderWindow &window)
{
    Sprite Ans;

    // draw Back Ground of Board
    window.draw(this->Ground);
    for (int i = 0; i < 18; ++i)
    {
        for (int j = 0; j < 18; ++j)
        {

            // draw X if this box has X
            if(this->G[i][j] == 'X')
            {
                Ans = this->X;
                Ans.setPosition(25 + i * 47.5, 35 + j * 47);
                window.draw(Ans);
            }

            // draw O if this box has O
            if(this->G[i][j] == 'O')
            {
                Ans = this->O;
                Ans.setPosition(25 + i * 47.5, 35 + j * 47);
                window.draw(Ans);
            }
        }
    }

    return ;
}
