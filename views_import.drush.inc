<?php
/**
 * @file
 * Drush commands for views_import module.
 *
 * Command to export includes files to store Views definitions on the disk.
 */

module_load_include('inc', 'views_import', 'views_import.drush');

/**
 * Callback for views_import_export_views command.
 *
 * @param string $view_name
 *   String containing the name of the view to export.
 */
function drush_views_import_export_views($view_name = '') {
  $views = views_get_all_views();
  $all = drush_get_option('all', 0);
  if ($view_name == '' and $all >= 1) {
    foreach ($views as $vname => $view) {
      _views_import_export_view($vname, $views);
    }
  }
  elseif ($view_name != '') {
    if (array_key_exists($view_name, $views)) {
      _views_import_export_view($view_name, $views);
    }
    else {
      return drush_set_error(dt('"@view_name" is not a valid view name', array('@view_name' => $view_name)));
    }
  }
  else {
    return drush_set_error(dt('No view name given, nothing to do :('));
  }
}

/**
 * Helper function to write individual views files.
 *
 * @param string $name
 *   Name of the view to export.
 * @param array $views
 *   Array of Views available to Drupal, generally from views_get_all_views().
 */
function _views_import_export_view($name, $views) {
  $file_name = $name . '.inc';
  $export = "<?php \n";
  $export .= views_export_view($views[$name]);
  file_put_contents(VIEWS_IMPORT_DIR . '/' . $file_name, $export);
}
