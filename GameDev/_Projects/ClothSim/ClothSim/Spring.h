#include "MassPoint.h"
#include "Vec3.h"

class Spring
{
private:
	float K, rest, restDistance;
	Vec3 restPos;
public:
	MassPoint *p1, *p2;
	Spring();
	Spring(MassPoint *_p1, MassPoint *_p2);
	void Render();
	void Update(float time);
	Vec3 GetForce();
	~Spring();
};