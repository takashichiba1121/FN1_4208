#pragma once
#include "DxLib.h"
#include <array>
#include"Vector2.h"

class Input
{
private:
	inline static Input* instance_ = nullptr;
	std::array<char, 256> keys_ = { 0 };
	std::array<char, 256> oldkeys_ = { 0 };

	uint32_t mouseKeys_=0;
	uint32_t oldMouseKeys_=0;

	Vector2 mousePos_={0,0};

	float mouseWheel_ = 0;

	int PadKey = 0;

	int oldPadkey = 0;

	int padX = 0;

	int padY = 0;

	bool isUsePad_ = false;

private:
	Input() {}
	Input(const Input&) {}
	Input& operator=(const Input&) {}
	~Input() {}

public:
	enum class Key;
	enum class MouseKey;

	static void Initialize();
	static void Update();

	static bool GetKey(const Key& key);
	static bool GetKeyTrigger(const Key& key);
	static bool GetKeyRelease(const Key& key);

	static bool GetMouseKey(const MouseKey& key);
	static bool GetMouseKeyTrigger(const MouseKey& key);
	static bool GetMouseKeyRelease(const MouseKey& key);

	static Vector2 GetMousePos();

	static float GetMouseWheel();

	/// <summary>
	/// キーを押しているか
	/// </summary>
	static bool PushPadKey(uint16_t keyNumber);

	/// <summary>
	/// キーを押した瞬間
	/// </summary>
	static bool TriggerPadKey(uint16_t keyNumber);

	/// <summary>
	/// キーを離した瞬間
	/// </summary>
	static bool ReleasePadKey(uint16_t keyNumber);

	static uint32_t PadX();

	static uint32_t PadY();

	static bool GetIsUsePad();

	enum class Key
	{
		BACK = KEY_INPUT_BACK,
		TAB = KEY_INPUT_TAB,
		Return = KEY_INPUT_RETURN,
		Enter = KEY_INPUT_RETURN,
		LShift = KEY_INPUT_LSHIFT,
		RShift = KEY_INPUT_RSHIFT,
		LControl = KEY_INPUT_LCONTROL,
		RControl = KEY_INPUT_RCONTROL,
		Escape = KEY_INPUT_ESCAPE,
		Space = KEY_INPUT_SPACE,
		PGUP = KEY_INPUT_PGUP,
		PGDN = KEY_INPUT_PGDN,
		END = KEY_INPUT_END,
		HOME = KEY_INPUT_HOME,
		Left = KEY_INPUT_LEFT,
		Up = KEY_INPUT_UP,
		Right = KEY_INPUT_RIGHT,
		Down = KEY_INPUT_DOWN,
		INSERT = KEY_INPUT_INSERT,
		Delete = KEY_INPUT_DELETE,
		MINUS = KEY_INPUT_MINUS,
		YEN = KEY_INPUT_YEN,
		PREVTRACK = KEY_INPUT_PREVTRACK,
		PERIOD = KEY_INPUT_PERIOD,
		SLASH = KEY_INPUT_SLASH,
		LALT = KEY_INPUT_LALT,
		RALT = KEY_INPUT_RALT,
		SCROLL = KEY_INPUT_SCROLL,
		SEMICOLON = KEY_INPUT_SEMICOLON,
		COLON = KEY_INPUT_COLON,
		LBRACKET = KEY_INPUT_LBRACKET,
		RBRACKET = KEY_INPUT_RBRACKET,
		AT = KEY_INPUT_AT,
		BACKSLASH = KEY_INPUT_BACKSLASH,
		COMMA = KEY_INPUT_COMMA,
		KANJI = KEY_INPUT_KANJI,
		CONVERT = KEY_INPUT_CONVERT,
		NOCONVERT = KEY_INPUT_NOCONVERT,
		KANA = KEY_INPUT_KANA,
		APPS = KEY_INPUT_APPS,
		CAPSLOCK = KEY_INPUT_CAPSLOCK,
		SYSRQ = KEY_INPUT_SYSRQ,
		PAUSE = KEY_INPUT_PAUSE,
		LWIN = KEY_INPUT_LWIN,
		RWIN = KEY_INPUT_RWIN,
		NUMLOCK = KEY_INPUT_NUMLOCK,
		NUMPAD0 = KEY_INPUT_NUMPAD0,
		NUMPAD1 = KEY_INPUT_NUMPAD1,
		NUMPAD2 = KEY_INPUT_NUMPAD2,
		NUMPAD3 = KEY_INPUT_NUMPAD3,
		NUMPAD4 = KEY_INPUT_NUMPAD4,
		NUMPAD5 = KEY_INPUT_NUMPAD5,
		NUMPAD6 = KEY_INPUT_NUMPAD6,
		NUMPAD7 = KEY_INPUT_NUMPAD7,
		NUMPAD8 = KEY_INPUT_NUMPAD8,
		NUMPAD9 = KEY_INPUT_NUMPAD9,
		MULTIPLY = KEY_INPUT_MULTIPLY,
		ADD = KEY_INPUT_ADD,
		SUBTRACT = KEY_INPUT_SUBTRACT,
		DECIMAL = KEY_INPUT_DECIMAL,
		DIVIDE = KEY_INPUT_DIVIDE,
		NUMPADENTER = KEY_INPUT_NUMPADENTER,
		F1 = KEY_INPUT_F1,
		F2 = KEY_INPUT_F2,
		F3 = KEY_INPUT_F3,
		F4 = KEY_INPUT_F4,
		F5 = KEY_INPUT_F5,
		F6 = KEY_INPUT_F6,
		F7 = KEY_INPUT_F7,
		F8 = KEY_INPUT_F8,
		F9 = KEY_INPUT_F9,
		F10 = KEY_INPUT_F10,
		F11 = KEY_INPUT_F11,
		F12 = KEY_INPUT_F12,
		A = KEY_INPUT_A,
		B = KEY_INPUT_B,
		C = KEY_INPUT_C,
		D = KEY_INPUT_D,
		E = KEY_INPUT_E,
		F = KEY_INPUT_F,
		G = KEY_INPUT_G,
		H = KEY_INPUT_H,
		I = KEY_INPUT_I,
		J = KEY_INPUT_J,
		K = KEY_INPUT_K,
		L = KEY_INPUT_L,
		M = KEY_INPUT_M,
		N = KEY_INPUT_N,
		O = KEY_INPUT_O,
		P = KEY_INPUT_P,
		Q = KEY_INPUT_Q,
		R = KEY_INPUT_R,
		S = KEY_INPUT_S,
		T = KEY_INPUT_T,
		U = KEY_INPUT_U,
		V = KEY_INPUT_V,
		W = KEY_INPUT_W,
		X = KEY_INPUT_X,
		Y = KEY_INPUT_Y,
		Z = KEY_INPUT_Z,
		Num0 = KEY_INPUT_0,
		Num1 = KEY_INPUT_1,
		Num2 = KEY_INPUT_2,
		Num3 = KEY_INPUT_3,
		Num4 = KEY_INPUT_4,
		Num5 = KEY_INPUT_5,
		Num6 = KEY_INPUT_6,
		Num7 = KEY_INPUT_7,
		Num8 = KEY_INPUT_8,
		Num9 = KEY_INPUT_9,
	};

	enum class MouseKey
	{
		LEFT=MOUSE_INPUT_LEFT,
		RIGHT=MOUSE_INPUT_RIGHT,
		MIDDLE=MOUSE_INPUT_MIDDLE,
	};
};