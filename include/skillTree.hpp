#ifndef SKILLTREE_HPP
#define SKILLTREE_HPP

#include <set>

#include "button.hpp"
#include "skillNode.hpp"
#include "text.hpp"

#define RIGHTPANELCENTERX Graphics::screenWidth + (Graphics::windowWidth - Graphics::screenWidth) / 2

enum SkillState;

class SkillTree
{
public:
	SkillTree();
	~SkillTree();
	static SkillTree *instance;
	static std::set<Button *> buttons;
	std::vector<SkillNode *> nodes[4];

	skill *selectedSkill;
	Text *totalExp;
	Button *currentSkillButton;
	SkillState currentState;
	void autoLayout();

	int calculateDepth(SkillNode *node, SkillNode *current, int maxDepth);

	void render();
	void getNodes();
	void renderRightPanel();
};

#endif