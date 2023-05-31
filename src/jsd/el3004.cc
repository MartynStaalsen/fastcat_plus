// Include related header (for cc files)
#include "fastcat/jsd/el3004.h"

// Include c then c++ libraries

// Include external then project includes
#include "fastcat/yaml_parser.h"

fastcat::El3004::El3004()
{
  MSG_DEBUG("Constructed El3004");

  state_       = std::make_shared<DeviceState>();
  state_->type = EL3004_STATE;
}

bool fastcat::El3004::ConfigFromYaml(YAML::Node node)
{
  bool retval = ConfigFromYamlCommon(node);
  jsd_set_slave_config((jsd_t*)context_, slave_id_, jsd_slave_config_);
  return retval;
}

bool fastcat::El3004::ConfigFromYamlCommon(YAML::Node node)
{
  if (!ParseVal(node, "name", name_)) {
    return false;
  }
  state_->name = name_;

  jsd_slave_config_.configuration_active = true;
  jsd_slave_config_.product_code         = JSD_EL3004_PRODUCT_CODE;
  snprintf(jsd_slave_config_.name, JSD_NAME_LEN, "%s", name_.c_str());

  return true;
}

bool fastcat::El3004::Read()
{
  jsd_el3004_read((jsd_t*)context_, slave_id_);

  const jsd_el3004_state_t* jsd_state =
      jsd_el3004_get_state((jsd_t*)context_, slave_id_);

  state_->el3004_state.voltage_ch1   = jsd_state->voltage[0];
  state_->el3004_state.voltage_ch2   = jsd_state->voltage[1];
  state_->el3004_state.voltage_ch3   = jsd_state->voltage[2];
  state_->el3004_state.voltage_ch4   = jsd_state->voltage[3];
  state_->el3004_state.adc_value_ch1 = jsd_state->adc_value[0];
  state_->el3004_state.adc_value_ch2 = jsd_state->adc_value[1];
  state_->el3004_state.adc_value_ch3 = jsd_state->adc_value[2];
  state_->el3004_state.adc_value_ch4 = jsd_state->adc_value[3];

  return true;
}