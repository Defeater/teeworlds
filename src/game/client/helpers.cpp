#include <game/client/helpers.h>


float Wrapvalue(float Angle)
{
  while (Angle < 0.0f || Angle >=360.0f )
  {
    if (Angle < 0.0f) Angle +=360.0f;
    if (Angle >= 360.0f ) Angle -=360.0f;
  }
  return Angle;
}

float TCurvevalue(float Dest, float Current, float Time)
{
	return Current + (Dest - Current) * Time;
}

float Curveangle(float Dest, float Current, float Speed)
{
   if (Current - Dest > 180)
   {
      Current -= 360;
      Current += (Dest - Current) / Speed;
      Current += 360;
      return Wrapvalue(Current);
   }
   else if (Current - Dest < -180)
   {
      Current += 360;
      Current += (Dest - Current) / Speed;
      Current -= 360;
      return Wrapvalue(Current);
   }
   else
   {
      Current += (Dest - Current) / Speed;
      return Current;
   }
}



float Curvevalue(float Dest, float Current, float Speed)
{
	return Current + (Dest - Current) / Speed;
}