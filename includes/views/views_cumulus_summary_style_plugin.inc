<?php

/**
 * A tag-cloud summary style view.
 */
class views_cumulus_summary_style_plugin extends views_plugin_style_summary {

  /**
   * Set default options
   */
  function option_definition() {
    return cumulus_views_options();
  }

  /**
   * Render the given style.
   */
  function options_form(&$form, &$form_state) {
    cumulus_views_options_form($form, $form_state, $this);
  }

  function render() {
    foreach($this->view->result as $row) {
      $this->rendered_fields[] = array(
        'link' => 'taxonomy/term/' . $row->term_node_tid,
        'name' => $row->term_data_name,
        'weight' => $row->num_records,
        );
    }
    $output .= theme($this->theme_functions(), $this->view, $this->options, $rows, $title);
    return $output;
  }

}
