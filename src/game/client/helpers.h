#ifndef GAME_CLIENT_HELPERS_H
#define GAME_CLIENT_HELPERS_H

#define RAD 0.017453292519943295769236907684886f
#define DEG 57.2957795131f


float Wrapvalue(float Angle);

float TCurvevalue(float Dest, float Current, float Time);

float Curveangle(float Dest, float Current, float Speed);


float Curvevalue(float Dest, float Current, float Speed);

#endif