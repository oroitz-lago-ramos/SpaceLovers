#include <vector>
#include <map>

#include "entity.hpp"
#include "skillNode.hpp"

SkillNode::SkillNode(int r, int g, int b, std::string name)
	: Entity(r, g, b, 0, 0, 100, 100), name(name), requiredBy(0), depth(0), checkedRequirements(0)
{
}

SkillNode::~SkillNode()
{
}

void SkillNode::setPosition(int x, int y)
{
	this->setX(x);
	this->setY(y);
}

void SkillNode::addRequirement(SkillNode *requirement)
{
	requirements.push_back(requirement);
}

void SkillNode::autoLayout(int xSpacing, int ySpacing)
{
	std::map<SkillNode *, int> nodeLevels;
	std::vector<SkillNode *> currentLevel;
	std::vector<SkillNode *> nextLevel;

	// Calculate levels based on dependencies
	int currentLevelIdx = 0;
	nodeLevels[this] = currentLevelIdx;
	currentLevel.push_back(this);

	while (!currentLevel.empty())
	{
		++currentLevelIdx;
		nextLevel.clear();
		for (SkillNode *node : currentLevel)
		{
			for (SkillNode *requirement : node->requirements)
			{
				if (nodeLevels.find(requirement) == nodeLevels.end())
				{
					nodeLevels[requirement] = currentLevelIdx;
					nextLevel.push_back(requirement);
				}
			}
		}
		std::swap(currentLevel, nextLevel);
	}

	// Set positions based on levels
	std::map<int, int> levelNodeCount;
	for (const auto &pair : nodeLevels)
	{
		int level = pair.second;
		if (levelNodeCount.find(level) == levelNodeCount.end())
		{
			levelNodeCount[level] = 0;
		}
		int xPos = levelNodeCount[level] * (width + xSpacing);
		int yPos = level * (height + ySpacing);
		pair.first->setPosition(xPos, yPos);
		++levelNodeCount[level];
	}
}