<?php


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

  function render() {

    $options = $this->view->style_options;
    if (empty($options['title_field'])) {
      drupal_set_message(t('You have to define a title field to display items.'), 'error');
      return;
    }

    if (!$this->uses_fields()) {
      return;
    }

    if (isset($this->rendered_fields)) {
      return $this->rendered_fields;
    }

    $this->view->row_index = 0;
    $keys = array_keys($this->view->field);
    foreach ($this->view->result as $count => $row) {
      $this->view->row_index = $count;
      foreach ($keys as $id) {
        $this->rendered_fields[$count][$id] = $this->view->field[$id]->theme($row);
      }
    }
    unset($this->view->row_index);
    // TODO: title is undefined.
    $output .= theme($this->theme_functions(),
      array(
        'view' => $this->view,
        'options' => $this->options,
        'rows' => array(),
        'title' => $title,
      ),
    );
    return $output;
  }

}

