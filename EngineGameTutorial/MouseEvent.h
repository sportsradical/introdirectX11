#pragma once





struct MousePoint
{
	int x;
	int y;
};



class MouseEvent
{
public:
	enum EventType
	{
		LPress,
		LRelease,
		RPress,
		RRelease,
		MPress,
		MRelease,
		WheelUp,
		WheelDown,
		Move,
		RAW_MOVE,
		Invalid
	};



public:
	MouseEvent();
	MouseEvent(const EventType type, const int x, const int y);
	~MouseEvent();

	bool IsValide()const;
	EventType GetType() const;
	MousePoint GetPos() const;
	int GetPosY() const;
	int GetPosX() const;
protected:
	EventType type;
	int x;
	int y;



private:




};

