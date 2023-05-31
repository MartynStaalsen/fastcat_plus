#ifndef FASTCAT_LOGGER_H_
#define FASTCAT_LOGGER_H_

// Include related header (for cc files)

// Include c then c++ libraries

// Include external then project includes
#include "fastcat/device_base.h"

namespace fastcat
{


class Logger : public DeviceBase
{
 public:
  Logger();
  bool ConfigFromYaml(YAML::Node node) override;
  bool Read() override;
 protected:
  double last_signal_value_;
};

}  // namespace fastcat

#endif
