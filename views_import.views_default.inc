<?php

function views_import_views_default_views() {
  $dir = drupal_get_path('module', 'views_import') .'/import';
  $files = file_scan_directory($dir, '.*', array('.', '..', 'CVS', 'README.txt'), 0, FALSE);

  foreach ($files as $file) {
    $export_data = file_get_contents($file->filename);
    eval($export_data);
    $view->disabled = TRUE;
    $views[$view->name] = $view;
  }

  return $views;
}
