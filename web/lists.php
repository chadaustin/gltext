<?php
// $Id: lists.php,v 1.1 2002-06-08 01:33:35 nonchocoboy Exp $
include 'common.inc';
layoutHeader('mailing lists', 'mailing lists');

function mailinglist($name, $forumid, $desc)
{
   $listname = "gltext-$name";
   return <<<EOD
<tr>
 <td><a href="mailto:$listname">$listname</a></td>
 <td>[<a href="http://lists.sourceforge.net/lists/listinfo/$listname">subscribe</a>]<br>
     [<a href="http://sourceforge.net/mailarchive/forum.php?forum_id=$forumid">archives</a>]</td>
 <td>$desc</td>
</tr>
EOD;
}

function lists($mailinglists)
{
   echo "<table class=\"mailinglist\">\n";
   echo join("", $mailinglists);
   echo "</table>\n";
}
?>

<h1>Mailing Lists</h1>
<p>
The GLText mailing lists are available for you to help make you experience with
using or developing the library easier.
</p>

<?php
lists(array(
      mailinglist('announce', '12345', 'Announcements and news related to GLText. This '.
                                       'low volume list is for those users who want to '.
                                       'know when the next release or updates are available.'),
      mailinglist('users', '12345',    'Information and discussion related to using GLText.'),
      mailinglist('devel', '12345',    'Discussion amongst the developers working on GLText.'),
      mailinglist('commits', '12345',  'Notification of changes to the CVS respository. This '.
                                       'may be high volume at times of heavy development.')
));

layoutFooter();
?>
