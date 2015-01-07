<?php
/**
 * @file
 * Plugin to provide access control based upon a parent term.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t("Taxonomy: term has children"),
  'description' => t('Control access based on whether the term has any children.'),
  'callback' => 'extra_selection_rules_term_has_children_ctools_access_check',
  'default' => array('vid' => array(), 'depth' => 0),
  //'settings form' => 'extra_selection_rules_term_has_children_ctools_access_settings',
  //'settings form validation' => 'extra_selection_rules_term_has_children_ctools_access_settings_validate',
  //'settings form submit' => 'extra_selection_rules_term_has_children_ctools_access_settings_submit',
  'summary' => 'extra_selection_rules_term_has_children_ctools_access_summary',
  'required context' => new ctools_context_required(t('Term'), array('taxonomy_term', 'terms')),
);

/**
 * Check for access.
 */
function extra_selection_rules_term_has_children_ctools_access_check($conf, $context) {
  // As far as I know there should always be a context at this point, but this
  // is safe.
  if (empty($context) || empty($context->data) || empty($context->data->vid) || empty($context->data->tid)) {
    return FALSE;
  }

  return extra_selection_rules_term_has_children($context->data->tid);

}

/**
 * Provide a summary description based upon the checked terms.
 */
function extra_selection_rules_term_has_children_ctools_access_summary($conf, $context) {
  $vocab = taxonomy_vocabulary_load($conf['vid']);

  return t('"@term" has at least one child term', array(
    '@term' => $context->identifier,
  ));
}
