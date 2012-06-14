<?php
/**
 * @file views_import.views_default.inc
 */

/**
 * Includes file with view and returns view object or NULL if file don't have a
 * view.
 *
 * @param string $filename
 *
 * @return mixed
 */
function _views_import_fetch_view($filename) {
  $view = NULL;
  include $filename;
  if ($view && isset($view->name)) {
    return $view;
  }
  else {
    return NULL;
  }
}

/**
 * Implements hook_views_default_views().
 *
 * @return array
 */
function views_import_views_default_views() {
  $dir = 'sites/all/imports/views';
  $files = file_scan_directory($dir, '.inc', array(), 0, FALSE);
  
  foreach ($files as $file) {
    $view = _views_import_fetch_view($file->filename);
    if ($view) {
      $view->tag = 'views_import';
      $views[$view->name] = $view;
    }
  }

  return $views;
}
