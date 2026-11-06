#pragma once
//#include <Pixel.h>
#include "Pixel/Core.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

enum CameraMovement
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

//Default Camera Values
const f32 YAW = -90.0f;
const f32 PITCH = 0.0f;
const f32 WALKSPEED = 5.0f;
const f32 LOOKSENSITIVITY = 0.25f;
const f32 ZOOM = 45.0f;
const f32 ZOOMSENSITIVITY = 1.0f;

namespace Pixel
{


class PIXEL_API Camera
{
	public:
		Camera(glm::vec3 position, glm::vec3 up, glm::vec3 front, glm::vec3 worldUp = {0,1,0}, f32 yaw = YAW, f32 pitch = PITCH, f32 movementSpeed = WALKSPEED, f32 sensitivity = LOOKSENSITIVITY, f32 zoom = ZOOM)
		{

			m_CamPos = position;
			m_CamFront = front;
			m_CamUp = up;
			m_CamRight = { 0,0,0 };
			m_WorldUp = worldUp;

			m_CamYaw = yaw;;
			m_CamPitch = pitch;
			m_CamFOV = zoom;
			m_MouseLookSensitivity = sensitivity;
			m_CamWalkSpeeed = movementSpeed;
			m_MouseZoomSensitivity = ZOOMSENSITIVITY;

			updateCameraVectors();
		}

		glm::mat4 GetViewMatrix()
		{
			return glm::lookAt(m_CamPos, m_CamPos + m_CamFront, m_CamUp);
		}

		glm::mat4 getProjectionMatrix(ui32 width, ui32 height)
		{

			glm::mat4 projection = glm::perspective(glm::radians(m_CamFOV), (f32)width / (f32)height, 0.1f, 100.0f);
			return projection;
		}

		void ProcessKeyboard(CameraMovement direction, float deltaTime, bool lockCameraYMovement = false)
		{
			float velocity = m_CamWalkSpeeed * deltaTime;

			glm::vec3 forward = m_CamFront;
			glm::vec3 right = m_CamRight;

			if (lockCameraYMovement)
			{
				forward.y = 0.0f;
				right.y = 0.0f;
				forward = glm::normalize(forward);
				right = glm::normalize(right);
			}

			if (direction == FORWARD)  m_CamPos += forward * velocity;
			if (direction == BACKWARD) m_CamPos -= forward * velocity;
			if (direction == LEFT)     m_CamPos -= right * velocity;
			if (direction == RIGHT)    m_CamPos += right * velocity;
		}

		void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true)
		{
			xoffset *= m_MouseLookSensitivity;
			yoffset *= m_MouseLookSensitivity;

			m_CamYaw += xoffset;
			m_CamPitch -= yoffset;

			// make sure that when pitch is out of bounds, screen doesn't get flipped
			if (constrainPitch)
			{
				if (m_CamPitch > 89.0f)m_CamPitch = 89.0f;
				if (m_CamPitch < -89.0f)m_CamPitch = -89.0f;
			}

			// update Front, Right and Up Vectors using the updated Euler angles
			updateCameraVectors();
		}

		void ProcessMouseScroll(float yoffset)
		{
			m_CamFOV -= (float)yoffset;
			if (m_CamFOV < 1.0f) m_CamFOV = 1.0f;
			if (m_CamFOV > 45.0f) m_CamFOV = 45.0f;
		}

		f32 getFOV()
		{
			return m_CamFOV;
		}

	private:
		glm::vec3 m_CamPos;
		glm::vec3 m_CamFront;
		glm::vec3 m_CamRight;
		glm::vec3 m_CamUp;

		glm::vec3 m_WorldUp;

		f32 m_CamYaw;
		f32 m_CamPitch;
		f32 m_CamFOV;
		f32 m_MouseLookSensitivity;
		f32 m_CamWalkSpeeed;
		f32 m_MouseZoomSensitivity;

		void updateCameraVectors()
		{
			// calculate the new Front vector
			glm::vec3 newFront;
			newFront.x = cos(glm::radians(m_CamYaw)) * cos(glm::radians(m_CamPitch));
			newFront.y = sin(glm::radians(m_CamPitch));
			newFront.z = sin(glm::radians(m_CamYaw)) * cos(glm::radians(m_CamPitch));
			m_CamFront = glm::normalize(newFront);
			m_CamRight = glm::normalize(glm::cross(m_CamFront, m_WorldUp));
			m_CamUp = glm::normalize(glm::cross(m_CamRight, m_CamFront));
		}
	};
}