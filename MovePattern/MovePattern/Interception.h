


class Interception
{
public:
	Interception();
	~Interception();
private:
	float m_Vr;			// ���Α��x
	float m_Sr;			// ���΋���
	float m_Tc;			// �ڋߎ���

	float m_Sp;			// �v���C���[�̌��ݍ��W
	float m_Vp;			// �v���C���[�̈ړ��x�N�g��
	float m_Se;			// �G�̌��ݍ��W
	float m_Ve;			// �G�̈ړ��x�N�g��

	float m_point;		// �}���|�C���g

protected:
	void Initialize();
	void Update();
};