<?php
// $Id: dev.php,v 1.1 2002-06-08 01:08:49 nonchocoboy Exp $
include 'common.inc';
layoutHeader('development', 'development');

function resource($name, $link, $desc)
{
   return <<<EOD
<tr>
 <td><a href="$link">$name</td>
 <td>$desc</td>
</tr>
EOD;
}

function resourceList($resources)
{
   echo "<table class=\"resource\">\n";
   echo join("", $resources);
   echo "</table>\n";
}

?>

<h1>Development</h1>
<p>
GLText is always looking for developers to help out. If you're interested, drop
us a line at <a href="mailto:gltext-devel@lists.sourceforge.net">gltext-devel@lists.sourceforge.net</a>.
</p>

<h2>Resources</h2>
<p>
Here are some resources useful for GLText developers and hackers.
</p>
<?php

resourceList(array(
   resource('Coding Style', 'codingstyle.php',
      'Guidelines you need to follow if you are adding code to the project.'),
   resource('Project Page', 'http://sf.net/projects/gltext',
      'The GLText project page at <a href="http://sf.net">SourceForge</a>.'),
   resource('CVS Viewer', 'http://cvs.sf.net/cgi-bin/viewcvs.cgi/gltext',
      'A browsable view into the CVS repository at <a href="http://sf.net">SourceForge</a>.'),
   resource('FreeType', 'http://freetype.sf.net/index2.html',
      'The FreeType Web site.')
));


layoutFooter();
?>
