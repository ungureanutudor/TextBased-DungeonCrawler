#include "GameCharacter.h"
#ifndef CHAR_H
#define CHAR_H

GameCharacter::GameCharacter(string n, int h, int a, int d) 
{
    name = n;
    maxHealth = h;
    attack = a;
    currentHealth = h;
    defence = d;
}

int GameCharacter::takeDamage(int amount) 
{
    int damage = amount - defence;
    if(damage < 0) {
        damage = 0;
    }
    currentHealth -= damage;
    return damage;
}

bool GameCharacter::checkIsDead()
{
    return currentHealth <= 0;
}

#endif