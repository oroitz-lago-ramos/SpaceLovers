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
						  {100, 500, 1000, 5000, 10000}};
	__skills[1] = (skill){1, 0, 5, {-1, -1}, []()
						  { Player::instance->maxLifePoints *= 1.05; },
						  "Vitality",
						  "Increases max health by 5% per level",
						  {100, 500, 1000, 5000, 10000}};
	__skills[2] = (skill){2, 0, 5, {0, 3}, []()
						  { Player::instance->power *= 1.15; std::cout << "Supremacy" << std::endl;},
						  "Supremacy",
						  "Increasedd the damage of your attacks by 15% per level",
						  {100, 500, 1000, 5000, 10000}};
}