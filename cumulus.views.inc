<?php
// $Id$
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
  return array(
    'style' => array(
      'cumulus' => array(
        'title' => t('Cumulus cloud'),
        'help' => t('Displays rows as an flash-based 3D "tag"-cloud.'),
        'handler' => 'views_cumulus_style_plugin',
        'theme' => 'views_view_cumulus',
        'uses row plugin' => FALSE,
        'uses options' => TRUE,
        'uses fields' => TRUE,
        'uses grouping' => FALSE,
        'type' => 'normal',
      ),
    ),
  );
}
