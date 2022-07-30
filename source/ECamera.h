#pragma once
#include "ERenderer.h"
#include "EMath.h"

namespace Elite
{
	class Camera
	{
	public:
		Camera();
		~Camera() = default;

		Camera(const Camera&) = delete;
		Camera(Camera&&) noexcept = delete;
		Camera& operator=(const Camera&) = delete;
		Camera& operator=(Camera&&) noexcept = delete;

		void Reset(const FVector3& worldUp = {0.f,1.f,0.f});
		FMatrix4 LookAt();
		float GetFov() const { return tan(ToRadians(m_Fov / 2.f)); };
		void Update();

	private:
		float m_Fov = 90.f;
		Elite::FPoint4 m_Pos{};
		Elite::FVector3 m_Forward{};
		Elite::FVector3 m_Right{};
		Elite::FVector3 m_Up{};
		Elite::FMatrix3 m_RotationMatrix{};
		const float m_Speed = 0.5f;
		const float m_RotationSpeed = Elite::ToRadians(0.25f);

		void GetKeyboard();
		void GetMouse();
		void MoveRight(float right);
		void MoveForward(float forward);
		void MoveUp(float up);
		void RotateAroundUp(float right);
		void RotateAroundRight(float forward);
	};
}


