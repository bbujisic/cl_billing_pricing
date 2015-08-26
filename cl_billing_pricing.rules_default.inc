<?php

/**
 * @file
 * Default rule configurations for Commerce License Billing Pricing.
 */

/**
 * Implements hook_default_rules_configuration().
 */
function commerce_license_billing_pricing_default_rules_configuration() {
  $items = array();

  $items['commerce_license_billing_pricing_process'] = entity_import('rules_config', '{ "commerce_license_billing_pricing_process" : {
      "LABEL" : "Process license- and user-specific pricing field",
      "PLUGIN" : "reaction rule",
      "WEIGHT" : "-50",
      "OWNER" : "rules",
      "TAGS" : [ "Commerce License Billing" ],
      "REQUIRES" : [
        "rules",
        "commerce_license_billing",
        "commerce_line_item",
        "commerce_product_reference"
      ],
      "ON" : { "commerce_product_calculate_sell_price" : [] },
      "IF" : [
        { "entity_is_of_bundle" : {
            "entity" : [ "commerce-line-item" ],
            "type" : "commerce_line_item",
            "bundle" : { "value" : { "recurring" : "recurring" } }
          }
        }
      ],
      "DO" : [
        { "commerce_license_billing_pricing_rules_process_line_item" : {
            "commerce_line_item" : [ "commerce_line_item" ],
          }
        }
      ]
    }
  }');

  return $items;
}

