#ifndef FASTCAT_EL3004_H_
#define FASTCAT_EL3004_H_

// Include related header (for cc files)

// Include c then c++ libraries

// Include external then project includes
#include "fastcat/jsd/jsd_device_base.h"
#include "jsd/jsd_el3004_pub.h"

namespace fastcat
{
class El3004 : public JsdDeviceBase
{
 public:
  El3004();
  bool ConfigFromYaml(YAML::Node node) override;
  bool Read() override;

 protected:
  bool ConfigFromYamlCommon(YAML::Node node);

 private:
  jsd_slave_config_t jsd_slave_config_{0};
};

}  // namespace fastcat

#endif