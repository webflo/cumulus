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
