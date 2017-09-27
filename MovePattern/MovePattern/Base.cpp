#include "Base.h"
#include "Graphics.h"


void Base::Render()
{
	m_model->Draw(Graphics::Get().Context().Get(), *m_states, m_world, m_camera->GetView(), m_camera->GetProjection());
}


void Base::LoadModel(const std::wstring& file_name)
{
	std::wstring path = L"Resources\\" + file_name + L".cmo";
	m_model = DirectX::Model::CreateFromCMO(Graphics::Get().Device().Get(), path.c_str(), *(Graphics::Get().EffectFactory()));
}
