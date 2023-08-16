#ifndef SKILLNODE_HPP
#define SKILLNODE_HPP

#include <vector>
#include <string>
#include <functional>

#include "entity.hpp"
#include "text.hpp"

#define NUMBER_OF_SKILLS 5

#pragma once

typedef struct s_pair
{
	int id;
	int level;
} t_pair;

typedef struct s_skill
{
	int id;
	int level;
	int maxLevel;
	t_pair requirements;
	std::function<void()> effect;
	std::string name;
	std::string description;
	std::vector<int> costs;
} skill;

extern skill __skills[NUMBER_OF_SKILLS];

class SkillNode : public Entity
{
public:
	SkillNode(int r, int g, int b, std::string name);
	~SkillNode();

	void addRequirement(SkillNode *requirement);
	void setPosition(int x, int y);
	void autoLayout(int xSpacing, int ySpacing);
	std::vector<SkillNode *> requirements;
	std::string name;
	int requiredBy;
	int depth;
	int id;
	int checkedRequirements;
	Text *text;

private:
};

#endif