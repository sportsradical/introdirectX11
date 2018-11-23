#include "MouseClass.h"

MouseClass::MouseClass()
{

}

MouseClass::~MouseClass()
{

}

void MouseClass::OnLeftPressed(int x, int y)
{
	this->leftIsDown = false;
	MouseEvent me(MouseEvent(MouseEvent::EventType::LPress, x, y));
	this->eventBuffer.push(me);
}

void MouseClass::OnLeftRelease(int x, int y)
{
	this->leftIsDown = false;
	this->eventBuffer.push(MouseEvent(MouseEvent::EventType::LRelease, x, y));
}


void MouseClass::OnRightPressed(int x, int y)
{
	this->rightIsDown = true;
	this->eventBuffer.push(MouseEvent(MouseEvent::EventType::RPress, x, y));
}


void MouseClass::OnRightRelease(int x, int y)

{
	this->rightIsDown = false;
	this->eventBuffer.push(MouseEvent(MouseEvent::EventType::RRelease, x, y));
}

void MouseClass::OnMiddletPressed(int x, int y)
{
	this->mbuttonDown = true;
	this->eventBuffer.push(MouseEvent(MouseEvent::EventType::MPress, x, y));
}

void MouseClass::OnMiddleRelease(int x, int y)
{
	this->mbuttonDown = false;
	this->eventBuffer.push(MouseEvent(MouseEvent::EventType::MRelease, x, y));
}

void MouseClass::OnWheelUp(int x, int y)
{
	this->eventBuffer.push(MouseEvent(MouseEvent::EventType::WheelUp, x, y));
}

void MouseClass::OnWheelDown(int x, int y)
{
	this->eventBuffer.push(MouseEvent(MouseEvent::EventType::WheelDown, x, y));
}

void MouseClass::OnMouseMove(int x, int y)
{
	this->x = x;
	this->y = y;

	this->eventBuffer.push(MouseEvent(MouseEvent::Move, x, y));
}

bool MouseClass::IsRightDown()
{
	return this->rightIsDown;
}

bool MouseClass::IsLeftDown()
{
	return this->leftIsDown;
}

bool MouseClass::IsMiddleDown()
{
	return this->mbuttonDown;
}

int MouseClass::GetPosX()
{
	return x;
}

int MouseClass::GetPosY()
{
	return y;
}

MousePoint MouseClass::GetPos()
{
	return { this->x, this->y };
}

bool MouseClass::EventBufferIsEmpty()
{
	return this->eventBuffer.empty();
}

MouseEvent MouseClass::ReadEvent()
{
	if (this->eventBuffer.empty())
	{
		return MouseEvent();
	}
	else
	{
		MouseEvent mouseEvent = this->eventBuffer.front();
		this->eventBuffer.pop();
		return mouseEvent;
	}
}

void  MouseClass::OnMouseMoveRaw(int x, int y)
{
	this->eventBuffer.push(MouseEvent(MouseEvent::EventType::RAW_MOVE, x, y));
}




