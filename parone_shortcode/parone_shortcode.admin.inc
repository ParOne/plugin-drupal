<?php

/**
 * @file
 * Administrative page callbacks for the parone_shortcode module.
 */

/**
 * Implements hook_admin_settings() for module settings configuration.
 */
function parone_shortcode_admin_settings_form($form_state) {
    drupal_add_js("https://sdk-stage.parone.io/parone.js", "external");
    drupal_add_js("https://network-videos.parone.io/network-videos.umd.js", "external");
    $form['parone_code'] = array(
        '#type' => 'fieldset',
        '#title' => t('General settings'),
    );
    
    $form['parone_code']['parone_feed_id'] = array(
        '#title' => t('ParOne Feed Sync Code'),
        '#type' => 'textfield',
        '#default_value' => variable_get('parone_feed_id', ''),
        '#size' => 20,
        '#maxlength' => 20,
        '#required' => TRUE,
        '#description' => t('Feed Sync Code is used to view different videos associated with your account.'),
    );
    $feed_id = variable_get('parone_feed_id', '');

    if (!empty($feed_id)) {
        $response = drupal_http_request("https://api.parone.io/find_feeds/$feed_id");
        $feeds = $response->data;
        $form['parone_feeds'] = array(
            '#type' => 'fieldset',
            '#title' => t('Parone Feeds'),
        );
        $form['parone_feeds']['feeds'] = [
            "#markup" => "<parone-network-videos cms='drupal' feeds=$feeds> </parone-network-videos>",
        ];
    }
    
    return system_settings_form($form);
}