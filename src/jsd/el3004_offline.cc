// Include related header (for cc files)
#include "fastcat/jsd/el3004_offline.h"

// Include c then c++ libraries

// Include external then project includes

bool fastcat::El3004Offline::ConfigFromYaml(YAML::Node node)
{
  return ConfigFromYamlCommon(node);
}

bool fastcat::El3004Offline::Read() { return true; }