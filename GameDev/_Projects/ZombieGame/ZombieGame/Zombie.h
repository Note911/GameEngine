#pragma once

#include "Agent.h"

class Zombie : public Agent
{
public:
    Zombie();
    ~Zombie();

    void init(float speed, glm::vec2 pos);

    virtual void update(const std::vector<std::string>& levelData,
                        std::vector<Human*>& humans,
                        std::vector<Zombie*>& zombies);
private:
	glm::vec2 Wander();
	double _wanderDistance;
	double _wanderRadius;
	double _wanderJitter;
	glm::vec2 _heading;
	glm::vec2 _wanderTarget;
	int RandomClamped();
    Human* getNearestHuman(std::vector<Human*>& humans);
};

