#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include "Caro.h"

using namespace std;
using namespace sf;

int main()
{
    // Create Window
    RenderWindow window(VideoMode(900,912),"Caro");

    // Create Back_Ground
    Caro_Board Back_Ground = Caro_Board(20);

    // Chose Player
    string Turn = "Player";
    string winner = "Draw";

    while(window.isOpen())
    {

        // AI Turn
        if (Turn == "AI")
        {
            cout << "Please waiting!!!\n";
            Back_Ground.MiniMax();
            Turn = "Player";
        }

        // Check event
        Event event;
        while(window.pollEvent(event))
        {
            // Close the window
            if(event.type == Event::Closed) window.close();

            // Get Click
            if(Mouse::isButtonPressed(Mouse::Left) && Turn == "Player")
            {
                // Get Position
                int x = (Mouse::getPosition(window).x - 25) / 47;
                int y = (Mouse::getPosition(window).y - 35) / 47;

                // Make sure that x and y in Board
                x = max(x, 0);
                x = min(x, Back_Ground.get_size());
                y = max(y, 0);
                y = min(y, Back_Ground.get_size());

                // Draw X in Board
                if(Back_Ground.isEmpty(x, y))
                {
                    Back_Ground.Tick_X(x, y);
                    Turn = "AI";
                }
            }
        }
        // Is AI won
        if (Back_Ground.isWin())
        {
            winner = "AI";
            window.close();
            cout << "You Lose!!!\n";
        }

        // Is Player won
        if (Back_Ground.isLose())
        {
            winner = "Player";
            window.close();
            cout << "You Win!!!\n";
        }

        // Display Board
        window.clear();
        Back_Ground.Display(window);
        window.display();
    }

    return 0;
}
