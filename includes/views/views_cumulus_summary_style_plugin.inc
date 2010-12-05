<?php

/**
 * A tag-cloud summary style view.
 */
class views_cumulus_summary_style_plugin extends views_plugin_style_summary {

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

}
