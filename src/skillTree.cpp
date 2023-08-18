#include <vector>
#include <set>
#include <iostream>
#include <SDL2/SDL.h>

#include "skillTree.hpp"
#include "button.hpp"
#include "game.hpp"
#include "graphics.hpp"
#include "text.hpp"

std::set<Button *> SkillTree::buttons = {};
SkillTree *SkillTree::instance = nullptr;

SkillTree::SkillTree()
	: selectedSkill(nullptr), totalExp(nullptr), currentSkillButton(nullptr), currentState(SPEED)
{
	SkillTree::instance = this;
	Game::currentState = SKILLTREE;
	buttons.insert(new Button(
		255, 0, 0, 50, 25, 100, 50, []()
		{ Game::currentState = MENU; SkillTree::instance->~SkillTree(); },
		"Back", false));
	buttons.insert(new Button(
		255, 0, 0, 175, 100, 150, 100, []()
		{ SkillTree::instance->currentState = SPEED; },
		"Vitesse", false));
	buttons.insert(new Button(
		255, 0, 0, 325, 100, 150, 100, []()
		{ SkillTree::instance->currentState = POWER; },
		"Puissance", false));
	buttons.insert(new Button(
		255, 0, 0, 475, 100, 150, 100, []()
		{ SkillTree::instance->currentState = DEFENSE; },
		"Defense", false));
	buttons.insert(new Button(
		255, 0, 0, 625, 100, 150, 100, []()
		{ SkillTree::instance->currentState = INGAMEITEM; },
		"Boost", false));
	this->getNodes();
	char *exp = new char[100];
	sprintf(exp, "Exp: %d", (int)Player::instance->experience);
	this->totalExp = new Text(0, 250, 200, RIGHTPANELCENTERX, 50, 100, 50, exp, Graphics::font);
	for (int a = 0; a < 4; a++)
		for (long long unsigned int i = 0; i < nodes[a].size(); i++)
		{
			for (long long unsigned int j = 0; j < nodes[a][i]->requirements.size(); j++)
			{
				for (long long unsigned int k = 0; k < nodes[a].size(); k++)
				{
					if (nodes[a][k] == nodes[a][i]->requirements[j])
					{
						nodes[a][k]->requiredBy++;
					}
				}
			}
		}
	for (int a = 0; a < 4; a++)
		for (SkillNode *node : nodes[a])
		{
			node->depth = this->calculateDepth(node, node, -1);
		}

	this->autoLayout();
	for (int a = 0; a < 4; a++)
		for (SkillNode *node : nodes[a])
		{
			node->text = new Text(0, 255, 0, node->getX(), node->getY(), node->getWidth(), node->getHeight(), node->name.c_str(), Graphics::font);
		}
}

int SkillTree::calculateDepth(SkillNode *node, SkillNode *current, int maxDepth)
{
	for (SkillNode *req : node->requirements)
	{
		maxDepth = std::max(maxDepth, this->calculateDepth(req, current, maxDepth));
	}
	return maxDepth + 1;
}

void SkillTree::autoLayout()
{
	for (int i = 0; i < 4; i++)
	{
		std::sort(nodes[i].begin(), nodes[i].end(), [](SkillNode *a, SkillNode *b)
				  { return a->requirements.size() < b->requirements.size(); });
		int x = 50;
		int y = 350;
		int nodeWidth = 100;
		for (SkillNode *node : nodes[i])
		{

			if (node->requirements.size() == 0)
			{
				node->setY(y);
				node->setX(x);
				y += nodeWidth + 175;
			}
			else
			{
				node->setX(x + node->depth * 150);
				for (SkillNode *req : node->requirements)
				{
					int miny = req->getY();
					miny -= (150 * (req->requiredBy - 1)) / 2;
					miny += 150 * req->checkedRequirements;

					node->setY(miny);
					req->checkedRequirements++;
				}
			}
		}
	}
}

SkillTree::~SkillTree()
{
	Game::currentState = MENU;
	for (auto button : std::set<Button *>(this->buttons))
	{
		this->buttons.erase(button);
		button->~Button();
	}
	for (int i = 0; i < 4; i++)
		for (auto node : this->nodes[i])
		{
			delete node;
		}
	this->totalExp->~Text();
	// delete this->totalExp;
}

void SkillTree::render()
{
	for (auto button : buttons)
	{
		button->render();
	}
	for (auto node : nodes[this->currentState])
	{
		for (auto req : node->requirements)
		{
			SDL_SetRenderDrawColor(Graphics::renderer, 255, 255, 255, 255);
			SDL_RenderDrawLine(Graphics::renderer, node->getX(), node->getY(), req->getX(), req->getY());
		}
	}
	for (auto node : nodes[this->currentState])
	{
		node->render();
		node->text->render();
	}
	SDL_Event event;
	this->renderRightPanel();
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			Game::isRunning = false;
		}
		else if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			const SDL_Point point = {event.button.x, event.button.y};

			for (auto button : buttons)
			{
				if (SDL_PointInRect(&point, &button->rect))
				{
					button->onClick();
					break;
				}
			}
			for (auto *node : this->nodes[this->currentState])
			{
				if (SDL_PointInRect(&point, &node->rect))
				{
					this->selectedSkill = &__skills[node->id];
					this->buttons.erase(this->currentSkillButton);
					delete this->currentSkillButton;
					this->currentSkillButton = new Button(
						255, 0, 0, RIGHTPANELCENTERX, 550, 100, 50, []()
						{
							if (SkillTree::instance->selectedSkill->level < SkillTree::instance->selectedSkill->maxLevel && Player::instance->experience >= SkillTree::instance->selectedSkill->costs[SkillTree::instance->selectedSkill->level])
							{
								Player::instance->experience -= SkillTree::instance->selectedSkill->costs[SkillTree::instance->selectedSkill->level];
								SkillTree::instance->selectedSkill->level++;
								SkillTree::instance->totalExp->textUpdate(std::to_string((int)Player::instance->experience).c_str());
							} },
						"Upgrade", false);
					this->buttons.insert(this->currentSkillButton);
					break;
				}
			}
		}
	}
}

void SkillTree::getNodes()
{
	for (long long unsigned int i = 0; i < __skills.size(); i++)
	{
		SkillNode *node = new SkillNode(255, 0, 0, __skills[i].name);
		node->id = __skills[i].id;
		this->nodes[(int)__skills[i].tree].push_back(node);
	}
	for (int a = 0; a < 4; a++)
	{
		for (long long unsigned int i = 0; i < this->nodes[a].size(); i++)
		{
			for (long long unsigned int j = 0; j < __skills[this->nodes[a][i]->id].requirements.size(); j++)
			{
				if (__skills[this->nodes[a][i]->id].requirements[j].id != -1)
				{
					for (auto node : this->nodes[a])
					{
						if (node->id == __skills[this->nodes[a][i]->id].requirements[j].id)
						{
							this->nodes[a][i]->addRequirement(node);
						}
					}
				}
			}
		}
	}
}

void SkillTree::renderRightPanel()
{
	this->totalExp->render();
	if (this->selectedSkill == nullptr)
		return;

	Text *skillName = new Text(0, 250, 200, RIGHTPANELCENTERX, 100, 200, 50, this->selectedSkill->name.c_str(), Graphics::font);
	skillName->render();
	delete skillName;
	char skillLevel[30];
	snprintf(skillLevel, 30, "Level: %d/%d", this->selectedSkill->level, this->selectedSkill->maxLevel);
	Text *skillLevelText = new Text(0, 250, 200, RIGHTPANELCENTERX, 150, 200, 50, skillLevel, Graphics::font);
	skillLevelText->render();
	delete skillLevelText;
	char skillDescription[200];
	snprintf(skillDescription, 200, "%s", this->selectedSkill->description.c_str());
	Text *skillDescriptionText = new Text(0, 250, 200, RIGHTPANELCENTERX, 350, 200, 300, skillDescription, Graphics::font);
	skillDescriptionText->render();
	delete skillDescriptionText;
	char skillCost[30];
	if (this->selectedSkill->level < this->selectedSkill->maxLevel)
	{
		snprintf(skillCost, 30, "Cost: %d", this->selectedSkill->costs[this->selectedSkill->level]);
	}
	else
	{
		snprintf(skillCost, 30, "Max Level");
	}
	Text *skillCostText = new Text(0, 250, 200, RIGHTPANELCENTERX, 500, 200, 50, skillCost, Graphics::font);
	skillCostText->render();
	delete skillCostText;

	this->currentSkillButton->render();
}