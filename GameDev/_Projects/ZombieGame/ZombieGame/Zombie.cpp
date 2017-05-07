#include "Zombie.h"

#include "Human.h"

#include <stdio.h>
#include <time.h>

Zombie::Zombie()
{
}

Zombie::~Zombie()
{
}

void Zombie::init(float speed, glm::vec2 pos) {
    _speed = speed;
    _position = pos;
    _health = 150;

	srand(time(NULL));
    // Set Green Color
    _color.r = 0;
    _color.g = 160;
    _color.b = 0;
    _color.a = 255;

	_wanderDistance = 10;
	_wanderRadius = 10;
	_wanderJitter = 1.5;

	
	_heading = glm::vec2(RandomClamped(), RandomClamped());

}

void Zombie::update(const std::vector<std::string>& levelData,
                    std::vector<Human*>& humans,
                    std::vector<Zombie*>& zombies) {

    // Find the closest human
    Human* closestHuman = getNearestHuman(humans);

    // If we found a human, move towards him
    if (closestHuman != nullptr) {
		glm::vec2 direction = closestHuman->getPosition() - _position;
		float distance = sqrt(pow(direction.x, 2) + pow(direction.y, 2));
		if (distance < 300) {
			// Get the direction vector twoards the player
			direction = glm::normalize(closestHuman->getPosition() - _position);
			_heading = direction;
			_position += direction * _speed;
		}
		else
		{
			glm::vec2 target = Wander();
			_heading = target / sqrt(pow(target.x, 2) + pow(target.y, 2));
			_position += _heading * _speed;

		}
    }

    // Do collision
    collideWithLevel(levelData);
}

Human* Zombie::getNearestHuman(std::vector<Human*>& humans) {
    Human* closestHuman = nullptr;
    float smallestDistance = 9999999.0f;

    for (int i = 0; i < humans.size(); i++) {
        // Get the direction vector
        glm::vec2 distVec = humans[i]->getPosition() - _position;
        // Get distance
        float distance = glm::length(distVec);

        // If this person is closer than the closest person, this is the new closest
        if (distance < smallestDistance) {
            smallestDistance = distance;
            closestHuman = humans[i];
        }
    }
    
    return closestHuman;
}

glm::vec2 Zombie::Wander() {
	_wanderTarget += glm::vec2(RandomClamped() * _wanderJitter, RandomClamped() * _wanderJitter);
	_wanderTarget /= sqrt(pow(_wanderTarget.x, 2) + pow(_wanderTarget.y, 2));
	_wanderTarget *= _wanderRadius;
	glm::vec2 targetLocal = _wanderTarget + (glm::vec2(_heading.x * _wanderDistance, _heading.y * _wanderDistance));
	return targetLocal;

}

int Zombie::RandomClamped() {
	int ran = rand() % 3 - 1;

	return ran;
}