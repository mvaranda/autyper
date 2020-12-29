#ifndef FEEDERMP3_H
#define FEEDERMP3_H

#include "feederbase.h"

class FeederMp3: FeederBase
{
public:
  FeederMp3(QString input);
  feeder_res_t getSamples(sample_t * samples, uint32_t num_samples, int progress);

private:
  FeederMp3() {};
};

#endif // FEEDERMP3_H
