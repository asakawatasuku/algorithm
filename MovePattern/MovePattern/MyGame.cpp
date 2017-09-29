#include "MyGame.h"

using namespace Microsoft;
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

// コンストラクタ Constructor
MyGame::MyGame(int width, int height) : Game(width, height){
}

// MyGameオブジェクトを初期する Initialize MyGame object
void MyGame::Initialize() {
	// 基本クラスのInitializeを呼び出す
	Game::Initialize();

	Base::StaticInitialize(camera);

	m_ground = make_unique<Ground>();
	m_ground->Initialize(L"ground");

	// Playerオブジェクトを生成する Create Player object
	m_player = make_unique<Player>();
	// Playerオブジェクトを初期化する Initialize Player object
	m_player->Initialize(L"player");

	// Enemyオブジェクトを生成する Create Enemy object
	m_enemy = make_unique<Enemy>();
	m_enemy->SetTarget(m_player.get());
	// Enemyオブジェクトを初期化する Initialize Enemy object
	m_enemy->Initialize(L"enemy");

	m_keyboard = make_unique<KeyboardUtil>();
	m_player->SetKeyboard(m_keyboard.get());
}

// ゲームを更新する Update game
void MyGame::Update(const DX::StepTimer& timer) {
	float elapsedTime = float(timer.GetElapsedSeconds());

	// TODO: 更新処理を追加する Add your update process here

	Game::Update(timer);

	m_keyboard->Update();

	// プレイヤを更新する Update Player object
	m_player->Update();
	// エネミーを更新する Update Enemy object
	m_enemy->Update();
}

// シーンを描画する Draws the scene
void MyGame::Render(const DX::StepTimer& timer) {
	// 最初の更新の前は何も描画しないようにする Don't try to render anything before the first Update.
	if (timer.GetFrameCount() == 0) {
		return;
	}

	// TODO: レンダリングコードを追加する Add your rendering code here
	// 画面をクリアする Clear Screen
	Clear();

	Game::Render(timer);

	// 描画を始める Begin rendering
	spriteBatch->Begin(SpriteSortMode_Deferred, commonStates->NonPremultiplied());

	// 地面を描画する
	m_ground->Render();
	// Playerオブジェクトを描画する Render Player object
	m_player->Render();
	// Enemyオブジェクトを描画する Render Enemy object
	m_enemy->Render();

	// 描画を終える Finish rendering
	spriteBatch->End();
	// バックバッファをスクリーンに送る Presents the back buffer contents to the screen
	Present();
}

// 終了処理をおこなう Finalize Game
void MyGame::Finalize() {
	m_enemy->Finalize();
	// Enemyオブジェクトをリセットする
	m_enemy.reset();

	m_player->Finalize();
	// Playerオブジェクトをリセットする
	m_player.reset();

	// 基本クラスのFinalizeを呼び出す
	Game::Finalize();
}
