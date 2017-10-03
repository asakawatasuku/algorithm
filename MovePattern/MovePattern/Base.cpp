#include "Base.h"
#include "Graphics.h"

using namespace DirectX::SimpleMath;

std::unique_ptr<DirectX::CommonStates> Base::m_states = nullptr;
std::shared_ptr<Camera> Base::m_camera = nullptr;


void Base::StaticInitialize(std::shared_ptr<Camera> camera)
{
	m_states = make_unique<DirectX::CommonStates>(Graphics::Get().Device().Get());
	m_camera = camera;
}


void Base::Initialize(const std::wstring& file_name)
{
	LoadModel(file_name);

	m_scale = Vector3(1.0f);
}


void Base::Update()
{
	Matrix scale_mat = Matrix::CreateScale(m_scale);

	Matrix rot_mat_z = Matrix::CreateRotationZ(m_rot.z);
	Matrix rot_mat_x = Matrix::CreateRotationX(m_rot.x);
	Matrix rot_mat_y = Matrix::CreateRotationY(m_rot.y);
	Matrix rot_mat = rot_mat_z * rot_mat_x * rot_mat_y;

	m_pos += m_speed;
	Matrix trans_mat = Matrix::CreateTranslation(m_pos);

	m_world = scale_mat * rot_mat * trans_mat;
}


void Base::Render()
{
	m_model->Draw(Graphics::Get().Context().Get(), *m_states, m_world, m_camera->GetView(), m_camera->GetProjection());
}


void Base::LoadModel(const std::wstring& file_name)
{
	std::wstring path = L"Resources\\" + file_name + L".cmo";
	m_model = DirectX::Model::CreateFromCMO(Graphics::Get().Device().Get(), path.c_str(), *(Graphics::Get().EffectFactory()));
}
