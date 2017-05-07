#include "Spring.h"

class Cloth
{
private:
	Spring **springs;
	int numSprings;
public:
	MassPoint ***massPoints;
	int length, width;
	Cloth();
	Cloth(int _length, int _width);
	~Cloth();
	void UpdateForces();
	void Update(float time);
	void Render();
};