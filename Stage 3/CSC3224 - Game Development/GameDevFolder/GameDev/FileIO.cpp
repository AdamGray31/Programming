#include "FileIO.h"

//create Entities and start level 1
FileIO::FileIO(vector<Entity*>* entities)
{
	map = new Entity();
	player = new Entity();
	playerShot = new Entity();
	grenade = new Entity();
	enemy = new Entity();
	walls = vector<Entity*>();

	map->setPosition(Vector2(0.0f, 100.0f));
	map->setDepth(-200.0f);
	map->setRotation(0.0f);

	player->setDepth(-199.9f);
	player->setRotation(90.0f);
	player->setRadius(10.0f);

	enemy->setDepth(-199.8f);
	enemy->setRotation(90.0f);
	enemy->setRadius(10.0f);

	entities->push_back(map);
	entities->push_back(player);
	entities->push_back(playerShot);
	entities->push_back(grenade);
	entities->push_back(enemy);

	for (int i = 0; i < 10; ++i)
	{
		walls.push_back(new Entity());
		entities->push_back(walls.at(i));
		
	}

	for each (Entity* wall in walls)
	{
		wall->setDepth(-199.99f);
		wall->setRotation(0.0f);
		wall->setRadius(50.0f);
	}
	
	currentLevel = 0;

	nextLevel();

}
	
FileIO::~FileIO()
{
}

//Read txt file and interpret level data

/*

Level file format: (Entity, x coord, y coord)

p x y 
e x y
w x y
w x y
w x y
w x y
w x y
w x y
w x y
w x y
w x y
w x y

*/

void FileIO::readLevelFile(char* levelFile)
{

	//Move shot and grenade off map
	playerShot->setPosition(Vector2(-10000, -10000));
	playerShot->setDepth(-199.8f);
	playerShot->setRotation(0.0f);
	playerShot->setRadius(10.0f);

	grenade->setPosition(Vector2(-10000, -10000));
	grenade->setDepth(-199.8f);
	grenade->setRotation(0.0f);
	grenade->setRadius(10.0f);

	//Set default positions
	Vector2 playerPos;
	Vector2 enemyPos;
	vector<Vector2> wallPos;

	playerPos = Vector2(0.0f, 0.0f);
	enemyPos = Vector2(-200.0f, 200.0f);

	float wallX = -575.0f;

	for each(Entity* wall in walls)
	{
		wallPos.push_back(Vector2(wallX, 150.0f));
		wallX += 125.0f;
	}
	//Read level file
	
	ifstream file(levelFile);
	string line;
	int currentWall = 0;
	
	while (getline(file, line))
	{
		//Store each 'word' of the line as a substring
		vector<string> substrings;
		size_t pos = 0, found;
		while ((found = line.find_first_of(' ', pos)) != string::npos)
		{
			substrings.push_back(line.substr(pos, found - pos));
			pos = found + 1;
		}
		substrings.push_back(line.substr(pos));


		if (substrings[0] == "p")
		{
			playerPos = Vector2(stof(substrings[1]), stof(substrings[2]));
		}
		else if (substrings[0] == "e")
		{
			enemyPos = Vector2(stof(substrings[1]), stof(substrings[2]));
		}
		else if (substrings[0] == "w" && currentWall < walls.size())
		{
			wallPos.at(currentWall++) = Vector2(stof(substrings[1]), stof(substrings[2]));
		}
	}
	
	player->setPosition(playerPos);
	
	enemy->setPosition(enemyPos);

	for (int i = 0; i < walls.size(); i++)
	{
		walls.at(i)->setPosition(wallPos.at(i));
	}

}

//Load next level
void FileIO::nextLevel()
{
	char fileName[19]; 
	snprintf(fileName, sizeof fileName, "levels/level%d.txt", ++currentLevel);
	readLevelFile(fileName);
}
