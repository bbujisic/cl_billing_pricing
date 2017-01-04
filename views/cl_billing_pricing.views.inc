<?php

/**
 * Implements hook_field_views_data().
 */
function cl_billing_pricing_field_views_data($field) {
  $field_name = $field['field_name'];
  $data = field_views_field_default_views_data($field);
  // Only expose these components as Views field handlers.
  $implemented = array(
    'condition' => [
      'field_handler' => 'views_handler_field',
    ],
    'action' => [
      'field_handler' => 'cl_billing_pricing_handler_field_action',
      'filter_handler' => 'cl_billing_pricing_handler_filter_action',
    ],
    'expires' => [
      'field_handler' => 'views_handler_field_date',
      'filter_handler' => 'views_handler_filter_date',
    ],
    'data' => [
      'field_handler' => 'views_handler_field_serialized',
    ],
    'weight' => [
      'field_handler' => 'views_handler_field_numeric',
    ],
  );

  // Define the valid columns.
  $valid_columns = array();
  $properties = cl_billing_pricing_data_property_info();
  $field_labels = field_views_field_label($field['field_name']);
  $field_label = array_shift($field_labels);

  foreach ($implemented as $implement => $handlers) {
    $column_name = $field_name . '_' . $implement;
    $title = t('@field-label - @property-label', array(
      '@field-label' => $field_label,
      '@property-label' => $properties[$implement]['label'],
    ));
    $valid_columns[$column_name] = $handlers;
    $valid_columns[$column_name]['title'] = $title;
  }

  foreach ($data as &$table) {
    // Make sure the parent Views field is defined.
    if (isset($table[$field_name]['field'])) {
      // @todo: this does not work properly -- see how to access all fields
      //        without using hook_field_formatter_view()
      $table[$field_name]['field']['handler'] = 'cl_billing_pricing_handler_field_clbp';

      // Use the parent field definition as a template for component columns.
      $field_def = $table[$field_name]['field'];
      unset($field_def['additional fields']);

      // Iterate over the billing pricing field components.
      foreach ($table as $column_name => &$column) {
        if (empty($column['field']) && isset($valid_columns[$column_name])) {
          // Assign the default component definition.
          $column['field'] = $field_def;
          $column['field']['field_name'] = $column_name;
          $column['field']['real field'] = $column_name;
          $column['field']['handler'] = $valid_columns[$column_name]['field_handler'];
          $column['title'] = $valid_columns[$column_name]['title'];
          $column['title short'] = $valid_columns[$column_name]['title'];
          // Set filter handler from the $implemented array.
          if (!empty($valid_columns[$column_name]['filter_handler'])) {
            $column['filter']['handler'] = $valid_columns[$column_name]['filter_handler'];
          }
          // Unset default filters if handler not set.
          else {
            unset($column['filter']);
          }
        }
      }
    }
  }

  return $data;
}
