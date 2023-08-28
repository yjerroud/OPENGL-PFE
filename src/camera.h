#ifndef CAMERA_H
#define CAMERA_H

#include "math.h"

struct	Camera
{
	Vec3		position;
	Vec3		worldUp;
	Vec3		at;
	Vec3		x;
	Vec3		y;
	Vec3		z;
	
	float	   yaw;	   //rotation around yAxis
	float	   pitch;	//rotation around xAxis
	
	float	   fov;
};

static Camera	InitCamera(Vec3 position, Vec3 worldUp, Vec3 at, float fov);

static void	  CameraPitch(Camera& camera, float value);
static void	  CameraYaw(Camera& camera, float value);
static void	  CameraSideStep(Camera& camera, float value);
static void	  CameraForwardStep(Camera& camera, float value);
static void	  UpdateCameraCoords(Camera& camera);




#endif //CAMERA_H
