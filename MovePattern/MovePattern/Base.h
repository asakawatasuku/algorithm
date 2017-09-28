#pragma once

#include "Camera.h"
#include <memory>
#include <Model.h>
#include <d3d11.h>
#include <SimpleMath.h>

class Base
{
protected:
	static std::unique_ptr<DirectX::CommonStates> m_states;
	static std::shared_ptr<Camera> m_camera;

protected:
	std::unique_ptr<DirectX::Model> m_model;
	DirectX::SimpleMath::Vector3 m_scale;
	DirectX::SimpleMath::Vector3 m_rot;
	DirectX::SimpleMath::Vector3 m_pos;	// ç¿ïW
	DirectX::SimpleMath::Matrix m_world;
	float m_speed;

public:
	static void StaticInitialize(std::shared_ptr<Camera> camera);
public:
	virtual ~Base() {}

	virtual void Initialize(const std::wstring& file_name);
	virtual void Update();
	virtual void Render();
	virtual void Finalize() = 0;

	void LoadModel(const std::wstring& file_name);

	float GetSpeed()
	{
		return m_speed;
	}
	DirectX::SimpleMath::Vector3 GetPos()
	{
		return m_pos;
	}

	void SetPos(DirectX::SimpleMath::Vector3 pos)
	{
		m_pos = pos;
	}
};

