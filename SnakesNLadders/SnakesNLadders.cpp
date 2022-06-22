#include <iostream>
#include <fstream>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>  
#include <string>

using namespace std;

struct node
{
    int data;
    node* next;
    node* prev;
    node* travel = NULL;
};

class LinkedList
{
public:
    node* head;
    node* tail;
    LinkedList()
    {
        head = NULL;
        tail = NULL;
    }
    void CreateMapp(int value)
    {
        for (int i = 1; i <= value; i++)
        {
            AddNodeEnd(i);
        }
    }

    void Display()
    {
        node* temp = tail;
        int x=0;
        while (temp != NULL)
        {
            if (x == 10)
            {
                cout << endl;
                x = 0;
            }
            cout << temp->data << " ";
            temp = temp->prev;
            x++;
        }
    }

    void AddNodeStart(int value)
    {
        node* temp = new node;
        temp->data = value;
        temp->next = NULL;
        temp->prev = NULL;
        if (head == NULL)
        {
            temp->prev = NULL;
            head = temp;
            tail = temp;
        }
        else
        {
            temp->next = head;
            head->prev = temp;
            head = temp;
        }
    }

    void AddNodeEnd(int value)
    {
        node* temp = new node;
        temp->data = value;
        temp->next = NULL;
        if (head == NULL)
        {
            temp->prev = NULL;
            head = temp;
            tail = temp;
        }
        else
        {
            temp->prev = tail;
            tail->next = temp;
            tail = temp;
        }
    }

    void InsertNode(int position)
    {
        node* temp = new node;
        temp->next = NULL;
        temp->prev = NULL;
        temp->data = position;
        node* cur = head;

        if (position == 1)
        {
            AddNodeStart(position);
            temp = head;
            temp = temp->next;
        }  
        else
        {
            for (int i = 2; i < position; i++)
            {
                if (cur == tail)
                {
                    AddNodeEnd(i);
                    return;
                }
                cur = cur->next;
            }
            temp->next = cur->next;
            temp->prev = cur;
            cur->next = temp;
            temp = temp->next;
            cur = cur->next;
            temp->prev = cur;
        }
        while (true)
        {
            position++;
            temp->data = position;
            if (temp->next == NULL)
                break;
            else
                temp = temp->next;
        }


    }

    void DeleteNodeStart()
    {
        node* temp = head;
        if (head == tail)
        {
            tail = NULL;
            head = NULL;
            delete temp;
            cout << "The node has been deleted!\n";
        }
        else
        {
            temp = head;
            head = head->next;
            head->prev = NULL;
            delete temp;
            cout << "The node has been deleted!\n";
        }
    }

    void DeleteNodeEnd()
    {
        if (head == tail)
        {
            node* temp = head;
            head = NULL;
            tail = NULL;
            delete temp;
            cout << "The node has been deleted!\n";
        }
        else
        {
            node* temp = tail;
            tail = tail->prev;
            tail->next = NULL;
            delete temp;
            cout << "The node has been deleted!\n";
        }
    }

    void DeleteNodeInside(int position)
    {
        node* cur = head;
        node* pre = NULL;
        node* temp = NULL;
        if (position == 1)
        {
            DeleteNodeStart();
            temp = head;
        }
        else
        {
            for (int i = 2; i <= position; i++)
            {
                pre = cur;
                cur = cur->next;
                if (cur == tail)
                {
                    DeleteNodeEnd();
                    return;
                }
            }
            pre->next = cur->next;
            temp = cur->next;
            temp->prev = cur->prev;
            delete cur;
        }
        while (true)
        {
            temp->data = position;
            if (temp->next == NULL)
                break;
            else
                temp = temp->next;
            position++;
        }
    }

    void DeleteAll()
    {
        if (head == NULL)
        {
            return;
        }
        else if (head == tail)
        {
            node* temp = head;
            head = NULL;
            tail = NULL;
            delete temp;
        }
        else
        {
            node* temp = head;
            node* cur = NULL;
            head = NULL;
            while (temp != NULL)
            {
                cur = temp->next;
                delete temp;
                temp = cur;
            }
            delete cur;
            tail = NULL;
        }
    }
    void CreateSnake(int from, int to)
    {
        node* tempfrom = head;
        node* tempto = head;
        for (int i = 1; i < from; i++)
        {
            tempfrom = tempfrom->next;
            if (to != i && to > i) {
                tempto = tempto->next;
            }
        }
        tempfrom->travel = tempto;
    }
    void CreateLadder(int from, int to)
    {
        node* tempfrom = head;
        node* tempto = head;
        for (int i = 1; i < to; i++)
        {
            tempto = tempto->next;
            if (from != i && from > i) {
                tempfrom = tempfrom->next;
            }
        }
        tempfrom->travel = tempto;
    }
};

class Player
{
public:
    node* pos;
    Player(LinkedList Mapp)
    {
        pos = Mapp.head;
        cout << pos->data;
    }
    void move(int n)
    {
        node* temp;
        for (int i = 0; i < n; i++)
        {
            if (pos->next == NULL)
                break;
            else
                pos = pos->next;
        }
            
        if (pos->travel != NULL)
            {
                temp = pos->travel;
                if (temp->data > pos->data)
                    cout << "Ladders!" << endl;
                else
                    cout << "Snake!" << endl;
                cout << "Traveling from: " << getTravelStartDestination() << " ---> Traveling to: " << getTravelEndDestination() << endl;
                Sleep(2000);
                pos = pos->travel;
            }
    }
    int getData()
    {
        int possition;
        possition = pos->data;
        return possition;
    }
    int getTravelEndDestination()
    {
        node* temp;
        int possition;
        temp = pos;
        temp = temp->travel;
        possition = temp->data;
        return possition;
    }
    int getTravelStartDestination()
    {
        int possition;
        possition = pos->data;
        return possition;
    }
};
int DiceRoll()
{
    int DiceValue;
    srand(time(NULL));

    DiceValue = rand() % 6 + 1;

    return DiceValue;
}

void menu(int boardsize)
{
    cout << "Size of board: " << boardsize << endl;
    cout << "_____________________________________________" << endl;
    cout << "Menu" << endl;
    cout << "[1] Start Game" << endl;
    cout << "[2] Show the board" << endl;
    cout << "[3] Add a tile" << endl;
    cout << "[4] Delete a tile" << endl;
    cout << "[5] Delete board" << endl;
    cout << "[6] Add snake/ladder" << endl;
    cout << "[0] Exit" << endl;
    cout << "To make a selection, please enter a number: ";
}

void createFromTxt(int & n, LinkedList & Mapp)
{
    ifstream fd(".\\document.txt");
    int from;
    int to;

    fd >> n;
    Mapp.CreateMapp(n);
    
    while (fd >> from >> to)
    {
        if (from < to)
        {
            Mapp.CreateLadder(from, to);
        }
        else if (from > to)
        {
            Mapp.CreateSnake(from, to);
        }
    }
    
}
void Game(LinkedList Mapp, int players, int boardsize)
{
    Player p1(Mapp);
    Player p2(Mapp);
    Player p3(Mapp);
    int n;
    string input;
    getline(cin, input);

    while (true)
    { 
        

        for (int i = 0; i < players; i++)
        {
            system("CLS");
            cout << "TO END GAME ENTER: end" << endl;
            cout << "Player 1 is at tile: " << p1.getData() << endl;
            if (players == 3)
            {
                cout << "Player 2 is at tile: " << p2.getData() << endl;
                cout << "Player 3 is at tile: " << p3.getData() << endl;
            }
            else if (players == 2)
            {
                cout << "Player 2 is at tile: " << p2.getData() << endl;
            }

            if (i == 0)//player1
            {
                cout << "PLAYER 1 TURN" << endl;
                Sleep(1000);
                cout << "Press Enter to roll the dice...";
                getline(cin, input);
                if (input == "end")
                    break;
                n = DiceRoll();
                cout << "Rolled: " << n << endl;
                Sleep(1000);
                if (p1.getData() >= boardsize)
                {
                    cout << "PLAYER 1 WINS!" << endl;
                    Sleep(2000);
                    input = string("end");
                    break;
                }
                p1.move(n);
            }
            else if (i == 1)//player2
            {
                cout << "PLAYER 2 TURN" << endl;
                Sleep(1000);
                cout << "Press Enter to roll the dice...";
                getline(cin, input);
                if (input == "end")
                    break;
                n = DiceRoll();
                cout << "Rolled: " << n << endl;
                Sleep(1000);
                if (p2.getData() >= boardsize)
                {
                    cout << "PLAYER 2 WINS!" << endl;
                    Sleep(2000);
                    input = string("end");
                    break;
                }
                p2.move(n);
            }
            else if (i == 2)//player3
            {
                cout << "PLAYER 3 TURN" << endl;
                Sleep(1000);
                cout << "Press Enter to roll the dice...";
                getline(cin, input);
                if (input == "end")
                    break;
                n = DiceRoll();
                cout << "Rolled: " << n << endl;
                Sleep(1000);
                if (p3.getData() >= boardsize)
                {
                    cout << "PLAYER 3 WINS!" << endl;
                    Sleep(2000);
                    input = string("end");
                    break;
                }
                p3.move(n);
            }
        }
        if (input == "end")
            break;
    }


}
int PlayerCount()
{
    int players;
    system("CLS");
    cout << "Enter 0 to exit to menu" << endl;
    cout << "Enter the number of players (1 - 3) : ";
    cin >> players;
    if (players == 0)
    {
        cout << endl;
        cout << "Exiting...";
        Sleep(1000);
    }
    else if (players > 0 && players <= 3)
    {
        cout << endl;
        cout << "Selected amount of players: " << players << endl;
        Sleep(1000);
    }
    else
    {
        cout << endl;
        cout << "Invalid amount of players";
        Sleep(1000);
    }
    return players;

}
   

int main()
{
    int boardsize;
    int players;
    int n;
    int from, to;
    LinkedList Mapp;
    LinkedList Empty;
    createFromTxt(boardsize, Mapp);
    while(true)
    {
        system("CLS");
        menu(boardsize);
        cin >> n;
        switch (n)
        {
        default:
            break;
        //Start game
        case 1:
            players = PlayerCount();
            Game(Mapp, players, boardsize);
            break;
        //Show board 
        case 2:
            system("CLS");
            Mapp.Display();
            Sleep(4000);
            break;
        //Add Tile
        case 3:
            system("CLS");
            cout << "Enter the possition of tile: ";
            cin >> n;
            Mapp.InsertNode(n);
            boardsize++;
            cout << "Tile added" << endl;
            break;
        //Delete Tile
        case 4:
            system("CLS");
            cout << "Enter the possition of tile: ";
            cin >> n;
            Mapp.DeleteNodeInside(n);
            boardsize--;
            cout << "Tile deleted" << endl;
            break;
        //Delete Mapp
        case 5:
            system("CLS");
            Mapp.DeleteAll();
            cout << "Mapp deleted" << endl;
            boardsize = 0;
            break;
        //Exit
        case 6:
            system("CLS");
            cout << "Enter start tile: ";
            cin >> from;
            cout << endl;
            if (from < 1 || from > boardsize)
            {
                cout << "Can't be smaller than 1 or bigger than " << boardsize << endl;
                Sleep(2000);
                break;
            }
            cout << "Enter end tile: ";
            cin >> to;
            cout << endl;
            if (to < 1 || to > boardsize || to == from)
            {
                cout << "Can't be smaller than 1, bigger than " << boardsize <<" Or equal to "<< from << endl;
                Sleep(2000);
                break;
            }
            if (to > from)
            {
                cout << "Created a ladder from " << from << " to " << to << endl;
                Sleep(2000);
                Mapp.CreateLadder(from, to);
            }
            if (to < from)
            {
                cout << "Created a snake from " << from << " to " << to << endl;
                Sleep(2000);
                Mapp.CreateSnake(from, to);
            }
            break;
        case 0:
            return 0;
        }
    }
}