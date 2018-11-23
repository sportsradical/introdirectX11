#include "KeyboardClass.h"



CKeyboardClass::CKeyboardClass()
{
	for (int i = 0; i < 256; i++)
	{
		this->keyStates[i] = false; // initialized all key in off
	}
}


CKeyboardClass::~CKeyboardClass()
{
}

void CKeyboardClass::Initialize()
{
	
}

bool CKeyboardClass::KeyIsPressed(const unsigned char keycode)
{
	return this->keyStates[keycode];
}

bool CKeyboardClass::KeyBufferIsEmpty()
{
	return this->keyBuffer.empty();
}

bool CKeyboardClass::CharBufferIsEmpty()
{
	return this->charBuffer.empty();
}

KeyboardEvent CKeyboardClass::ReadKey()
{
	if (this->keyBuffer.empty()) // if no keys to be read?
	{
		return KeyboardEvent(); // return empety keyboard event
	}
	else
	{
		KeyboardEvent e = this->keyBuffer.front(); // get first keyboard event from queen
		this->keyBuffer.pop(); // remove first item from queen
		return e; // return keyboard event
	}
}

unsigned char CKeyboardClass::ReadChar()
{
	if (this->charBuffer.empty()) // if no keys to be read?
	{
		return 0u; // return empety keyboard event
	}
	else
	{
		unsigned char e = this->charBuffer.front(); // get first keyboard event from queen
		this->charBuffer.pop(); // remove first item from queen
		return e; // return keyboard event
	}
}

void CKeyboardClass::OnKeyPress(const unsigned char key)
{
	this->keyStates[key] = true;
	this->keyBuffer.push(KeyboardEvent(KeyboardEvent::EventType::Press, key));
}

void CKeyboardClass::OnKeyRelease(const unsigned char key)
{
	this->keyStates[key] = false;
	this->keyBuffer.push(KeyboardEvent(KeyboardEvent::EventType::Release, key));
}

void CKeyboardClass::OnChar(const unsigned char key)
{
	this->charBuffer.push(key);
}


void CKeyboardClass::EnableAutoRepeatKeys()
{
	this->autoRepeatsKeys = true;
}

void CKeyboardClass::DisableAutoRepeatKeys()
{
	this->autoRepeatsKeys = false;
}

void CKeyboardClass::EnableAutoRepeatChars()
{
	this->autoRepeatsChars = true;
}

void CKeyboardClass::DisableAutoRepeatChars()
{
	this->autoRepeatsChars = false;
}

bool CKeyboardClass::IsKeysAutoRepeat()
{
	return this->autoRepeatsKeys;
}

bool CKeyboardClass::IsCharsAutoRepeat()
{
	return this->autoRepeatsChars;
}


