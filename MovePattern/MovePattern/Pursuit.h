#include <iostream>

class Pursuit
{
public:
	Pursuit();
	~Pursuit();

private:
	float m_P1;			// プレイヤー座標
	float m_P2;			// エネミー座標
	float m_move;		// 2点間の距離
	float m_go;			// 追跡移動量

protected:
	void Initialize();
	void Update();
	void Drow();

};

