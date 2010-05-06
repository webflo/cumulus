<?php
// $Id$

/**
 * @file
 * Contains the cumulus style plugin.
 */

/**
 * Style plugin to render the results as a 3D Flash-cloud.
 *
 * @ingroup views_style_plugins
 */
class views_cumulus_style_plugin extends views_plugin_style {
  /**
   * Set default options
   */
  function option_definition() {
    $options = parent::option_definition();

    $options['title_field'] = array('default' => '');
    $options['use_field_as_weight']['weight_text'] = array('default' => 0);
    $options['use_field_as_weight']['weight_field'] = array('default' => '');
    $options['size_interval'] = array('default' => 6);
    $options['flash_width'] = array('default' => 200);
    $options['flash_height'] = array('default' => 150);
    $options['flash_background'] = array('default' => 'ffffff');
    $options['flash_transparency'] = array('default' => 'false');
    $options['flash_color'] = array('default' => 'ff0000');
    $options['flash_color2'] = array('default' => '000000');
    $options['flash_hicolor'] = array('default' => '666666');
    $options['flash_speed'] = array('default' => 100);
    $options['flash_distribute'] = array('default' => 'true');
    $options['flash_font_size'] = array('default' => 10);
    $options['flash_font_size_interval'] = array('default' => 2);

    return $options;
  }

  /**
   * Render the given style.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $fields = $this->view->display_handler->get_handlers('field');
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
      $form['title_field'] = array(
        '#type' => 'select',
        '#title' => t('Title field'),
        '#options' => $options,
        '#default_value' => $this->options['title_field'],
        '#description' => t('Select the field that should be used as the items title in the cloud.'),
      );
      $form['use_field_as_weight']['#tree'] = TRUE;
      $form['use_field_as_weight']['weight_text'] = array(
        '#type' => 'checkbox',
        '#title' => t('Use a field as source for weight calculation'),
        '#description' => t('If checked, you can select a field that is use as source for weight calculation instead of using the sort order.'),
        '#default_value' => $this->options['use_field_as_weight']['weight_text'],
      );
      $form['use_field_as_weight']['weight_field'] = array(
        '#type' => 'select',
        '#title' => t('Weight field'),
        '#options' => $options,
        '#default_value' => $this->options['use_field_as_weight']['weight_field'],
        '#description' => t('Select the field that should be used for weight calculation.'),
        '#process' => array('views_process_dependency'),
        '#dependency' => array(
          'edit-style-options-use-field-as-weight-weight-text' => array(1)
        ),
      );
    }
    else {
      drupal_set_message(t('You need to define at least one field to set up a cumulus cloud view.', 'error'));
    }
    $form['size_interval'] = array(
      '#type' => 'textfield',
      '#title' => t('Item size interval'),
      '#default_value' => $this->options['size_interval'],
      '#maxlength' => 2,
      '#description' => t('The number of item sizes you want to use.'),
    );
    $form['flash_transparency'] = array(
      '#type' => 'select',
      '#title' => t('Background transparency'),
      '#default_value' => $this->options['flash_transparency'],
      '#options' => array(
        'false' => t('no'),
        'true' => t('yes'),
      ),
      '#description' => t('Enabling background transparency might cause issues with some (mostly older) browsers.<br />Under Linux, transparency doesn\'t work at all due to a known limitation in the current Flash player.'),
    );
    $form['flash_width'] = array(
      '#type' => 'textfield',
      '#title' => t('Width of cumulus'),
      '#default_value' => $this->options['flash_width'],
      '#maxlength' => 3,
      '#description' => t('The width of the cumulus in pixels.'),
    );
    $form['flash_height'] = array(
      '#type' => 'textfield',
      '#title' => t('Height of cumulus'),
      '#default_value' => $this->options['flash_height'],
      '#maxlength' => 3,
      '#description' => t('The height of the cumulus in pixels.'),
    );
    $form['flash_background'] = array(
      '#type' => 'textfield',
      '#title' => t('Background color of cumulus'),
      '#default_value' => $this->options['flash_background'],
      '#maxlength' => 6,
      '#description' => t('The hex color value for the background of the cumulus. E.g. ffffff. If "Background transparency" is enabled, this option will have no effect.'),
    );
    $form['flash_color'] = array(
      '#type' => 'textfield',
      '#title' => t('Font color of cumulus'),
      '#default_value' => $this->options['flash_color'],
      '#maxlength' => 6,
      '#description' => t('The hex color value you would like to use for the items. E.g. 000000.'),
    );
    $form['flash_color2'] = array(
      '#type' => 'textfield',
      '#title' => t('Second font color of cumulus'),
      '#default_value' => $this->options['flash_color2'],
      '#maxlength' => 6,
      '#description' => t('Second item color. If supplied, items will get a color from a gradient between both colors based on their sorting.'),
    );
    $form['flash_hicolor'] = array(
      '#type' => 'textfield',
      '#title' => t('Highlight color of cumulus'),
      '#default_value' => $this->options['flash_hicolor'],
      '#maxlength' => 6,
      '#description' => t('The hex color value you would like to use for the item mouseover/hover color'),
    );
    $form['flash_speed'] = array(
      '#type' => 'textfield',
      '#title' => t('Rotation speed'),
      '#default_value' => $this->options['flash_speed'],
      '#maxlength' => 3,
      '#description' => t('Set the speed of the cumulus. Options between 25 and 500 work best.'),
    );
    $form['flash_distribute'] = array(
      '#type' => 'select',
      '#title' => t('Distribute items evenly on cumulus'),
      '#default_value' => $this->options['flash_distribute'],
      '#options' => array(
        'false' => t('no'),
        'true' => t('yes'),
      ),
      '#description' => t('When enabled, the movie will attempt to distribute the items evenly over the surface of the cumulus.'),
    );
    $form['flash_font_size'] = array(
      '#type' => 'textfield',
      '#title' => t('Font size'),
      '#default_value' => $this->options['flash_font_size'],
      '#maxlength' => 2,
      '#description' => t('Set the font size of the tag with the lowest item-size in pixels (level 1).'),
    );
    $form['flash_font_size_interval'] = array(
      '#type' => 'textfield',
      '#title' => t('Font size interval'),
      '#default_value' => $this->options['flash_font_size_interval'],
      '#maxlength' => 1,
      '#description' => t('Set the font size interval used for the different item-sizes (level 2 and higher).'),
    );
  }

  /**
   * Render the display in this style.
   */
  function render() {
    $output = parent::render();
    $js = drupal_get_path('module', 'cumulus') .'/cumulus.js';
    if (file_exists($js)) {
      drupal_add_js($js, 'module', 'header', FALSE, TRUE, FALSE);
    }
    else {
      drupal_set_message(t('The file @folder is missing. Please download it from !link, and add it to the Cumulus module folder!', array('@folder' => $js, '!link' => l('http://pratul.in/files/cumulus.js', 'http://pratul.in/files/cumulus.js'))), 'error');
    }

    return $output;
  }
}

