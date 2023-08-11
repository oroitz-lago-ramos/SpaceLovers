#ifndef SKILLTREE_HPP
#define SKILLTREE_HPP

#include <set>

#include "button.hpp"
#include "skillNode.hpp"

class SkillTree
{
public:
	SkillTree();
	~SkillTree();
	static SkillTree *instance;
	static std::set<Button *> buttons;
	std::vector<SkillNode *> nodes;
	void autoLayout();

	int calculateDepth(SkillNode *node, SkillNode *current, int maxDepth);

	void render();
};

#endif