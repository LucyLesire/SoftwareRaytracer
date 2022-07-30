#include "ECamera.h"
#include <SDL.h>
#include <iostream>
Elite::Camera::Camera()
{
	m_Pos = { 0.f, 3.f, 9.f,0 };
	m_RotationMatrix[0] = { 1.f,0.f,0.f };
	m_RotationMatrix[1] = { 0.f,1.f,0.f };
	m_RotationMatrix[2] = { 0.f,0.f,1.f };

	Reset();
}

void Elite::Camera::Reset(const FVector3& worldUp)
{
	m_Forward = Elite::GetNormalized(m_RotationMatrix[2]);
	m_Right = Elite::GetNormalized(Cross(worldUp, m_Forward));
	m_Up = Elite::GetNormalized(Cross(m_Forward, m_Right));
}

Elite::FMatrix4 Elite::Camera::LookAt()
{
	Elite::FMatrix4 lookAtMatrix{};
	lookAtMatrix[0][0] = m_Right.x;
	lookAtMatrix[0][1] = m_Right.y;
	lookAtMatrix[0][2] = m_Right.z;

	lookAtMatrix[1][0] = m_Up.x;
	lookAtMatrix[1][1] = m_Up.y;
	lookAtMatrix[1][2] = m_Up.z;

	lookAtMatrix[2][0] = m_Forward.x;
	lookAtMatrix[2][1] = m_Forward.y;
	lookAtMatrix[2][2] = m_Forward.z;

	lookAtMatrix[3][0] = m_Pos.x;
	lookAtMatrix[3][1] = m_Pos.y;
	lookAtMatrix[3][2] = m_Pos.z;
	lookAtMatrix[3][3] = 1;

	return lookAtMatrix;
}

void Elite::Camera::Update()
{
	GetKeyboard();
	GetMouse();
}

void Elite::Camera::GetKeyboard()
{
	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_W] || state[SDL_SCANCODE_UP])
	{
		MoveForward(m_Speed);
	}
	if (state[SDL_SCANCODE_D] || state[SDL_SCANCODE_RIGHT])
	{
		MoveRight(-m_Speed);
	}
	if (state[SDL_SCANCODE_S] || state[SDL_SCANCODE_DOWN])
	{
		MoveForward(-m_Speed);
	}
	if (state[SDL_SCANCODE_A] || state [SDL_SCANCODE_LEFT])
	{
		MoveRight(m_Speed);
	}
	if (state[SDL_SCANCODE_SPACE])
	{
		MoveUp(m_Speed);
	}
	if (state[SDL_SCANCODE_LSHIFT])
	{
		MoveUp(-m_Speed);
	}
}

void Elite::Camera::GetMouse()
{
	int x, y;
	Uint32 buttons;

	SDL_PumpEvents();  // make sure we have the latest mouse state.

	buttons = SDL_GetRelativeMouseState(&x, &y);

	if ((buttons & SDL_BUTTON_LMASK) != 0)
	{
		if ((buttons & SDL_BUTTON_RMASK) != 0)
		{
			if (y != 0)
			{
				MoveUp(float(y));
			}
		}
		else if ((buttons & SDL_BUTTON_LMASK) != 0)
		{
			if (x != 0 && y != 0)
			{
				RotateAroundUp(x * m_RotationSpeed);
				MoveForward(float(-y));
			}
		}
	}

	else if ((buttons & SDL_BUTTON_RMASK) != 0)
	{
		if (x != 0 && y != 0)
		{
			RotateAroundUp(x * m_RotationSpeed);
			RotateAroundRight(-y * m_RotationSpeed);
		}
	}
}

void Elite::Camera::MoveRight(float right)
{
	m_Pos += right * Elite::GetNormalized(m_Right);
	Reset();
}

void Elite::Camera::MoveForward(float forward)
{
	m_Pos -= forward * Elite::GetNormalized(m_Forward);
	Reset();
}

void Elite::Camera::MoveUp(float up)
{
	m_Pos.y += up;
	Reset();
}

void Elite::Camera::RotateAroundUp(float right)
{
	Elite::FMatrix3 rotation = MakeRotation(right, {0.f,1.f,0.f});

	m_RotationMatrix *= rotation;
	Reset();
}

void Elite::Camera::RotateAroundRight(float forward)
{
	Elite::FMatrix3 rotation = MakeRotation(forward, {1.f,0.f,0.f});

	m_RotationMatrix *= rotation;
	Reset();
}
