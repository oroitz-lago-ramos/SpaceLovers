#include <set>
#include <iostream>
#include <SDL2/SDL.h>

#include "skillTree.hpp"
#include "button.hpp"
#include "game.hpp"

std::set<Button *> SkillTree::buttons = {};
SkillTree *SkillTree::instance = nullptr;

SkillTree::SkillTree()
{
	SkillTree::instance = this;
	Game::currentState = SKILLTREE;
	buttons.insert(new Button(
		255, 0, 0, 0, 0, 100, 50, []()
		{ Game::currentState = MENU; SkillTree::instance->~SkillTree(); },
		"Back", false));
	SkillNode *node1 = new SkillNode(100, 100, 100, "Node 1");
	SkillNode *node2 = new SkillNode(200, 100, 100, "Node 2");
	SkillNode *node3 = new SkillNode(100, 200, 100, "Node 3");
	this->nodes.insert(node1);
	this->nodes.insert(node2);
	this->nodes.insert(node3);
	node2->addRequirement(node1);
	node3->addRequirement(node1);
	node3->addRequirement(node2);
	node3->autoLayout(100, 100);
	// node2->autoLayout(100, 100);
	// node1->autoLayout(100, 100);
}

SkillTree::~SkillTree()
{
	Game::currentState = MENU;
	for (auto button : buttons)
	{
		buttons.erase(button);
		button->~Button();
	}
}

void SkillTree::render()
{
	for (auto button : buttons)
	{
		button->render();
	}
	for (auto node : nodes)
	{
		node->render();
	}
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			Game::isRunning = false;
		}
		if (event.type == SDL_MOUSEBUTTONDOWN)
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
		}
	}
}