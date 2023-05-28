#pragma once

#include "NGS/NGS_Defined.h"
#include "NGS/NGS_Defined.h"
#include "NGS/NGS_STL.h"
#include "NGS/NGS_Bit.h"

NGS_BEGIN

/**
* @brief 影片剪辑的计算部分，可以使需要成为影片剪辑的类继承此类
* @brief 帧数范围为[1,?)（非0）
* @brief 请调用Update函数实时刷新影片剪辑
*/
class Movie {
public:
	NGS_DEFAULT_TYPE;

	inline constexpr const static _TYP FLAG
		IS_PLAYING = bit(0),
		IS_INVERT_PLAY = bit(1),
		IS_LOOP = bit(2)
		;
public:
	Movie() :
		_frameCount(0),
		_currentFrame(0),
		_totalFrames(1)
	{}
	Movie(__size totalFrames) :
		_frameCount(0),
		_currentFrame(0),
		_totalFrames(totalFrames)
	{}

	virtual void Update() {
		if (IsPlaying()) {
			if (IsInvertPlay())
				PrevFrame();
			else
				NextFrame();
		}
		++_frameCount;
	}

	void AddFrameScript();

	void NextFrame() {
		if (_currentFrame < TotalFrames() - 1) {
			GoTo(_currentFrame + 1 + 1);
			return;
		}
		if (IsLoop())
			GoTo(1);
		else
			Stop();
	}
	void PrevFrame() {
		if (_currentFrame > 0) {
			GoTo(_currentFrame + 1 - 1);
			return;
		}
		if (IsLoop())
			GoTo(TotalFrames());
		else
			Stop();
	}

	void Play() { Bits<true>(_mc_flag, IS_PLAYING); }
	void Stop() { Bits<false>(_mc_flag, IS_PLAYING); }
	bool IsPlaying()const { return Bits(_mc_flag, IS_PLAYING); }

	void GoTo(__size frame, bool isPlay) {
		GoTo(frame);
		Bits(_mc_flag, IS_PLAYING, isPlay);
	}
	template<bool IS_PLAY>
	void GoTo(__size frame) {
		GoTo(frame);
		Bits<IS_PLAY>(_mc_flag, IS_PLAYING);
	}
	void GoTo(__size frame) {
		_currentFrame = frame - 1;
		_frameCount = 0;
	}
	void GoToAndPlay(__size frame) { GoTo<true>(frame); }
	void GoToAndStop(__size frame) { GoTo<false>(frame); }

	void Loop() { GoTo(IsInvertPlay() ? TotalFrames() : 1); Bits<true>(_mc_flag, IS_LOOP); }
	void StopLoop() { Bits<false>(_mc_flag, IS_LOOP); }
	bool IsLoop()const { return Bits(_mc_flag, IS_LOOP); }

	bool IsInvertPlay()const { return Bits(_mc_flag, IS_INVERT_PLAY); }
	void PlayDirect(bool isInvertPlay) { Bits(_mc_flag, IS_INVERT_PLAY, isInvertPlay); }

	__size TotalFrames()const { return _totalFrames; }
	void TotalFrames(__size v) { _totalFrames = v; }
	__size CurrentFrame()const { return _currentFrame + 1; }
	__size FrameCount()const { return _frameCount; }

	__size FrameStart()const { return (_totalFrames - 1) * IsInvertPlay() + 1; }
	__size FrameEnd()const { return (_totalFrames - 1) * !IsInvertPlay() + 1; }

	bool IsPlayStart()const { return CurrentFrame() == FrameStart(); }
	bool IsPlayEnd()const { return CurrentFrame() == FrameEnd(); }
private:
	_TYP FLAG _mc_flag = IS_PLAYING | IS_LOOP;

	__size _frameCount;
	__size _currentFrame;
	__size _totalFrames;
};

NGS_END