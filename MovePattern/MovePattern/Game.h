// Game.h

#pragma once
#ifndef GAME
#define GAME

/*
#include <WinSDKVer.h>
#define _WIN32_WINNT 0x0600
#include <SDKDDKVer.h>
*/

// Use the C++ standard templated min/max
#define NOMINMAX

// DirectX apps don't need GDI
#define NODRAWTEXT
#define NOGDI
#define NOBITMAP

// Include <mcx.h> if you need this
#define NOMCX

// Include <winsvc.h> if you need this
#define NOSERVICE

// WinHelp is deprecated
#define NOHELP


#include <windows.h>
#include <iostream>
#include <string>
#include <iomanip>

#include <d3d11.h>
#include <SimpleMath.h>
#include <SpriteBatch.h>
#include <SpriteFont.h>
#include <Model.h>
#include <Keyboard.h>
#include <GeometricPrimitive.h>
#include <WICTextureLoader.h>
#include <algorithm>

#include "StepTimer.h"
#include "Camera.h"
#include "dx.h"
#include "Window.h"
#include "Graphics.h"

#include "Player.h"

class Window;

class Game {
public:
	// 基本ゲームループを実行する Run basic game loop
	MSG Run();

	// コンストラクタ Constructor
    Game(int width, int height);
    // ゲームに必要なオブジェクトを初期する Initialize game object
    virtual void Initialize();
	// ゲームを更新する Update game
	virtual void Update(DX::StepTimer const& timer);
	// 画面をクリアする Clear screen
	virtual void Clear();
	// シーンを描画する Render scene
	virtual void Render(DX::StepTimer const& timer);
	// バックバッファをスクリーンに送る
	virtual void Present();
	// 終了処理をおこなう Finalize game
	virtual void Finalize();

    // メッセージ Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowSizeChanged(int width, int height);

    // プロパティ Properties
    void GetDefaultSize(int& width, int& height) const;
	// FPSを描画する Draw FPS
	void DrawFPS();

private:
	// インスタンスハンドル
	HINSTANCE hInstance;
	// 実行時のウィンドウの大きさ
	int nCmdShow;
    // デバイスリソース Device resources
    HWND hWnd;
	// 出力幅 window width
    int width;
	// 出力高 window height
    int height;

	// ウィンドウ Window
	std::unique_ptr<Window> window;
	// グラフィックス Graphics
	std::unique_ptr<Graphics> graphics;
	// 機能レベル Feature level
    D3D_FEATURE_LEVEL featureLevel;

protected:
    // ループタイマーを描画する Rendering loop timer
    DX::StepTimer timer;

	// スプライトバッチ SpriteBatch
	std::unique_ptr<DirectX::SpriteBatch> spriteBatch;
	// フォント Font
	std::unique_ptr<DirectX::SpriteFont> font;
	// エフェクトファクトリインターフェース IEffectFactory
	std::unique_ptr<DirectX::CommonStates> commonStates;

	std::shared_ptr<Camera> camera;
};

#endif	// GAME
