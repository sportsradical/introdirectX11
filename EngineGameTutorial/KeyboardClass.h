#pragma once
#include"KeyboardEvent.h"
#include<queue>




class CKeyboardClass
{
public:
	CKeyboardClass();
	virtual ~CKeyboardClass();
	void Initialize();
	bool KeyIsPressed(const unsigned char keycode);
	bool KeyBufferIsEmpty();
	bool CharBufferIsEmpty();
	unsigned char ReadChar();

	void OnKeyPress(const unsigned char key);
	void OnKeyRelease(const unsigned char key);
	void OnChar(const unsigned char key);
	void EnableAutoRepeatKeys();
	void DisableAutoRepeatKeys();
	void EnableAutoRepeatChars();
	void DisableAutoRepeatChars();

	bool IsKeysAutoRepeat();
	bool IsCharsAutoRepeat();

	KeyboardEvent ReadKey();




protected:
	bool autoRepeatsKeys;
	bool autoRepeatsChars;
	bool keyStates[256];
	std::queue<KeyboardEvent>keyBuffer;
	std::queue<unsigned char>charBuffer;
};

