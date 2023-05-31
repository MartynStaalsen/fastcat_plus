// Include related header (for cc files)
#include "fastcat/fastcat_devices/logger.h"

// Include c then c++ libraries
#include <cmath>

// Include external then project includes
#include "fastcat/signal_handling.h"
#include "fastcat/yaml_parser.h"
#include "jsd/jsd_print.h"

fastcat::Logger::Logger()
{
  state_       = std::make_shared<DeviceState>();
  state_->type = LOGGER_STATE;
  last_signal_value_ = 0;
}

bool fastcat::Logger::ConfigFromYaml(YAML::Node node)
{
  if (!ParseVal(node, "name", name_)) {
    return false;
  }
  state_->name = name_;

  if (!ConfigSignalsFromYaml(node, signals_, false)) {
    return false;
  }
  if (signals_.size() != 1) {
    ERROR("Expecting exactly one signal for Logger, saw %ld", signals_.size());
    return false;
  }

  return true;
}

bool fastcat::Logger::Read()
{
  // update input signal
  if (!UpdateSignal(signals_[0])) {
    ERROR("Could not extract signal");
    return false;
  }

  double signal_value = signals_[0].value;
  MSG("watching signal %s with value %f\n", signals_[0].observed_device_name.c_str(), signal_value);

  state_->logger_state.output = (signal_value != last_signal_value_);  // for the sake of output...
  last_signal_value_ = signal_value;

  return true;
}
