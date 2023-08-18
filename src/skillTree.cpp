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
	: selectedSkill(nullptr), totalExp(nullptr)
{
	SkillTree::instance = this;
	Game::currentState = SKILLTREE;
	buttons.insert(new Button(
		255, 0, 0, 0, 0, 100, 50, []()
		{ Game::currentState = MENU; SkillTree::instance->~SkillTree(); },
		"Back", false));
	this->getNodes();
	char *exp = new char[100];
	sprintf(exp, "Exp: %d", (int)Player::instance->experience);
	this->totalExp = new Text(0, 250, 200, RIGHTPANELCENTERX, 50, 100, 50, exp, "Kichenset.otf", 64);
	for (long long unsigned int i = 0; i < nodes.size(); i++)
	{
		for (long long unsigned int j = 0; j < nodes[i]->requirements.size(); j++)
		{
			for (long long unsigned int k = 0; k < nodes.size(); k++)
			{
				if (nodes[k] == nodes[i]->requirements[j])
				{
					nodes[k]->requiredBy++;
				}
			}
		}
	}
	for (SkillNode *node : nodes)
	{
		node->depth = this->calculateDepth(node, node, 0);
	}
	this->autoLayout();
	for (SkillNode *node : nodes)
	{
		node->text = new Text(0, 255, 0, node->getX(), node->getY(), node->getWidth(), node->getHeight(), node->name.c_str(), Graphics::font);
	}
}

int SkillTree::calculateDepth(SkillNode *node, SkillNode *current, int maxDepth)
{
	if (node->requirements.size() > 0)
	{
		maxDepth++;
	}
	for (SkillNode *req : node->requirements)
	{
		maxDepth = this->calculateDepth(req, current, maxDepth);
	}
	return maxDepth;
}

void SkillTree::autoLayout()
{
	std::sort(nodes.begin(), nodes.end(), [](SkillNode *a, SkillNode *b)
			  { return a->requirements.size() < b->requirements.size(); });
	int x = 250;
	int y = 550;
	int nodeWidth = 100;
	for (SkillNode *node : nodes)
	{

		if (node->requirements.size() == 0)
		{
			node->setY(y);
			node->setX(x);
			x += nodeWidth + 175;
		}
		else
		{
			node->setY(y - node->depth * 150);
			for (SkillNode *req : node->requirements)
			{
				int minx = req->getX();
				minx -= (150 * (req->requiredBy - 1)) / 2;
				minx += 150 * req->checkedRequirements;

				node->setX(minx);
				req->checkedRequirements++;
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
	for (auto node : this->nodes)
	{
		node->~SkillNode();
	}
	delete this->totalExp;
}

void SkillTree::render()
{
	for (auto button : buttons)
	{
		button->render();
	}
	for (auto node : nodes)
	{
		for (auto req : node->requirements)
		{
			SDL_SetRenderDrawColor(Graphics::renderer, 255, 255, 255, 255);
			SDL_RenderDrawLine(Graphics::renderer, node->getX(), node->getY(), req->getX(), req->getY());
		}
	}
	for (auto node : nodes)
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
			for (auto *node : this->nodes)
			{
				if (SDL_PointInRect(&point, &node->rect))
				{
					this->selectedSkill = &__skills[node->id];
					// if (__skills[node->id].level < __skills[node->id].maxLevel && Player::instance->experience >= __skills[node->id].costs[__skills[node->id].level])
					// {
					// 	// Player::instance->experience -= __skills[node->id].costs[__skills[node->id].level];
					// 	// __skills[node->id].level++;
					// }
					break;
				}
			}
		}
	}
}

void SkillTree::getNodes()
{
	for (long long unsigned int i = 0; i < sizeof(__skills) / sizeof(skill); i++)
	{
		SkillNode *node = new SkillNode(255, 0, 0, __skills[i].name);
		node->id = __skills[i].id;
		this->nodes.push_back(node);
	}
	for (long long unsigned int i = 0; i < sizeof(__skills) / sizeof(skill); i++)
	{
		if (__skills[i].requirements.id != -1)
		{
			for (long long unsigned int j = 0; j < sizeof(__skills) / sizeof(skill); j++)
			{
				if (__skills[i].requirements.id == __skills[j].id)
				{
					this->nodes[i]->addRequirement(this->nodes[j]);
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

	Text *skillName = new Text(0, 255, 0, RIGHTPANELCENTERX, 100, 100, 50, this->selectedSkill->name, "Kichenset.otf", 64);

	char skillLevel[10];
}