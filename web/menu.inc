<?php
// $Id: menu.inc,v 1.1 2002-06-07 23:56:39 nonchocoboy Exp $

/**
 * Makes a menu item within the menu.
 */
function menuItem($name, $link, $curSection)
{
   $selected = $name == $curSection;
   $html = '<strong>&middot;</strong> ';
   if ($selected)
   {
      $html .= '<b>';
   }
   $html .= "<a href=\"$link\">$name</a>";
   if ($selected)
   {
      $html .= '</b>';
   }
   return $html;
}

/**
 * Makes a menu from a list of menu items.
 */
function menu($items)
{
   // put the menu items together, each on its own line
   return join("<br>\n", $items);
}

/**
 * Builds the HTML for the common menu. Any menu items whose name matches the
 * currentSection will be highlighted.
 */
function layoutMenu($currentSection)
{
   // create the menu
   $menuitems = array(
         menuItem('home',           'home.php',       $currentSection),
         menuItem('documentation',  'docs.php',       $currentSection),
         menuItem('download',       'download.php',   $currentSection),
         menuItem('development',    'dev.php',        $currentSection),
         menuItem('mailing lists',  'lists.php',      $currentSection),
         menuItem('links',          'links.php',      $currentSection),
         menuItem('people',         'people.php',     $currentSection)
   );

   return menu($menuitems);
}

?>
