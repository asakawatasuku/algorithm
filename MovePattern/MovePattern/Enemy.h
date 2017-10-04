/// <summary>
/// �G�l�~�[�N���X
/// </summary>

#pragma once

#include "Base.h"
#include "MovingPattern.h"
#include "WaypointNavigation.h"
#include "KeyboardUtil.h"
#include <SpriteBatch.h>
#include <SpriteFont.h>

class Enemy :public Base
{
private:
	enum PATTERN_KIND
	{
		PURSUIT,
		GETAWAY,
		INTERCEPTION,
		WAYPOINT_NAVIGATION,
		WAYPOINT_NAVIGATION_RENDER,

		PATTERN_KIND_NUM
	};

	// �ړ��p�^�[��
	std::unique_ptr<MovingPattern> m_moving_pattern;
	std::unique_ptr<WaypointNavigation> m_waypoint;
	// �ǐՑΏ�
	Base* m_target;

	// �ړ��p�^�[���\���p�ϐ�
	int m_pattern_num;

	KeyboardUtil* m_keyboard;

	DirectX::SpriteBatch* m_batch;
	DirectX::SpriteFont* m_font;
public:
	Enemy();
	~Enemy();

	void Initialize(const std::wstring& file_name);
	void Update();
	void Render();
	void Finalize();

	void SetTarget(Base* target)
	{
		m_target = target;
	}
	void SetKeyboard(KeyboardUtil* keyboard)
	{
		m_keyboard = keyboard;
	}
	void SetSpriteBatch(DirectX::SpriteBatch* batch)
	{
		m_batch = batch;
	}
	void SetSpriteFont(DirectX::SpriteFont* font)
	{
		m_font = font;
	}
};
