<?php

/**
 * @file
 * Definition of cl_billing_pricing_handler_filter_action.
 */

/**
 * Filter based on commerce license billing pricing action.
 *
 * @ingroup views_filter_handlers
 */
class cl_billing_pricing_handler_filter_action extends views_handler_filter_in_operator {
  var $value_form_type = 'select';

  function get_value_options() {
    $this->value_options = _cl_billing_pricing_actions_options();
  }
}
