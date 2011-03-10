<?php

/**
 * @file
 * Provide an cumulus style plugin for Views. This file is autoloaded by views.
 */

/**
 * Implementation of hook_views_plugins().
 *
 * Add cumulus style plugin.
 */
function cumulus_views_plugins() {
  $path = drupal_get_path('module', 'cumulus') . '/includes/views';
  return array(
    'style' => array(
      'cumulus' => array(
        'title' => t('Cumulus cloud'),
        'help' => t('Displays rows as an flash-based 3D "tag"-cloud.'),
        'handler' => 'views_cumulus_style_plugin',
        'theme' => 'views_view_cumulus',
        'theme path' => $path,
        'uses row plugin' => FALSE,
        'uses options' => TRUE,
        'uses fields' => TRUE,
        'uses grouping' => FALSE,
        'type' => 'normal',
        'path' => $path,
      ),
      'cumulus_summary' => array(
        'title' => t('Cumulus cloud'),
        'help' => t('Displays rows as an flash-based 3D "tag"-cloud.'),
        'handler' => 'views_cumulus_summary_style_plugin',
        'parent' => 'default_summary',
        'theme' => 'views_view_cumulus',
        'theme path' => $path,
        'type' => 'summary', // only shows up as a summary style
        'uses options' => TRUE,
        'path' => $path,
      ),
    ),
  );
}

function cumulus_views_options_form(&$form, &$form_state, $view) {
  if ($view->definition['type'] === 'normal') {
    $fields = $view->view->display_handler->get_handlers('field');
    if (count($fields)) {
      $options = array('' => t('<None>'));
      foreach ($fields as $field => $handler) {
        if ($label = $handler->label()) {
          $options[$field] = $label;
        }
        else {
          $options[$field] = $handler->ui_name();
        }
      }
      $form['unique_id'] = array(
        '#type' => 'select',
        '#title' => t('Unique ID'),
        '#options' => $options,
        '#default_value' => $view->options['unique_id'],
        '#description' => t('Select the field that should be used to be unqiue (e.g. Entitiy ID like Term ID or User ID.)'),
      );
      $form['title_field'] = array(
        '#type' => 'select',
        '#title' => t('Title field'),
        '#options' => $options,
        '#default_value' => $view->options['title_field'],
        '#description' => t('Select the field that should be used as the items title in the cloud.'),
      );
      $form['link_field'] = array(
        '#type' => 'select',
        '#title' => t('Link field'),
        '#options' => $options,
        '#default_value' => $view->options['link_field'],
        '#description' => t('Select the field that should be used as the items link in the cloud.'),
      );
      $form['use_field_as_weight']['#tree'] = TRUE;
      $form['use_field_as_weight']['weight_text'] = array(
        '#type' => 'checkbox',
        '#title' => t('Use a field as source for weight calculation'),
        '#description' => t('If checked, you can select a field that is use as source for weight calculation instead of using the sort order.'),
        '#default_value' => $view->options['use_field_as_weight']['weight_text'],
      );
      $form['use_field_as_weight']['weight_field'] = array(
        '#type' => 'select',
        '#title' => t('Weight field'),
        '#options' => $options,
        '#default_value' => $view->options['use_field_as_weight']['weight_field'],
        '#description' => t('Select the field that should be used for weight calculation.'),
        /*
        // TODO: use drupal form states
        '#process' => array('views_process_dependency'),
        '#dependency' => array(
          'edit-style-options-use-field-as-weight-weight-text' => array(1)
        ),
        */  
      );
    }
    else {
      drupal_set_message(t('You need to define at least two fields to set up a cumulus cloud view. 1. Name of the link. 2. URL for the link. And 3. Optional weight.', 'error'));
    }
  }
  $form['size_interval'] = array(
    '#type' => 'textfield',
    '#title' => t('Item size interval'),
    '#default_value' => $view->options['size_interval'],
    '#maxlength' => 2,
    '#description' => t('The number of item sizes you want to use.'),
  );
  $form['flash_transparency'] = array(
    '#type' => 'select',
    '#title' => t('Background transparency'),
    '#default_value' => $view->options['flash_transparency'],
    '#options' => array(
      'false' => t('no'),
      'true' => t('yes'),
    ),
    '#description' => t('Enabling background transparency might cause issues with some (mostly older) browsers.<br />Under Linux, transparency doesn\'t work at all due to a known limitation in the current Flash player.'),
  );
  $form['flash_width'] = array(
    '#type' => 'textfield',
    '#title' => t('Width of cumulus'),
    '#default_value' => $view->options['flash_width'],
    '#maxlength' => 3,
    '#description' => t('The width of the cumulus in pixels.'),
  );
  $form['flash_height'] = array(
    '#type' => 'textfield',
    '#title' => t('Height of cumulus'),
    '#default_value' => $view->options['flash_height'],
    '#maxlength' => 3,
    '#description' => t('The height of the cumulus in pixels.'),
  );
  $form['flash_background'] = array(
    '#type' => 'textfield',
    '#title' => t('Background color of cumulus'),
    '#default_value' => $view->options['flash_background'],
    '#maxlength' => 6,
    '#description' => t('The hex color value for the background of the cumulus. E.g. ffffff. If "Background transparency" is enabled, this option will have no effect.'),
  );
  $form['flash_color'] = array(
    '#type' => 'textfield',
    '#title' => t('Font color of cumulus'),
    '#default_value' => $view->options['flash_color'],
    '#maxlength' => 6,
    '#description' => t('The hex color value you would like to use for the items. E.g. 000000.'),
  );
  $form['flash_color2'] = array(
    '#type' => 'textfield',
    '#title' => t('Second font color of cumulus'),
    '#default_value' => $view->options['flash_color2'],
    '#maxlength' => 6,
    '#description' => t('Second item color. If supplied, items will get a color from a gradient between both colors based on their sorting.'),
  );
  $form['flash_hicolor'] = array(
    '#type' => 'textfield',
    '#title' => t('Highlight color of cumulus'),
    '#default_value' => $view->options['flash_hicolor'],
    '#maxlength' => 6,
    '#description' => t('The hex color value you would like to use for the item mouseover/hover color'),
  );
  $form['flash_speed'] = array(
    '#type' => 'textfield',
    '#title' => t('Rotation speed'),
    '#default_value' => $view->options['flash_speed'],
    '#maxlength' => 3,
    '#description' => t('Set the speed of the cumulus. Options between 25 and 500 work best.'),
  );
  $form['flash_distribute'] = array(
    '#type' => 'select',
    '#title' => t('Distribute items evenly on cumulus'),
    '#default_value' => $view->options['flash_distribute'],
    '#options' => array(
      'false' => t('no'),
      'true' => t('yes'),
    ),
    '#description' => t('When enabled, the movie will attempt to distribute the items evenly over the surface of the cumulus.'),
  );
  $form['flash_font_size'] = array(
    '#type' => 'textfield',
    '#title' => t('Font size'),
    '#default_value' => $view->options['flash_font_size'],
    '#maxlength' => 2,
    '#description' => t('Set the font size of the tag with the lowest item-size in pixels (level 1).'),
  );
  $form['flash_font_size_interval'] = array(
    '#type' => 'textfield',
    '#title' => t('Font size interval'),
    '#default_value' => $view->options['flash_font_size_interval'],
    '#maxlength' => 1,
    '#description' => t('Set the font size interval used for the different item-sizes (level 2 and higher).'),
  );
}
