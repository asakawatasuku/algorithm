#include <iostream>

class Pursuit
{
public:
	Pursuit();
	~Pursuit();

private:
	float m_P1;			// �v���C���[���W
	float m_P2;			// �G�l�~�[���W
	float m_move;		// 2�_�Ԃ̋���
	float m_go;			// �ǐՈړ���

protected:
	void Initialize();
	void Update();
	void Drow();

};

