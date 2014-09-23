
#include <game/client/lightsaber.h>
#include <game/client/helpers.h>

void CLightsaber::Clear(vec2 Position)
{
	m_Alpha = 1.0f;
	
	m_LightEnd = m_TargetDirection*60;
	
	for (int i = 0; i < 9; i++)
	{
		m_aOldTipPos[i] = Position + m_Offset + m_LightEnd;
		m_aOldStartPos[i] =  Position + m_Offset + m_TargetDirection*12;
	}
}

void CLightsaber::DoSteps(vec2 Position)
{
	int64 currentTime = time_get();
	if ((currentTime-m_LastUpdate > time_freq()) || (m_LastUpdate == 0))
		m_LastUpdate = currentTime;
		
	int step = time_freq()/60;
	
	for (;m_LastUpdate < currentTime; m_LastUpdate += step)
	{
	
		for (int i = 9; i > 0; i--)
		{
			m_aOldTipPos[i] = m_aOldTipPos[i-1];
			m_aOldStartPos[i] = m_aOldStartPos[i-1];
		}
	
		m_aOldTipPos[0] =  Position + m_Offset + m_LightEnd;
		m_aOldStartPos[0] = Position + m_Offset + m_TargetDirection*12;
	
		// do dynamic stuff
		m_LightEnd.x += (m_TargetDirection.x*60-m_LightEnd.x)/1.4f;
		m_LightEnd.y += (m_TargetDirection.y*60-m_LightEnd.y)/1.4f;
		
		m_Offset.x += (m_TargetOffset.x-m_Offset.x)/4.0f;
		m_Offset.y += (m_TargetOffset.y-m_Offset.y)/4.0f;
		m_Alpha += 0.025f;
	}
	
	// do static stuff
}
