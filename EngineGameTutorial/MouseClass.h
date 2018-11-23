#pragma once
#include"MouseEvent.h"
#include<iostream>
#include<queue>


class MouseClass
{
public:
	MouseClass();
	~MouseClass();

	void OnLeftPressed(int x, int y);
	void OnLeftRelease(int x, int y);

	void OnRightPressed(int x, int y);
	void OnRightRelease(int x, int y);
	
	void OnMiddletPressed(int x, int y);
	void OnMiddleRelease(int x, int y);
	
	void OnWheelUp(int x, int y);
	void OnWheelDown(int x, int y);
	
	void OnMouseMove(int x, int y);

	void OnMouseMoveRaw(int x, int y);


	bool IsLeftDown();
	bool IsMiddleDown();
	bool IsRightDown();


	int GetPosX();
	int GetPosY();
	MousePoint GetPos();

	bool EventBufferIsEmpty();
	MouseEvent ReadEvent();


private:
	std::queue<MouseEvent>eventBuffer;
	bool leftIsDown = false;
	bool rightIsDown = false;
	bool mbuttonDown = false;
	
	int x = 0;
	int y = 0;

};

