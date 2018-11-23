#include"MouseEvent.h"


MouseEvent::MouseEvent(): type(EventType::Invalid), x(x), y(y)
{

}

MouseEvent::~MouseEvent()
{

}

MouseEvent::MouseEvent(const EventType type, const int x, const int y):type(), x(x), y(y)
{
	
}


bool MouseEvent::IsValide() const
{
	return this->type != EventType::Invalid;
}

MouseEvent::EventType MouseEvent::GetType() const
{
	return this->type;
}


MousePoint MouseEvent::GetPos() const
{
	return { this->x, this->y };
}

int MouseEvent::GetPosY() const
{
	return this->y;
}

int MouseEvent::GetPosX() const
{
	return this->x;
}

