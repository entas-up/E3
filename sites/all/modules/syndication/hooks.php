<?php
/**
 * Allows modules to add RSS feeds to the Syndication page
 *
 * Any module can export boxes to the syndication page. You do so
 * by creating a <i>modulename</i>_syndication function which returns
 * an associative array of boxes, much like the block module. Each box
 * in the array requires <i>subject</i> and <i>content</i> fields. 
 */
function hook_syndication() {
  // Creating the first box
  $box[0]["subject"] = t('Name of Feed');
  $box[0]["content"] = "HTML to show on Syndication page";

  // Lets create a one box more
  $box[1]["subject"] = t('Name of other Feed');
  $box[2]["content"] = "HTML to show on Syndication page";
  
  return $box;
}