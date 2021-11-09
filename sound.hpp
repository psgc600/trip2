#pragma once

#include <DxLib.h>
#include <memory>

class sound_handle
{
public:
	explicit sound_handle(const TCHAR* path)
		: handle_(DxLib::LoadSoundMem(path))
	{
	}

	~sound_handle()
	{
		DeleteSoundMem(handle_);
	}

	int handle() const
	{
		return handle_;
	}

private:
	int handle_;
};

typedef std::shared_ptr<sound_handle> sound_ptr;

inline sound_ptr LoadSoundPtr(const TCHAR* path)
{
	return std::make_shared< sound_handle >(path);
}

inline int PlaySoundPtr(sound_ptr sound, int play_type = DX_PLAYTYPE_BACK)
{
	return DxLib::PlaySoundMem(sound->handle(), play_type);
}

inline int StopSoundPtr(sound_ptr sound)
{
	return DxLib::StopSoundMem(sound->handle());
}

inline bool CheckSoundPtr(sound_ptr sound)
{
	return (DxLib::CheckSoundMem(sound->handle()) == 1) ? true : false;
}
