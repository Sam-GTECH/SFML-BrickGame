#include <cmath>

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
}