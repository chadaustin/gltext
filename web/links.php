<?php
// $Id: links.php,v 1.2 2003-02-04 07:27:04 aegis Exp $
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
   newlink('GLTT',  'http://gltt.sourceforge.net'),
   newlink('FTGL',  'http://homepages.paradise.net.nz/henryj/code/index.html#FTGL'),
   newlink('OGLFT', 'http://oglft.sourceforge.net'),
));

layoutFooter();
?>
