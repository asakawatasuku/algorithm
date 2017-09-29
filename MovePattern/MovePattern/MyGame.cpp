#include "MyGame.h"

using namespace Microsoft;
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

// �R���X�g���N�^ Constructor
MyGame::MyGame(int width, int height) : Game(width, height){
}

// MyGame�I�u�W�F�N�g���������� Initialize MyGame object
void MyGame::Initialize() {
	// ��{�N���X��Initialize���Ăяo��
	Game::Initialize();

	Base::StaticInitialize(camera);

	m_ground = make_unique<Ground>();
	m_ground->Initialize(L"ground");

	// Player�I�u�W�F�N�g�𐶐����� Create Player object
	m_player = make_unique<Player>();
	// Player�I�u�W�F�N�g������������ Initialize Player object
	m_player->Initialize(L"player");

	// Enemy�I�u�W�F�N�g�𐶐����� Create Enemy object
	m_enemy = make_unique<Enemy>();
	m_enemy->SetTarget(m_player.get());
	// Enemy�I�u�W�F�N�g������������ Initialize Enemy object
	m_enemy->Initialize(L"enemy");

	m_keyboard = make_unique<KeyboardUtil>();
	m_player->SetKeyboard(m_keyboard.get());
}

// �Q�[�����X�V���� Update game
void MyGame::Update(const DX::StepTimer& timer) {
	float elapsedTime = float(timer.GetElapsedSeconds());

	// TODO: �X�V������ǉ����� Add your update process here

	Game::Update(timer);

	m_keyboard->Update();

	// �v���C�����X�V���� Update Player object
	m_player->Update();
	// �G�l�~�[���X�V���� Update Enemy object
	m_enemy->Update();
}

// �V�[����`�悷�� Draws the scene
void MyGame::Render(const DX::StepTimer& timer) {
	// �ŏ��̍X�V�̑O�͉����`�悵�Ȃ��悤�ɂ��� Don't try to render anything before the first Update.
	if (timer.GetFrameCount() == 0) {
		return;
	}

	// TODO: �����_�����O�R�[�h��ǉ����� Add your rendering code here
	// ��ʂ��N���A���� Clear Screen
	Clear();

	Game::Render(timer);

	// �`����n�߂� Begin rendering
	spriteBatch->Begin(SpriteSortMode_Deferred, commonStates->NonPremultiplied());

	// �n�ʂ�`�悷��
	m_ground->Render();
	// Player�I�u�W�F�N�g��`�悷�� Render Player object
	m_player->Render();
	// Enemy�I�u�W�F�N�g��`�悷�� Render Enemy object
	m_enemy->Render();

	// �`����I���� Finish rendering
	spriteBatch->End();
	// �o�b�N�o�b�t�@���X�N���[���ɑ��� Presents the back buffer contents to the screen
	Present();
}

// �I�������������Ȃ� Finalize Game
void MyGame::Finalize() {
	m_enemy->Finalize();
	// Enemy�I�u�W�F�N�g�����Z�b�g����
	m_enemy.reset();

	m_player->Finalize();
	// Player�I�u�W�F�N�g�����Z�b�g����
	m_player.reset();

	// ��{�N���X��Finalize���Ăяo��
	Game::Finalize();
}
