#include <cmath>

using namespace sf;

namespace math
{
	double pi = atan(1) * 4;

	float angle(float cood1, float cood2, bool turn_to_degrees)
	{
		float angle = -atan2(cood1, cood2);
		if (turn_to_degrees)
			angle = angle * (180 / pi);
		return angle;
	};

	void normalizeVector(Vector2f* vector)
	{
		float norme = sqrt(vector->x*vector->x + vector->y*vector->y);
		vector->x = vector->x / norme;
		vector->y = vector->y / norme;
	}
}