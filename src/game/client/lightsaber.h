#ifndef GAME_CLIENT_COMPONENTS_LIGHTSABER_H
#define GAME_CLIENT_COMPONENTS_LIGHTSABER_H

#include <base/vmath.h>
#include <base/math.h>
#include <base/system.h>

class CLightsaber
{
private:
	int64 m_LastUpdate;
	

public: 
	CLightsaber()
	{
		m_LightEnd = vec2(0, 0);
		m_TargetDirection = vec2(0, 0);
		
		for (int i = 0; i < 10; i++)
		{
			m_aOldStartPos[i] = vec2(0, 0);
			m_aOldTipPos[i] = vec2(0, 0);
		}
		
		m_Offset = vec2(0, 0);
		m_FlipY = -1;
		m_Alpha = 1.0f;
		
		m_SaberColor = vec3(0, 0, 0);
		
		/*while (!(m_SaberColor.x > 0.9f || m_SaberColor.y > 0.9f || m_SaberColor.z > 0.9f))
		{
			m_SaberColor = vec3(frandom(), frandom(), frandom());
		}*/
		
		int i = frandom()*7;
		if (i > 6) i = 6;
		switch (i)
		{
		case 0: m_SaberColor = vec3(1, 0.1f, 0.1f); break;
		case 1: m_SaberColor = vec3(1, 1, 0); break;
		case 2: m_SaberColor = vec3(1, 0, 1); break;
		case 3: m_SaberColor = vec3(0, 1, 0); break;
		case 4: m_SaberColor = vec3(0, 1, 1); break;
		case 5: m_SaberColor = vec3(0.1f, 0.1f, 1); break;
		case 6: m_SaberColor = vec3(1, 1, 1); break;
		};
	};
	
	vec2 m_Offset, m_TargetOffset;
	
	float m_Angle, m_TargetAngle;
	
	vec2 m_aOldStartPos[10];
	vec2 m_aOldTipPos[10];
	vec2 m_TargetDirection;
	vec2 m_LightEnd;
	
	int m_FlipY;
	float m_Alpha;
	
	vec3 m_SaberColor;
	
	void DoSteps(vec2 Position);
	void Clear(vec2 Position);
};



#endif