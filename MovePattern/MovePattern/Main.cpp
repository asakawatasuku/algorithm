// DirectX Game Framework 0.96
// 2017/05/05�@Added Japanese comment
// 2017/05/08  Added Graphics singleton class
// 2017/05/13  Added Window class
// 2017/05/20  Functioning WinMain function
// 2017/05/25  Change global Game object to local Game object
// 2017/05/29  Create Window object inside Game object
// 2017/07/01  Add MyGame class derrived from Game class
// 2017/07/11  Modify initializing order of objects

#include "Window.h"
#include "MyGame.h"

using namespace DirectX;

// �G���g���|�C���g Entry point
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    if (!XMVerifyCPUSupport())
        return 1;
	// COM���C�u����������������
    if (FAILED(CoInitializeEx(nullptr, COINITBASE_MULTITHREADED)))
        return 1;

	// �E�B���h�E��
	int width = 800;
	// �E�B���h�E��
	int height = 600;
	// MyGame�I�u�W�F�N�g�𐶐�����
	MyGame myGame(width, height);
	// �Q�[�������s����
	MSG msg = myGame.Run();

	// COM���C�u�����̏I������������
    CoUninitialize();
    return (int) msg.wParam;
}
