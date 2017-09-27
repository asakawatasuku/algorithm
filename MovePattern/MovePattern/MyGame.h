#pragma once

#ifndef MYGAME 
#define MYGAME

#include "Game.h"
#include "Player.h"
#include "Enemy.h"


class MyGame : public Game {
public:
	// コンストラクタ Constructor
	MyGame(int width, int height);
	// ゲームオブジェクトを初期する Initialize game object
	void Initialize() override;
	// ゲームを更新する Update game
	void Update(const DX::StepTimer& timer) override;
	// ゲームシーンを描画する Draws the scene
	void Render(const DX::StepTimer& timer) override;
	// 終了処理をおこなう Finalize game
	void Finalize() override;

protected:
	// プレイヤ Player
	std::unique_ptr<Player> m_player;
	// エネミー Enemy
	std::unique_ptr<Enemy> m_enemy;
};

#endif	// MYGAME
