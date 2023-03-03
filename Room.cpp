#include "Room.h"

Room::Room(int p, bool ie, vector<Item> its, vector<GameCharacter> gcs){
      position = p;
      isExit = ie;
      items = its;
      enemies = gcs;  
}

        void Room::clearLoot()
        {
            items.clear();
        }
        void Room::clearEnemies()
        {
            enemies.clear();
        }