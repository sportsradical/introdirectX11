#pragma once


class KeyboardEvent
{
public:
	enum EventType
	{
		Press,
		Release,
		Invalid
	};


public:

	KeyboardEvent();
	KeyboardEvent(const EventType type, const unsigned char key);
	~KeyboardEvent();
	
	bool IsPress()const;
	bool IsRelease()const;
	bool IsInvalid()const;

	unsigned char GetKeyCode()const;

protected:
	EventType type;
	unsigned char key;

};

