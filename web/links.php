<?php
// $Id: links.php,v 1.1 2002-06-11 03:28:59 nonchocoboy Exp $
include 'common.inc';
layoutHeader('links', 'links');

function newLink($name, $link, $desc='')
{
   return <<<EOD
<tr>
 <td><b><a href="$link">$name</a></b></td>
 <td>$desc</td>
</tr>
EOD;
}

function linksList($links)
{
   echo "<table class=\"links\">\n";
   echo join("", $links);
   echo "</table>\n";
}

?>

<h1>Links</h1>
<p>
Provided are links to sites that relate to GLText.
</p>

<h2>The Competition</h2>
<?php
linksList(array(
   newlink('GLTT', 'http://gltt.sourceforge.net'),
   newlink('FTGL', 'http://homepages.paradise.net.nz/henryj/code/index.html#FTGL'),
));

layoutFooter();
?>
