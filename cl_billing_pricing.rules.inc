<?php

/**
 * Implements hook_rules_action_info().
 */
function cl_billing_pricing_rules_action_info() {
  $actions['cl_billing_pricing_rules_process_line_item'] = array(
    'label' => t('Price a license-generated line item based on its pricing specification fields'),
    'parameter' => array(
      'commerce_line_item' => array(
        'type' => 'commerce_line_item',
        'label' => t('Line item'),
      ),
    ),
    'group' => t('Commerce License Billing'),
  );
  
  return $actions;
}

/**
 * Action callback for the field-driven pricing logic this module provides.
 *
 * Tightly wraps the main pricing function in the .module file; provided here
 * to implement this logic as a Rules action, which is the default pricing
 * model used by CLB.
 */
function cl_billing_pricing_rules_process_line_item($line_item) {
  cl_billing_pricing_process_line_item($line_item);
}

