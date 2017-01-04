<?php

/**
 * @file
 * Definition of cl_billing_pricing_handler_field_action
 */

/**
 * Provides a custom views field.
 */
class cl_billing_pricing_handler_field_action extends views_handler_field {

  function option_definition() {
    $options = parent::option_definition();
    $options['format'] = 1;

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['format'] = [
      '#type' => 'select',
      '#title' => t('Format'),
      '#options' => array(
        0 => t('Machine name'),
        1 => t('Label'),
      ),
      '#default_value' => $this->options['format'],
      '#description' => t('Choose action name format.'),
    ];
  }

  function get_value($values, $field = NULL) {
    $value = parent::get_value($values, $field);

    if ($this->options['format'] == 1) {
      $actions = _cl_billing_pricing_actions_options();
      if (!empty($actions[$value])) {

        return $actions[$value];
      }
    }

    return $value;
  }
}
