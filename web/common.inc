<?php
// $Id: common.inc,v 1.1 2002-06-07 04:55:49 nonchocoboy Exp $
include 'doctype.inc';

$SITE_NAME     = 'GLText';
$SITE_SLOGAN   = 'opengl truetype font renderer';

/**
 * Creates the beginning of a block with a title.
 */
function blockBegin($name)
{
   return <<<EOD
<table width="100%">
 <tr>
  <td class="blockborder" width=2 height=2><img src="clear.gif" width=2 height=2></td>
  <td class="blockborder" width=2 height=2><img src="clear.gif" width=2 height=2></td>
  <td class="blockborder" width=2 height=2><img src="clear.gif" width=2 height=2></td>
 </tr>
 <tr>
  <td class="blockborder" width=2 height=2><img src="clear.gif" width=2 height=2></td>
  <td class="blocktitle">
   <b>$name</b>
  </td>
  <td class="blockborder" width=2 height=2><img src="clear.gif" width=2 height=2></td>
 </tr>
 <tr>
  <td class="blockborder" width=2 height=2><img src="clear.gif" width=2 height=2></td>
  <td class="blockborder" width=2 height=2><img src="clear.gif" width=2 height=2></td>
  <td class="blockborder" width=2 height=2><img src="clear.gif" width=2 height=2></td>
 </tr>
 <tr>
  <td class="blockborder" width=2 height=2><img src="clear.gif" width=2 height=2></td>
  <td class="blockbody">
EOD;
}

/**
 * Creates the end of a block.
 */
function blockEnd()
{
   return <<<EOD
  </td>
  <td class="blockborder" width=2 height=2><img src="clear.gif" width=2 height=2></td>
 </tr>
 <tr>
  <td class="blockborder" width=2 height=2><img src="clear.gif" width=2 height=2></td>
  <td class="blockborder" width=2 height=2><img src="clear.gif" width=2 height=2></td>
  <td class="blockborder" width=2 height=2><img src="clear.gif" width=2 height=2></td>
 </tr>
</table>
EOD;
}


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

function layoutHeader($section, $name)
{
   global $SITE_NAME, $SITE_SLOGAN;

   $html = <<<EOD
<html>

<head>
 <title>$SITE_NAME [$name]</title>
 <link rel="stylesheet" type="text/css" href="default.css">
</head>

<body text="#000000">
 <!-- title -->
 <table width="100%">
  <tr>
   <td class="blockborder" width=2 height=2><img src="clear.gif" width=2 height=2></td>
   <td class="blockborder" width=2 height=2><img src="clear.gif" width=2 height=2></td>
   <td class="blockborder" width=2 height=2><img src="clear.gif" width=2 height=2></td>
  </tr>
  <tr>
   <td class="blockborder" width=2 height=2><img src="clear.gif" width=2 height=2></td>
   <td class="blockbody" align=center>
    <span class="sitetitle">$SITE_NAME</span><br>
    <small>$SITE_SLOGAN</small>
   </td>
   <td class="blockborder" width=2 height=2><img src="clear.gif" width=2 height=2></td>
  </tr>
  <tr>
   <td class="blockborder" width=2 height=2><img src="clear.gif" width=2 height=2></td>
   <td class="blockborder" width=2 height=2><img src="clear.gif" width=2 height=2></td>
   <td class="blockborder" width=2 height=2><img src="clear.gif" width=2 height=2></td>
  </tr>
 </table>

 <p><table width="100%" cellspacing=0 cellpadding=0>
  <tr>

   <!-- Menus -->
   <td width=150 nowrap valign=top>
EOD;

   // create the menu
   $menuitems = array(
         menuItem('introduction',   'index.php',      $section),
         menuItem('documentation',  'docs.php',       $section),
         menuItem('download',       'download.php',   $section),
         menuItem('source',         'source.php',     $section),
         menuItem('people',         'people.php',     $section)
   );

   // Menu
   $html .= blockBegin('Main Menu');
   $html .= menu($menuitems);
   $html .= blockEnd();

   // Sponsors
   $html .= "\n<p>";
   $html .= blockBegin('Sponsors');
   $html .= <<<EOD
<center>
 <a href="http://sourceforge.net/projects/gltext"><img src="http://sourceforge.net/sflogo.php?group_id=55024&type=1" width=88 height=31 border=0 alt="SourceForge Logo"></a>
</center>
EOD;
   $html .= blockEnd();

   $html .= <<<EOD
   </td>
   <td width="6"><img src="clear.gif" width=6 height=1></td>

   <!-- Document body -->
   <td class="docbody" width="100%" valign=top>
EOD;

   echo $html;
}

function layoutFooter()
{
   $html = <<<EOD
   </td>
  </tr>
 </table>

 <!-- copyright and contact -->

 <p><table width="100%">
  <tr>
   <td class="blockborder" width=2 height=2><img src="clear.gif" width=2 height=2></td>
   <td class="blockborder" width=2 height=2><img src="clear.gif" width=2 height=2></td>
   <td class="blockborder" width=2 height=2><img src="clear.gif" width=2 height=2></td>
  </tr>
  <tr>
   <td class="blockborder" width=2 height=2><img src="clear.gif" width=2 height=2></td>
   <td class="blockbody" align=center>
    <small>
    For inquiries, wishes or comments please contact <a href="mailto:nonchocoboy@users.sourceforge.net">nonchocoboy@users.sourceforge.net</a><br>
    GLText is copyright (C) 2002 Ben Scott.
    </small>
   </td>
   <td class="blockborder" width=2 height=2><img src="clear.gif" width=2 height=2></td>
  </tr>
  <tr>
   <td class="blockborder" width=2 height=2><img src="clear.gif" width=2 height=2></td>
   <td class="blockborder" width=2 height=2><img src="clear.gif" width=2 height=2></td>
   <td class="blockborder" width=2 height=2><img src="clear.gif" width=2 height=2></td>
  </tr>
 </table>

</body>
</html>
EOD;

   echo $html;
}
?>
