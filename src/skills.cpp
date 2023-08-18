#include <string>
#include <functional>

#include <iostream>

#include <player.hpp>
#include "skillNode.hpp"

skill __skills[NUMBER_OF_SKILLS];

void initializeSkills()
{
	__skills[0] = (skill){0, 0, 5, {-1, -1}, []()
						  { Player::instance->power *= 1.05; },
						  "Empower",
						  "Increases the damage of your attacks by 5% per level",
						  {1, 500, 1000, 5000, 10000}};
	__skills[1] = (skill){1, 0, 5, {-1, -1}, []()
						  { Player::instance->maxLifePoints *= 1.05; },
						  "Vitality",
						  "Increases max health by 5% per level",
						  {100, 500, 1000, 5000, 10000}};
	__skills[2] = (skill){2, 0, 5, {0, 3}, []()
						  { Player::instance->power *= 1.15;},
						  "Supremacy",
						  "Increases the damage of your attacks by 15% per level",
						  {100, 500, 1000, 5000, 10000}};
	__skills[3] = (skill){3, 0, 5, {1, 3}, []()
						  { Player::instance->maxLifePoints *= 1.15;},
						  "Fortitude",
						  "Increases max health by 15% per level",
						  {100, 500, 1000, 5000, 10000}};
	__skills[4] = (skill){4,0,5, {2, 5}, []()
							{ Player::instance->speed += 0.01f;},
							"Vitessitude",
							"Increases the speed by 0.01",
							{600000,4444444,2727272}};
}