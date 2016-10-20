#pragma once

#include "filter.h"
#include <speex/speex_echo.h>
#include <speex/speex_preprocess.h>

#include <QAudioFormat>

class SpeexAECFilter : public Filter
{
public:
  SpeexAECFilter(StatisticsInterface* stats, QAudioFormat format);
  ~SpeexAECFilter();

protected:

  void process();

private:
  SpeexEchoState *echo_state_;
  SpeexPreprocessState *preprocess_state_;

  QAudioFormat format_;

  uint32_t frameSize_;

  int16_t* pcmOutput_;
  int32_t max_data_bytes_;
};
