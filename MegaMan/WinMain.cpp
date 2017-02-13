﻿#ifndef _WinMain_H_
#define _WinMain_H_

#include <Windows.h>
#include "../SFramework/SFramework.h"
#include "../SFramework/GameTime.h"
#include "../SFramework/Scene.h"
#include "../SFramework/Layer.h"
#include "../SFramework/Sprite.h"
#include "../SFramework/Director.h"
#include "../SFramework/Texture.h"
#include "../SFramework/SpriteSpec.h"
#include "../SFramework/ViewPort.h"

#define APP_CLASS L"SampleWindow"
#define MAIN_WINDOW_TITLE L"Mega Man"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

USING_S_FRAMEWORK;

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

HWND hwnd;

bool initializeWindow(HINSTANCE hInstance){

	WNDCLASSEX wndClass = { 0 };

	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = WndProc;

	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = APP_CLASS;

	if (!RegisterClassEx(&wndClass))
		return -1;

	hwnd = CreateWindow(APP_CLASS,
		MAIN_WINDOW_TITLE,
		WS_OVERLAPPEDWINDOW,
		//WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL);

	if (!hwnd)
		return FALSE;

	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);
	return TRUE;
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPWSTR cmdLine, int cmdShow)
{
	UNREFERENCED_PARAMETER(prevInstance);
	UNREFERENCED_PARAMETER(cmdLine);

	if (!initializeWindow(hInstance))
		return FALSE;

	if (!SFramework::getInstance()->init(hwnd))
		return FALSE;

	GameTime::getInstance();

	// thiết lập ma trận transform
	//ViewPort::getInstance()->setPosition(FPOINT(20, 20));
	// load hình
	Texture* texture = new Texture();
	texture->init("Resource/texture.png", "Resource/texture.xml");


	Scene* scene = new Scene();
	scene->setHeight(SCREEN_HEIGHT *4);
	scene->setWidth(SCREEN_WIDTH * 4);
	scene->setPostion(FPOINT((float)SCREEN_WIDTH *2, (float)SCREEN_HEIGHT *2));

	Director::getInstance()->setScene(scene);	

	Layer* layer = new Layer();
	layer->setHeight(SCREEN_HEIGHT*2);
	layer->setWidth(SCREEN_WIDTH*2);
	FPOINT p;
	p.x = SCREEN_WIDTH * 3;
	p.y = SCREEN_HEIGHT * 2;
	//scene->setPostion(FPOINT((float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2));

	layer->setPostion(p);
	scene->addChild(layer);
	
	p.x = p.x - 200;
	p.y = p.y - 200;
	ViewPort::getInstance()->setPosition(p);

	Sprite* sprite = new Sprite(texture, texture->getSpriteSpecById(19));
	p.x = SCREEN_WIDTH + 100;
	p.y = 100;
	sprite->setPostion(p);

	
	layer->addChild(sprite);

	SFramework::getInstance()->loop();

	//GameRelease();

	return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}

	return 0;
}
#endif // !_WinMain_H_