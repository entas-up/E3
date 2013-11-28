<?php
/**
 * @file
 * The admin settings for the UpTime module.
 */

/**
 * Implements hook_settings().
 */
function uptime_admin_settings() {
  $last_refresh = variable_get('uptime_next_execution', 0) - variable_get('uptime_interval', 24 * 60 * 60);
  // Execution time has to be reset to force an instant cron run.
  variable_set('uptime_next_execution', 0);
  // To find a cron call here looks odd, but it's the only way to have any
  // changed variables in the form being processed in the hook_cron(). After
  // submitting the form you come back on the same form and that's when all
  // new variables are available. The only drawback is that cron runs twice
  // (once at the first form load and once at the second), but that's not a
  // big deal.
  drupal_cron_run();
  // Essential to have some credentials.
  $api_key = trim(variable_get('uptime_api_key', ''));
  $monitor_id = trim(variable_get('uptime_monitor_id', ''));
  // Where to find the all-time uptime ratio.
  $url = "http://api.uptimerobot.com/getMonitors?apiKey=" . $api_key . "&monitors=" . $monitor_id . "&format=xml";

  $form['api_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Uptime'),
  );

  $form['api_settings']['uptime_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enabled'),
    '#default_value' => variable_get('uptime_enabled', 1),
    '#description' => t('Disabling pauses the monitor until re-enabling and removes the ratio display. Disable uptime when your site might go down temporarily,for example during development, or if you want to use only the copyright notice.'),
  );

  $form['api_settings']['uptime_api_key'] = array(
    '#type' => 'textfield',
    '#title' => t('API key'),
    '#default_value' => $api_key,
    '#description' => t('To get an API key go to') . ' ' . l(t('www.uptimerobot.com'), 'http://www.uptimerobot.com', array(
        'attributes' => array('target' => '_blank'),
        )) . ' ' . t('▶ Start Now ▶ Register ▶ Sign-in ▶ Add New ▶ Monitor Type: HTTP(s) ▶ My Settings ▶ API Information (show details)'),
    '#size' => 40,
    '#maxlength' => 40,
    '#required' => TRUE,
  );

  $form['api_settings']['uptime_monitor_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Monitor ID'),
    '#default_value' => $monitor_id,
    '#description' => t('To find your Monitor ID go to') . ' ' . l(t('api.uptimerobot.com/getMonitors?apiKey=FILL-IN-YOUR-API-KEY-HERE'), 'http://api.uptimerobot.com/getMonitors?apiKey=FILL-IN-YOUR-API-KEY-HERE', array(
        'attributes' => array('target' => '_blank'),
        )) . t(', change the last part of the url, reload and copy your monitor ID to here.'),
    '#size' => 10,
    '#maxlength' => 10,
    '#required' => TRUE,
  );

  // Grabbing the uptime ratio once a day is good enough, but leave it up to
  // the site owner to decide. Second option is the actual set cron interval.
  $form['api_settings']['uptime_interval'] = array(
    '#type' => 'radios',
    '#title' => t('Refresh interval'),
    '#options' => array(
      24 * 60 * 60 => t('24 hours (recommended)'),
      0 => format_interval(DRUPAL_CRON_DEFAULT_THRESHOLD, 2) . ' ' . t('(every cron run)'),
    ),
    '#default_value' => variable_get('uptime_interval', 24 * 60 * 60),
    '#description' => t('Saving this form refreshes the uptime ratio instantly, independent from this setting. Last refresh was') . ' ' . t('@interval ago', array('@interval' => format_interval((REQUEST_TIME - $last_refresh)))) . '.',
  );

  // Offering the possibility to check the source of the data.
  $form['api_settings']['raw check'] = array(
    '#type' => 'fieldset',
    '#title' => t('Data check'),
    '#description' => t('Once you saved your credentials, you can check the raw data at') . ':<br />' . l($url, $url, array(
        'attributes' => array('target' => '_blank'),
        )),
  );

  $form['uptime_notice'] = array(
    '#type' => 'fieldset',
    '#title' => t('Copyright notice'),
  );

  $form['uptime_notice']['uptime_notice_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enabled'),
    '#default_value' => variable_get('uptime_notice_enabled', 0),
  );

  // For the examples we use real data.
  // Current domain name without the leading protocol.
  $host = parse_url($GLOBALS['base_url'], PHP_URL_HOST);
  $year = variable_get('uptime_year', '');
  $notice = variable_get('uptime_prepend', 'Copyright') . ' © ' . (($year != date('Y') && !empty($year)) ? $year . '-' . date('Y') : date('Y'));
  $form['uptime_notice']['uptime_url_name'] = array(
    // Create different types of notices to choose from.
    '#type' => 'radios',
    '#title' => t('Choose a notice'),
    '#options' => array(
      $host => '<strong>' . $notice . ' ' . $host . '</strong> ' . t('(default)'),
      variable_get('site_name', '') => '<strong>' . $notice . ' ' . variable_get('site_name', '') . '</strong> ' . t("(preferable if the site name is a person's full name or a company name)"),
      ' ' => '<strong>' . $notice . '</strong> ' . t('(leaving out the designation of owner is not recommended)'),
    ),
    '#default_value' => variable_get('uptime_url_name', $host),
    '#description' => t("'Year of first publication' is not used until entered below, for example © 2009-") . date('Y') . '. ' . t('Save this form to refresh above examples.'),
  );

  $form['uptime_notice']['uptime_year'] = array(
    '#type' => 'textfield',
    '#title' => t('What year was the domain first online?'),
    '#default_value' => variable_get('uptime_year', ''),
    '#description' => t("Leave empty to display only the current year (default). Also if the 'starting year' equals the 'current year' only one will be displayed until next year.<br />To play safe legally, it's best to enter a 'Year of first publication', although copyright is in force even without any notice."),
    '#size' => 4,
    '#maxlength' => 4,
  );

  $form['uptime_notice']['uptime_prepend'] = array(
    '#type' => 'textfield',
    '#title' => t('Prepend text'),
    '#default_value' => trim(variable_get('uptime_prepend', '')),
    '#description' => t("For example 'All images' on a photographer's website."),
  );

  return system_settings_form($form);
}

/**
 * Validate uptime settings submission.
 */
function uptime_admin_settings_validate($form, &$form_state) {
  $limit = $form_state['values']['uptime_monitor_id'];
  if (!is_numeric($limit)) {
    form_set_error('uptime_monitor_id', '<strong>' . t('MONITOR ID SHOULD BE A NUMBER.') . '</strong>');
  }
  // Before 1991 there was no world wide web and the future can't be a
  // 'year of first publication' but it can be left empty.
  $limit = $form_state['values']['uptime_year'];
  if ((!is_numeric($limit) || $limit < 1991 || $limit > date('Y')) && !empty($limit)) {
    form_set_error('uptime_year', '<strong>' . t('INVALID YEAR.') . '</strong>');
  }
}
