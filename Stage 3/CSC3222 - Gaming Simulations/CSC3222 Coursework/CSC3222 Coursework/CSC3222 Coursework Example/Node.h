#pragma once
#include <vector>

class Node
{

public:
	Node();
	Node(float x, float y);
	~Node();

	int getX() const;
	int getY() const;
	std::vector<Node*> getConnectedNodes() const;
	std::vector<int> getConnectedNodeCosts() const;
	int getF() const;
	int getG() const;
	int getH() const;
	Node* getParent() const;

	void setF();
	void setG(int g);
	void setH(Node start, Node end);
	void setParent(Node* parent);
	void addConnectedNode(Node* node);


private:
	int x;
	int y;
	std::vector<Node*> connectedNodes;
	std::vector<int> connectedNodeCosts;

	//Total cost of the node
	int f;

	//Cost to reach node from start
	int g;

	//Cost to reach goal from this node
	int h;

	Node* parent;
};

