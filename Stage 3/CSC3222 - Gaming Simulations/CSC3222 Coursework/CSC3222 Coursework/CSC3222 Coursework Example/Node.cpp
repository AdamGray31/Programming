#include "Node.h"



Node::Node()
{
}

Node::Node(float x, float y)
{
	this->x = floor((x - 12.0f) / 26.66f);
	this->y = floor((y + 2.0f) / 26.66f);
	this->parent = nullptr;
}


Node::~Node()
{
}

int Node::getX() const
{
	return x;
}

int Node::getY() const
{
	return y;
}

std::vector<Node*> Node::getConnectedNodes() const
{
	return connectedNodes;
}

std::vector<int> Node::getConnectedNodeCosts() const
{
	return connectedNodeCosts;
}

int Node::getF() const
{
	return f;
}

int Node::getG() const
{
	return g;
}

int Node::getH() const
{
	return h;
}

Node * Node::getParent() const
{
	return parent;
}

void Node::setF()
{
	f = g + h;
}

void Node::setG(int g)
{
	this->g = g;
}

void Node::setH(Node start, Node end)
{
	h = 0;
	int dx = abs(start.x - end.x);
	int dy = abs(start.y - end.y);

	while (dx > 0 || dy > 0)
	{
		if (dx > 0 && dy > 0)
		{
			h += 15;
			--dx;
			--dy;
		}
		else if (dx > 0)
		{
			h += 10;
			--dx;
		}
		else if (dy > 0)
		{
			h += 10;
			--dy;
		}
	}
}

void Node::setParent(Node* parent)
{
	this->parent = parent;
}

void Node::addConnectedNode(Node* node)
{
	connectedNodes.push_back(node);
}
