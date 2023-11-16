#include "math.h"

namespace math {
	double pi = atan(1) * 4;

	/// <summary>
	/// Returns a angle based on two coordinates
	/// </summary>
	/// <param name="cood1">The first coordinate</param>
	/// <param name="cood2">The second coordinate</param>
	/// <param name="turn_to_degrees">If true, the angle will be returned in degrees instead of radius</param>
	/// <returns>The angle between cood1 and cood2 in degrees or radius</returns>
	float angle(float cood1, float cood2, bool turn_to_degrees)
	{
		float angle = -atan2(cood1, cood2);
		if (turn_to_degrees)
			angle = angle * (180 / pi);
		return angle;
	}

	/// <summary>
	/// Normalizes a vector
	/// </summary>
	/// <param name="vector">A 2D float vector</param>
	void normalizeVector(sf::Vector2f* vector)
	{
		float norme = sqrt(vector->x * vector->x + vector->y * vector->y);
		vector->x = vector->x / norme;
		vector->y = vector->y / norme;
	}
}