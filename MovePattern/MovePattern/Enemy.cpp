#include "Enemy.h"


Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}

void Enemy::Initialize(std::shared_ptr<Camera> camera)
{
	m_camera = camera;
	//LoadModel(L"enemy");
}

void Enemy::Update()
{
}

void Enemy::Render()
{
}
