#include "Player.h"


Player::Player()
{
}


Player::~Player()
{
}

void Player::Initialize(std::shared_ptr<Camera> camera)
{
	m_camera = camera;
	//LoadModel(L"player");
}

void Player::Update()
{
}

void Player::Render()
{
}
