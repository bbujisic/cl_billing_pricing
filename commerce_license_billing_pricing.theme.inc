<?php


/**
 * Render a pricing field form. Similar to theme_field_multiple_value_form
 * in most respects, but without tabledrag and with shared headings.
 */
function theme_cl_billing_pricing_form($variables) {
  $element = $variables['element'];
  $output = '';

  $table_id = drupal_html_id($element['#field_name'] . '_values');
  $required = !empty($element['#required']) ? theme('form_required_marker', $variables) : '';

  $header = array(
    t('Condition'),
    t('Action'),
    t('Values'),
    t('Expiration'),
    t('Weight'),
  );
  $rows = array();

  // Sort items according to '_weight' (needed when the form comes back after
  // preview or failed validation)
  $items = array();
  foreach (element_children($element) as $key) {
    if ($key === 'add_more') {
      $add_more_button = &$element[$key];
    }
    else {
      $items[] = &$element[$key];
    }
  }

  // Add the items as table rows.
  foreach ($items as $key => $item) {
    $cells = array();
    foreach (element_children($item) as $child) {
      $cells[] = drupal_render($item[$child]);
    }
    $rows[] = array(
      'data' => $cells,
      'class' => array(),
    );
  }

  $output = '<div class="form-item">';
  $output .= '<label>' . t('!title !required', array('!title' => $element['#title'], '!required' => $required)) . '</label>';
  $output .= theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('id' => $table_id, 'class' => array('field-multiple-table'))));
  $output .= $element['#description'] ? '<div class="description">' . $element['#description'] . '</div>' : '';
  $output .= '<div class="clearfix">' . drupal_render($add_more_button) . '</div>';
  $output .= '</div>';

  return $output;
}
