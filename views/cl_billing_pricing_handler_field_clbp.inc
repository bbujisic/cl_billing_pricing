<?php

/**
 * @file
 * Definition of cl_billing_pricing_handler_field_clbp
 */

/**
 * Provides a custom views field.
 */
class cl_billing_pricing_handler_field_clbp extends views_handler_field {
  function option_definition() {
    $options = parent::option_definition();
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
  }

  function get_value($values, $field = NULL) {
    $value = parent::get_value($values, $field);
    // dpm([$values, $field, $value, $this->additional_fields]);

    return $value;
  }

  function render($data) {
    $this->get_value($data);
    $output = t("Hello World!");
    return $output;
  }
}