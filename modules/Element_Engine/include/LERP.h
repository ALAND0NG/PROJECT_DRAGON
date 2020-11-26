#pragma once //just basic class for LERP
static class LERP
{

	static float DoLERP(float v0, float v1, float t)
	{
		return v0 + t * (v1 - v0);
	}
};