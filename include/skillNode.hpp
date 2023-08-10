#ifndef SKILLNODE_HPP
#define SKILLNODE_HPP

#include <vector>
#include <string>

#include "entity.hpp"

class SkillNode : public Entity
{
public:
	SkillNode(int r, int g, int b, std::string name);
	~SkillNode();

	void addRequirement(SkillNode *requirement);
	void setPosition(int x, int y);
	void autoLayout(int xSpacing, int ySpacing);
	int requiredBy;
	int checkedRequirements;
	std::string name;
	std::vector<SkillNode *> requirements;
	int depth;

private:
};

#endif