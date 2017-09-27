#pragma once

#ifndef MYGAME 
#define MYGAME

#include "Game.h"
#include "Player.h"
#include "Enemy.h"


class MyGame : public Game {
public:
	// �R���X�g���N�^ Constructor
	MyGame(int width, int height);
	// �Q�[���I�u�W�F�N�g���������� Initialize game object
	void Initialize() override;
	// �Q�[�����X�V���� Update game
	void Update(const DX::StepTimer& timer) override;
	// �Q�[���V�[����`�悷�� Draws the scene
	void Render(const DX::StepTimer& timer) override;
	// �I�������������Ȃ� Finalize game
	void Finalize() override;

protected:
	// �v���C�� Player
	std::unique_ptr<Player> m_player;
	// �G�l�~�[ Enemy
	std::unique_ptr<Enemy> m_enemy;
};

#endif	// MYGAME
