#pragma once

#include "NGS/base/base.h"

NGS_BEGIN

/**
* @brief 影片剪辑的计算部分，可以使需要成为影片剪辑的类继承此类
* @brief 帧数范围为[1,?)（非0）
* @brief 请调用Update函数实时刷新影片剪辑
*/
class Movie {
public:
	NGS_FLAG(IS_PLAYING, 0);
	NGS_FLAG(IS_INVERT_PLAY, 1);
	NGS_FLAG(IS_LOOP, 2);

public:
	Movie() :
		_frameCount(0),
		_currentFrame(0),
		_totalFrames(1)
	{}
	Movie(size_t totalFrames) :
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

	void Play() { _mc_flag[IS_PLAYING] = true; }
	void Stop() { _mc_flag[IS_PLAYING] = false; }
	bool IsPlaying()const { return _mc_flag[IS_PLAYING]; }

	void GoTo(size_t frame, bool isPlay) {
		GoTo(frame);
		_mc_flag[IS_PLAYING] = isPlay;
	}
	template<bool IS_PLAY>
	void GoTo(size_t frame) {
		GoTo(frame);
		Bits<IS_PLAY>(_mc_flag, IS_PLAYING);
	}
	void GoTo(size_t frame) {
		_currentFrame = frame - 1;
		_frameCount = 0;
	}
	void GoToAndPlay(size_t frame) { GoTo<true>(frame); }
	void GoToAndStop(size_t frame) { GoTo<false>(frame); }

	void Loop() { GoTo(IsInvertPlay() ? TotalFrames() : 1); _mc_flag[IS_LOOP] = true; }
	void StopLoop() { _mc_flag[IS_LOOP] = false; }
	bool IsLoop()const { return _mc_flag[IS_LOOP]; }

	bool IsInvertPlay()const { return _mc_flag[IS_INVERT_PLAY]; }
	void PlayDirect(bool isInvertPlay) { _mc_flag[IS_INVERT_PLAY] = isInvertPlay; }

	size_t TotalFrames()const { return _totalFrames; }
	void TotalFrames(size_t v) { _totalFrames = v; }
	size_t CurrentFrame()const { return _currentFrame + 1; }
	size_t FrameCount()const { return _frameCount; }

	size_t FrameStart()const { return (_totalFrames - 1) * IsInvertPlay() + 1; }
	size_t FrameEnd()const { return (_totalFrames - 1) * !IsInvertPlay() + 1; }

	bool IsPlayStart()const { return CurrentFrame() == FrameStart(); }
	bool IsPlayEnd()const { return CurrentFrame() == FrameEnd(); }
private:
	BitSet<8> _mc_flag = IS_PLAYING | IS_LOOP;

	size_t _frameCount;
	size_t _currentFrame;
	size_t _totalFrames;
};

NGS_END