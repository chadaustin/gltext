<?php
// $Id: people.php,v 1.3 2003-08-05 03:22:09 aegis Exp $
include 'common.inc';
layoutHeader('people', 'people');

function person($name, $link, $title)
{
   return <<<EOD
<tr>
 <td class="person"><b><a href="$link">$name</a></b></td>
 <td class="person">$title</td>
</tr>
EOD;
}

function personList($people)
{
   echo "<table class=\"person_list\">\n";
   echo join("", $people);
   echo "</table>\n";
}

?>

<h1>People</h1>
<p>
GLText is developed by the following people. Be nice to them. ;) Remember that
the best way to ask questions is to email the mailing list,
<a href="mailto:gltext-devel@lists.sourceforge.net">gltext-devel@lists.sourceforge.net</a>,
rather than a developer directly.
</p>

<?php

personList(array(
   person('Ben Scott', 'mailto:nonchocoboy@users.sourceforge.net',
      'Developer and Project Manager'),
   person('Chad Austin', 'mailto:aegis@aegisknight.org',
      'Developer')
));

layoutFooter();
?>
