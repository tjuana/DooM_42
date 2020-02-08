//
// Created by Nymphadora Shelly on 19/12/2019.
//

#include "doom.h"
/*
 * min: Choose smaller of two scalars.
 */
float min(float a, float b)
{
    return  (((a) < (b)) ? (a) : (b));
}
/*
 * max: Choose greater of two scalars.
 */
float max(float a, float b)
{
    return  (((a) > (b)) ? (a) : (b));
}
/*
 * clamp: fijar los valores  eun rango establecido
 */
float clamp(float a, float mi, float ma)
{
    return  (min(max(a,mi),ma));
}
/*
 * vxs: Vector cross product
 */
float vxs(float x0, float y0, float x1, float y1)
{
    return ((x0)*(y1) - (x1)*(y0));
}
/*
 * Overlap:  Determine whether the two number ranges overlap.
 */
int Overlap(float a0, float a1, float b0, float b1)
{
    return (min(a0,a1) <= max(b0,b1) && min(b0,b1) <= max(a0,a1));
}
/*
 * IntersectBox: Determine whether two 2D-boxes intersect.
 */
int IntersectBox(float x0, float y0, float x1, float y1,float x2, float y2, float x3, float y3)
{
    return (Overlap(x0,x1,x2,x3) && Overlap(y0,y1,y2,y3));
}
/*
 * PointSide: Determine which side of a line the point is on. Return value: <0, =0 or >0.
 */
float PointSide(float px, float py, float x0, float y0,float x1, float y1)
{
    return (vxs((x1)-(x0), (y1)-(y0), (px)-(x0), (py)-(y0)));
}
/*
 * Intersect: Calculate the point of intersection between two lines.
 */
t_new_xy intersect(float x1, float y1, float x2, float y2,float x3, float y3, float x4, float y4)
{
	float		u_x;
	float		u_y;
	float		denom;
	float		num_x;
	float		num_y;

	denom  = (y4-y3) * (x2-x1) - (x4-x3) * (y2-y1);
	num_x = (x4-x3) * (y1-y3) - (y4-y3) * (x1-x3);
	num_y = (x2-x1) * (y1-y3) - (y2-y1) * (x1-x3);
	if (fabs(num_x) < FLT_EPSILON && fabs(num_y) < \
	FLT_EPSILON && fabs(denom) < FLT_EPSILON)
		return((t_new_xy){(x1 + x2) / 2, (y1 + y2) / 2});
	if (ABS(denom) < FLT_EPSILON)
		return((t_new_xy){-1, -1});
	u_x = num_x / denom;
	u_y = num_y	 / denom;
	if (u_x < 0 || u_x > 1 || u_y < 0 || u_y > 1)
		return((t_new_xy){ -1, -1});
	return((t_new_xy){x1 + u_x * (x2 - x1), y1 + u_x * (y2 - y1)});
}


float Yaw(float y, float z, t_new_player *player)
{
	// // printf("y:%f   z:%f   yaw:%f\n", y, z, player->yaw);
    return(y + z * player->yaw);
}

double to_deg(double radians)
{
    return radians * (180.0 / M_PI);
}