#pragma once
#include <iostream>
#include <d3d11_1.h>
#include <vector>
#include <algorithm>
#include <memory>
#include <functional>
#include "Base.h"
#include "Node.h"

class A_Star
{
private:
	Base* m_object;
	Base* m_target;

	int m_start_pos_x;						// �X�^�[�g���Wx
	int m_start_pos_z;						// �X�^�[�g���Wz
	int m_goal_pos_x;						// �S�[�����Wx
	int m_goal_pos_z;						// �S�[�����Wz
	int **m_cost;							// �R�X�g
	int **m_heuristic;						// ����
	std::vector<std::shared_ptr<Node>> L1;	// ���X�g1
	std::vector<std::shared_ptr<Node>> L2;	// ���X�g2

public:
	A_Star(std::pair<int, int> start, std::pair<int, int> goal, int **cost_, int **heuristic_);
	// �������֐�
	void Initialize(Base* object, Base* target);
	// �X�V����
	void Update();
	// �I������
	void Finalize();
	// ��r�֐�
	bool Compare(const std::shared_ptr<Node>& a, const std::shared_ptr<Node>& b);
	// �S�[��
	bool is_goal_node(std::shared_ptr<Node> node);
	bool is_included_in(std::vector<std::shared_ptr<Node>> list, std::shared_ptr<Node> node);
	// �m�[�h�̎擾
	std::shared_ptr<Node> get_node(std::shared_ptr<Node> source_node, int target_x, int target_z);
	std::vector<std::shared_ptr<Node>> expand(std::shared_ptr<Node> node);
	// �T������
	void search();
	// ��߂菈��
	void back_track();
};
