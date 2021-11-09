#pragma once

#include <DxLib.h>
#include "singleton.hpp"

class Input : public Singleton<Input>
{
public:
	enum
	{
		BUTTON_UP, BUTTON_DOWN, BUTTON_RIGHT, BUTTON_LEFT,
		BUTTON_TRIG1, BUTTON_TRIG2, BUTTON_TRIG3, BUTTON_TRIG4, BUTTON_TRIG5,
		BUTTON_TRIG6, BUTTON_TRIG7, BUTTON_TRIG8, BUTTON_TRIG9, BUTTON_TRIG10,
		MOUSE_LEFT, MOUSE_RIGHT, MOUSE_CENTER
	};

	void Update()
	{
		// Check inputs 'press'
		input_state_ = DxLib::GetJoypadInputState(DX_INPUT_KEY_PAD1);
		if (input_state_ & PAD_INPUT_UP) ++input_up_; else input_up_ = 0;
		if (input_state_ & PAD_INPUT_DOWN) ++input_down_; else input_down_ = 0;
		if (input_state_ & PAD_INPUT_RIGHT) ++input_right_; else input_right_ = 0;
		if (input_state_ & PAD_INPUT_LEFT) ++input_left_; else input_left_ = 0;
		if (input_state_ & PAD_INPUT_1) ++input_trig_[0]; else input_trig_[0] = 0;
		if (input_state_ & PAD_INPUT_2) ++input_trig_[1]; else input_trig_[1] = 0;
		if (input_state_ & PAD_INPUT_3) ++input_trig_[2]; else input_trig_[2] = 0;
		if (input_state_ & PAD_INPUT_4) ++input_trig_[3]; else input_trig_[3] = 0;
		if (input_state_ & PAD_INPUT_5) ++input_trig_[4]; else input_trig_[4] = 0;
		if (input_state_ & PAD_INPUT_6) ++input_trig_[5]; else input_trig_[5] = 0;
		if (input_state_ & PAD_INPUT_7) ++input_trig_[6]; else input_trig_[6] = 0;
		if (input_state_ & PAD_INPUT_8) ++input_trig_[7]; else input_trig_[7] = 0;
		if (input_state_ & PAD_INPUT_9) ++input_trig_[8]; else input_trig_[8] = 0;
		if (input_state_ & PAD_INPUT_10) ++input_trig_[9]; else input_trig_[9] = 0;

		if (DxLib::GetMouseInput() & MOUSE_INPUT_LEFT) ++mouse_left_; else mouse_left_ = 0;
		if (DxLib::GetMouseInput() & MOUSE_INPUT_RIGHT) ++mouse_right_; else mouse_right_ = 0;
		if (DxLib::GetMouseInput() & MOUSE_INPUT_MIDDLE) ++mouse_center_; else mouse_center_ = 0;

		// Check inputs 'push' and 'up'
		input_up_pushed_ = input_down_pushed_ = input_right_pushed_ = input_left_pushed_ = 0;
		input_up_upped_ = input_down_upped_ = input_right_upped_ = input_left_upped_ = 0;

		for (int i = 0; i < 10; ++i)
		{
			input_trig_pushed_[i] = 0;
			input_trig_upped_[i] = 0;
		}

		if (input_up_ > 0)
		{
			if (!input_up_flag_)
			{
				input_up_pushed_ = 1;
			}
			input_up_flag_ = 1;
		}
		else
		{
			if (input_up_flag_)
			{
				input_up_upped_ = 1;
			}
			input_up_flag_ = 0;
		}

		if (input_down_ > 0)
		{
			if (!input_down_flag_)
			{
				input_down_pushed_ = 1;
			}
			input_down_flag_ = 1;
		}
		else
		{
			if (input_down_flag_)
			{
				input_down_upped_ = 1;
			}
			input_down_flag_ = 0;
		}

		if (input_right_ > 0)
		{
			if (!input_right_flag_)
			{
				input_right_pushed_ = 1;
			}
			input_right_flag_ = 1;
		}
		else
		{
			if (input_right_flag_)
			{
				input_right_upped_ = 1;
			}
			input_right_flag_ = 0;
		}

		if (input_left_ > 0)
		{
			if (!input_left_flag_)
			{
				input_left_pushed_ = 1;
			}
			input_left_flag_ = 1;
		}
		else
		{
			if (input_left_flag_)
			{
				input_left_upped_ = 1;
			}
			input_left_flag_ = 0;
		}

		for (int i = 0; i < 10; ++i)
		{
			if (input_trig_[i] > 0)
			{
				if (!input_trig_flag_[i])
				{
					input_trig_pushed_[i] = 1;
				}
				input_trig_flag_[i] = 1;
			}
			else
			{
				if (input_trig_flag_[i])
				{
					input_trig_upped_[i] = 1;
				}
				input_trig_flag_[i] = 0;
			}
		}

		mouse_left_pushed_ = mouse_right_pushed_ = mouse_center_pushed_ = 0;
		mouse_left_upped_ = mouse_right_upped_ = mouse_center_upped_ = 0;

		if (mouse_left_ > 0)
		{
			if (!mouse_left_flag_)
			{
				mouse_left_pushed_ = 1;
			}
			mouse_left_flag_ = 1;
		}
		else
		{
			if (mouse_left_flag_)
			{
				mouse_left_upped_ = 1;
			}
			mouse_left_flag_ = 0;
		}

		if (mouse_right_ > 0)
		{
			if (!mouse_right_flag_)
			{
				mouse_right_pushed_ = 1;
			}
			mouse_right_flag_ = 1;
		}
		else
		{
			if (mouse_right_flag_)
			{
				mouse_right_upped_ = 1;
			}
			mouse_right_flag_ = 0;
		}

		if (mouse_center_ > 0)
		{
			if (!mouse_center_flag_)
			{
				mouse_center_pushed_ = 1;
			}
			mouse_center_flag_ = 1;
		}
		else
		{
			if (mouse_center_flag_)
			{
				mouse_center_upped_ = 1;
			}
			mouse_center_flag_ = 0;
		}

		DxLib::GetMousePoint(&mouse_x_, &mouse_y_);
	}

	int GetJoyPressCount(int button) const
	{
		switch (button)
		{
		case BUTTON_UP: return input_up_;
		case BUTTON_DOWN: return input_down_;
		case BUTTON_RIGHT: return input_right_;
		case BUTTON_LEFT: return input_left_;
		case BUTTON_TRIG1: return input_trig_[0];
		case BUTTON_TRIG2: return input_trig_[1];
		case BUTTON_TRIG3: return input_trig_[2];
		case BUTTON_TRIG4: return input_trig_[3];
		case BUTTON_TRIG5: return input_trig_[4];
		case BUTTON_TRIG6: return input_trig_[5];
		case BUTTON_TRIG7: return input_trig_[6];
		case BUTTON_TRIG8: return input_trig_[7];
		case BUTTON_TRIG9: return input_trig_[8];
		case BUTTON_TRIG10: return input_trig_[9];
		default: return 0;
		}
	}

	bool IsJoyPressed(int button) const
	{
		switch (button)
		{
		case BUTTON_UP: return input_up_ > 0;
		case BUTTON_DOWN: return input_down_ > 0;
		case BUTTON_RIGHT: return input_right_ > 0;
		case BUTTON_LEFT: return input_left_ > 0;
		case BUTTON_TRIG1: return input_trig_[0] > 0;
		case BUTTON_TRIG2: return input_trig_[1] > 0;
		case BUTTON_TRIG3: return input_trig_[2] > 0;
		case BUTTON_TRIG4: return input_trig_[3] > 0;
		case BUTTON_TRIG5: return input_trig_[4] > 0;
		case BUTTON_TRIG6: return input_trig_[5] > 0;
		case BUTTON_TRIG7: return input_trig_[6] > 0;
		case BUTTON_TRIG8: return input_trig_[7] > 0;
		case BUTTON_TRIG9: return input_trig_[8] > 0;
		case BUTTON_TRIG10: return input_trig_[9] > 0;
		default: return false;
		}
	}

	bool IsJoyPushed(int button) const
	{
		switch (button)
		{
		case BUTTON_UP: return input_up_pushed_ == 1;
		case BUTTON_DOWN: return input_down_pushed_ == 1;
		case BUTTON_RIGHT: return input_right_pushed_ == 1;
		case BUTTON_LEFT: return input_left_pushed_ == 1;
		case BUTTON_TRIG1: return input_trig_pushed_[0] == 1;
		case BUTTON_TRIG2: return input_trig_pushed_[1] == 1;
		case BUTTON_TRIG3: return input_trig_pushed_[2] == 1;
		case BUTTON_TRIG4: return input_trig_pushed_[3] == 1;
		case BUTTON_TRIG5: return input_trig_pushed_[4] == 1;
		case BUTTON_TRIG6: return input_trig_pushed_[5] == 1;
		case BUTTON_TRIG7: return input_trig_pushed_[6] == 1;
		case BUTTON_TRIG8: return input_trig_pushed_[7] == 1;
		case BUTTON_TRIG9: return input_trig_pushed_[8] == 1;
		case BUTTON_TRIG10: return input_trig_pushed_[9] == 1;
		default: return false;
		}
	}

	bool IsJoyUpped(int button) const
	{
		switch (button)
		{
		case BUTTON_UP: return input_up_upped_ == 1;
		case BUTTON_DOWN: return input_down_upped_ == 1;
		case BUTTON_RIGHT: return input_right_upped_ == 1;
		case BUTTON_LEFT: return input_left_upped_ == 1;
		case BUTTON_TRIG1: return input_trig_upped_[0] == 1;
		case BUTTON_TRIG2: return input_trig_upped_[1] == 1;
		case BUTTON_TRIG3: return input_trig_upped_[2] == 1;
		case BUTTON_TRIG4: return input_trig_upped_[3] == 1;
		case BUTTON_TRIG5: return input_trig_upped_[4] == 1;
		case BUTTON_TRIG6: return input_trig_upped_[5] == 1;
		case BUTTON_TRIG7: return input_trig_upped_[6] == 1;
		case BUTTON_TRIG8: return input_trig_upped_[7] == 1;
		case BUTTON_TRIG9: return input_trig_upped_[8] == 1;
		case BUTTON_TRIG10: return input_trig_upped_[9] == 1;
		default: return false;
		}
	}

	int GetMousePressCount(int button) const
	{
		switch (button)
		{
		case MOUSE_LEFT: return mouse_left_;
		case MOUSE_RIGHT: return mouse_right_;
		case MOUSE_CENTER: return mouse_center_;
		default: return 0;
		}
	}

	bool IsMousePressed(int button) const
	{
		switch (button)
		{
		case MOUSE_LEFT: return mouse_left_ > 0;
		case MOUSE_RIGHT: return mouse_right_ > 0;
		case MOUSE_CENTER: return mouse_center_ > 0;
		default: return false;
		}
	}

	bool IsMousePushed(int button) const
	{
		switch (button)
		{
		case MOUSE_LEFT: return mouse_left_pushed_ == 1;
		case MOUSE_RIGHT: return mouse_right_pushed_ == 1;
		case MOUSE_CENTER: return mouse_center_pushed_ == 1;
		default: return false;
		}
	}

	bool IsMouseUpped(int button) const
	{
		switch (button)
		{
		case MOUSE_LEFT: return mouse_left_upped_ == 1;
		case MOUSE_RIGHT: return mouse_right_upped_ == 1;
		case MOUSE_CENTER: return mouse_center_upped_ == 1;
		default: return false;
		}
	}

	int GetMouseX() const
	{
		return mouse_x_;
	}

	int GetMouseY() const
	{
		return mouse_y_;
	}

private:
	int input_state_;
	int input_up_, input_up_pushed_, input_up_upped_, input_up_flag_;
	int input_down_, input_down_pushed_, input_down_upped_, input_down_flag_;
	int input_right_, input_right_pushed_, input_right_upped_, input_right_flag_;
	int input_left_, input_left_pushed_, input_left_upped_, input_left_flag_;
	int input_trig_[10], input_trig_pushed_[10], input_trig_upped_[10], input_trig_flag_[10];
	int mouse_left_, mouse_left_pushed_, mouse_left_upped_, mouse_left_flag_;
	int mouse_right_, mouse_right_pushed_, mouse_right_upped_, mouse_right_flag_;
	int mouse_center_, mouse_center_pushed_, mouse_center_upped_, mouse_center_flag_;
	int mouse_x_, mouse_y_;

	Input()
		: input_state_(0)
		, input_up_(0), input_up_pushed_(0), input_up_upped_(0), input_up_flag_(0)
		, input_down_(0), input_down_pushed_(0), input_down_upped_(0), input_down_flag_(0)
		, input_right_(0), input_right_pushed_(0), input_right_upped_(0), input_right_flag_(0)
		, input_left_(0), input_left_pushed_(0), input_left_upped_(0), input_left_flag_(0)
		, mouse_left_(0), mouse_left_pushed_(0), mouse_left_upped_(0), mouse_left_flag_(0)
		, mouse_right_(0), mouse_right_pushed_(0), mouse_right_upped_(0), mouse_right_flag_(0)
		, mouse_center_(0), mouse_center_pushed_(0), mouse_center_upped_(0), mouse_center_flag_(0)
		, mouse_x_(0), mouse_y_(0)
	{
		for (int i = 0; i < 10; ++i)
		{
			input_trig_[i] = 0;
			input_trig_pushed_[i] = 0;
			input_trig_upped_[i] = 0;
			input_trig_flag_[i] = 0;
		}
	}
	friend Singleton<Input>;
};