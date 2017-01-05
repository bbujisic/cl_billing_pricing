<?php

/**
 * @file
 * Definition of cl_billing_pricing_handler_field_data
 */

/**
 * Provides a custom views field.
 */
class cl_billing_pricing_handler_field_data extends views_handler_field_serialized {

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    unset($form['format']);
    unset($form['key']);
  }

  function options_validate(&$form, &$form_state) {

  }


  function render($values) {
    $value = $values->{$this->field_alias};
    $value = (array) unserialize($value);

    if (empty($value['amount'])) {
      return FALSE;
    }

    if (isset($value['currency_code']) && !empty($value['amount'])) {
      if ($value['currency_code'] == 0) {
        $value['currency_code'] = commerce_default_currency();
      }
      return commerce_currency_format($value['amount'], $value['currency_code']);
    }

    return $value['amount'];
  }
}
