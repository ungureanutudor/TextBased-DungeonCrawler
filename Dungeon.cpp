#include "Dungeon.h"
#include "Player.h"
#include "Room.h"
#include <iostream>
using namespace std;
Dungeon::Dungeon(Player p)
{
    player = p;
}

void Dungeon::enterRoom(Room * room)
{
    if(room->enemies.size()!=0)
    {
        handleEnemyRoom(room);
    }
    else if (room->items.size()!=0)
    {
       handleChestRoom(room);
    }
    else
    {
        handleEmptyRoom(room);
    }
}

void Dungeon::handleEmptyRoom(Room * room)
{
    cout << "You enter the room. You find only walls. No loot to gain. \n";
    string actions[] = {"a. Move to another room"};
    while(true)
    {
        printActions(1, actions);
        string input;
        cin >> input;
        if (input == "a" || input == "A")
        {
            return;
        }
        else
        {
            cout << "Incorrect choice \n";
        }
    }
}

void Dungeon::handleFightActions(GameCharacter * enemy)
{
string actions[] = {"a. Attack", "b. Retreat"};
    while(true)
    {
        printActions(2, actions);
        string input;
        cin >> input;
        //handle player actions
        if (input == "a" || input == "A")
        {   
            int damage = enemy->takeDamage(player.attack);
            cout << "Your attack does " << damage << " damage \n";
        }
        else if (input == "b" || input == "B")
        {
            player.changeRooms(player.previousRoom);
            enterRoom(player.currentRoom);
            return;
        }
        else
        {
            cout << "Incorrect choice \n";
        }
        //check if enemy dead
        if(enemy->checkIsDead())
        {
            cout << "Enemy is dead \n";
            player.increaseStats(10,5,5);
            player.currentRoom->clearEnemies();
            return;
        }

        //handle enemy actions
        int damage = player.takeDamage(enemy->attack);
         cout << enemy->name << "'s attack does " << damage << " damage \n";
         cout << " Your health is " << player.currentHealth << " damage \n";
            if(player.checkIsDead())
            {
                return;
            }
    }
}

void Dungeon::handleEnemyRoom(Room * room)
{
    GameCharacter enemy = room->enemies.front();
    cout << "You enter the room. You find a huge "<< enemy.name<<"\n";
    string actions[] = {"a. Go back to previous room", "b. Fight the enemy"};
    while(true)
    {
        printActions(2, actions);
        string input;
        cin >> input;
        if (input == "a" || input == "A")
        {   
            player.changeRooms(player.previousRoom);
            enterRoom(player.currentRoom);
            return;
        }
        else if (input == "b" || input == "B")
        {
            handleFightActions(&enemy);
            return;
        }
        else
        {
            cout << "Incorrect choice \n";
        }
    }
}

void Dungeon::handleChestRoom(Room * room)
{
    cout << "You enter the room. You see a big juicy chest. \n";
    string actions[] = {"a. Move to another room", "b. Loot the chest"};
    while(true)
    {
        printActions(2, actions);
        string input;
        cin >> input;
        if (input == "a" || input == "A")
        {
            return;
        }
        else if (input == "b" || input == "B")
        {
            handleLootActions(room);
            return;
        }
        else
        {
            cout << "Incorrect choice \n";
        }
    }
}

void Dungeon::handleLootActions(Room * room)
{
    Item item = room->items.front();
    int size = room->items.size();
    player.lootRoom(room);
    room->clearLoot();
    for (int i = 0; i< size;i++){
    cout << "You opened the chest and found something shiny... It's a " << item.name << "\n";
    cout << "Your health is now " << player.currentHealth << ", your attack is now " << player.attack << ", you defence is now" << player.defence <<"\n";
    }
}

void Dungeon::printActions(int numActions, string actions[])
{
    cout << "Choose an action: \n";
    for (int i = 0; i < numActions; i++)
    {
        cout << actions[i] << "\n";
    }
}

void Dungeon::handleMovementActions(Room * room)
{   while(true){
    if(room->position == 0)
    {
        string actions[] = {"a. move right", "b. move down"};
        printActions(2,actions);
        string input;
        cin >> input;
        if(input == "a")
        {
            player.changeRooms(&rooms[1]);
            return;
        } else if (input == "b") {
            player.changeRooms(&rooms[2]);
            return;
        } else {
            cout << " wrong input \n";
        }
    }
    else if (room->position == 1)
    {
        string actions[] = {"a. move right"};
        printActions(1,actions);
        string input;
        cin >> input;
        if(input == "a")
        {
            player.changeRooms(&rooms[0]);
            return;
        } else {
            cout << " wrong input \n";
        }
    }
    else if (room->position == 2)
    {
        string actions[] = {"a. move up", "b. move right"};
        printActions(2,actions);
        string input;
        cin >> input;
        if(input == "a")
        {
            player.changeRooms(&rooms[0]);
            return;
        } else if (input == "b") {
            player.changeRooms(&rooms[3]);
            return;
        } else {
            cout << " wrong input \n";
        }
    }
    else if (room->position == 3)
    {
        string actions[] = {"a. move left"};
        printActions(1,actions);
        string input;
        cin >> input;
        if(input == "a")
        {
            player.changeRooms(&rooms[2]);
            return;
        }  else {
            cout << " wrong input \n";
        }
    }
    }   
}

int Dungeon::performEndGameLogic()
{
    string actions[] = {"a.Yes","b. No"};
    while(true){
    printActions(2,actions);
    string input;
    cin >> input;
    if (input == "a"){
        return 1;
    }else if (input == "b"){
        return 0;
    }else{
        cout << "incorrenct motnhter \n";
    }
    }
    
}

int Dungeon::runDungeon()
{   
    cout << "Welcome to the Dungeon! Inside you will find treasure and enemies! Good luck! \n";
    player.currentRoom = &rooms[0];
    player.previousRoom = &rooms[0];
    while(true)
    {
        enterRoom(player.currentRoom);
        if(player.checkIsDead()){
            cout << "Game over! Try again? \n";
            return performEndGameLogic();
        } else
        {
            if(player.currentRoom->isExit){
                if(player.currentRoom->enemies.size() == 0)
                {
                    cout <<"You win! Play again? \n";
                    return performEndGameLogic();
                }
            }
        }
        handleMovementActions(player.currentRoom);
    }
}