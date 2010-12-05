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
    $options += cumulus_views_options();
    return $options;
  }

  /**
   * Render the given style.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    cumulus_views_options_form($form, $form_state, $this);
  }

  function render_fields($result) {
    if (!$this->uses_fields()) {
      return;
    }

    $options = $this->view->style_options;
    if (empty($options['title_field'])) {
      drupal_set_message(t('You have to define a title field to display items.'), 'error');
      return;
    }

    if (isset($this->rendered_fields)) {
      return $this->rendered_fields;
    }
    $view = $this->view;

    $title_alias = $view->field[$options['title_field']]->field_alias;
    $weight_alias = $view->field[$options['use_field_as_weight']['weight_field']]->field_alias;

    // Range is from 1 to count($rows).
    $range = max(.01, count($result)) * 1.0001;

    $index = 1;
    $weight = 0;
    $tags_formatted_flash = '';

    $url_options = array();

    if (!empty($view->exposed_raw_input)) {
      $url_options['query'] = $view->exposed_raw_input;
    }


    foreach ($result as $row) {
      $row->nid = 1243;
    }
  }

}

