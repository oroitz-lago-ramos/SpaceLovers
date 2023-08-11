#include <vector>
#include <set>
#include <iostream>
#include <SDL2/SDL.h>

#include "skillTree.hpp"
#include "button.hpp"
#include "game.hpp"
#include "graphics.hpp"

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

	// red
	SkillNode *node1 = new SkillNode(255, 0, 0, "Node 1");
	// green
	SkillNode *node2 = new SkillNode(0, 255, 0, "Node 2");
	// blue
	SkillNode *node3 = new SkillNode(0, 0, 255, "Node 3");
	SkillNode *node4 = new SkillNode(200, 200, 200, "Node 4");
	SkillNode *node5 = new SkillNode(200, 200, 0, "Node 5");
	this->nodes.push_back(node1);
	this->nodes.push_back(node2);
	this->nodes.push_back(node3);
	this->nodes.push_back(node4);
	this->nodes.push_back(node5);
	node2->addRequirement(node1);
	node3->addRequirement(node2);
	// node3->addRequirement(node2);
	node4->addRequirement(node2);
	node5->addRequirement(node2);
	for (int i = 0; i < nodes.size(); i++)
	{
		for (int j = 0; j < nodes[i]->requirements.size(); j++)
		{
			for (int k = 0; k < nodes.size(); k++)
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
		int max = 0;
		node->depth = this->calculateDepth(node, node, 0);
	}
	this->autoLayout();
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
	int nodeHeight = 100;
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
	}
	SDL_Event event;
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
		}
	}
}