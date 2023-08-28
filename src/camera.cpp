#include "camera.h"

static Camera	InitCamera(Vec3 position, Vec3 worldUp, Vec3 at, float fov)
{
	Camera	result = {};
	
	result.position = position;
	result.worldUp = worldUp;
	result.at = at;
	result.fov = toRadians(fov);
	result.z = normalize(at - position);
	result.x = normalize(cross(worldUp, result.z));
	result.y = normalize(cross(result.z, result.x));
	
	result.yaw = toDegrees(acosf(dot(Vec3(0.0f, 1.0f, 0.0f), result.y)));
	result.pitch = toDegrees(acosf(dot(Vec3(1.0f, 0.0f, 0.0f), result.x)));
	
	return (result);
}

static void	  CameraPitch(Camera& camera, float angle)
{
	camera.pitch += angle;
	
	if (camera.pitch > 89.0f)
		camera.pitch = 89.0f;
	if (camera.pitch < -89.0f)
		camera.pitch = -89.0f;
	
	UpdateCameraCoords(camera);
}

static void	  CameraYaw(Camera& camera, float angle)
{
	camera.yaw += angle;
	
	UpdateCameraCoords(camera);
}

static void	  CameraSideStep(Camera& camera, float value)
{
	camera.position = camera.position + (camera.x * value);
	camera.at = camera.at + (camera.x * value);
	//camera.z = normalize(camera.at - camera.position);
	
}

static void	  CameraForwardStep(Camera& camera, float value)
{
	camera.position = camera.position + (camera.z * value);
	camera.at = camera.at + (camera.z * value);
}

static void	  UpdateCameraCoords(Camera& camera)
{
	float	yawR = toRadians(camera.yaw);
	float	pitchR = toRadians(camera.pitch);
	
	M4x4	rotYaw = rotateY(yawR);
	M4x4	rotPitch = rotateX(pitchR);
	
	
	Vec4	z = Vec4(0.0f, 0.0f, 1.0f, 0.0f);
	
	z = z * rotYaw;
	z = z * rotPitch;
	
	
	camera.z.x = z.x;
	camera.z.y = z.y;
	camera.z.z = z.z;
	camera.z = normalize(camera.z);
	camera.x = normalize(cross(camera.worldUp, camera.z));
	camera.y = normalize(cross(camera.z, camera.x));
}