#include "Pursuit.h"

using namespace std;

//---------------------------------------
// コンストラクタ
//---------------------------------------
Pursuit::Pursuit() {

}

//---------------------------------------
// デストラクタ
//---------------------------------------
Pursuit::~Pursuit() {

}

//---------------------------------------
// 初期設定
//---------------------------------------
void Pursuit::Initialize() {

}

//---------------------------------------
// 処理
//---------------------------------------
void Pursuit::Update() {
	m_move = m_P1 - m_P2;
	m_go = m_move *1.0;
}