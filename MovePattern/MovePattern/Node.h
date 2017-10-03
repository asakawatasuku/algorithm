#pragma once
#include <d3d11_1.h>
#include <memory>

class Node {
public:
	int x, z, cost; // cost�͂��̃m�[�h�ɂ���܂ł̍ŒZ�p�X��ł̗ݐϘa(f'(n))
	std::shared_ptr<Node> parent;
	Node(int x_, int z_, int cost_) 
	{
		x = x_; z = z_; cost = cost_;
	};
};