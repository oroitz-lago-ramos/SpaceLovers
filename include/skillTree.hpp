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

// class SkillNode : public Entity
// {
// public:
// 	SkillNode(int r, int g, int b, std::string name);
// 	~SkillNode();

// 	void addRequirement(SkillNode *requirement);
// 	void setPosition(int x, int y);
// 	std::string name;

// private:
// 	std::vector<SkillNode *> requirements;
// };

// class Entity
// {
// public:
//     Entity(int r, int g, int b, int x, int y, int width, int height);
//     ~Entity();
//     void render();
//     void setX(float x);
//     float getX();
//     void setY(float y);
//     float getY();

//     int r;
//     int g;
//     int b;
//     int width;
//     int height;
//     SDL_Rect rect;
//     SDL_Texture* texture;

// private:
//     float x;
//     float y;

// };

#endif