<?php
// $Id: lists.php,v 1.3 2002-06-15 22:27:22 nonchocoboy Exp $
include 'common.inc';
layoutHeader('mailing lists', 'mailing lists');

function mailinglist($name, $forumid, $desc)
{
   $listname = "gltext-$name";
   $listaddr = "$listname@lists.sourceforge.net";
   return <<<EOD
<tr>
 <td><a href="mailto:$listaddr">$listname</a></td>
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
      mailinglist('announce', '9700',  'Announcements and news related to GLText. This '.
                                       'low volume list is for those users who want to '.
                                       'know when the next release or updates are available.'),
      mailinglist('users',    '9699',  'Information and discussion related to using GLText.'),
      mailinglist('devel',    '9698',  'Discussion amongst the developers working on GLText.'),
      mailinglist('commits',  '9624',  'Notification of changes to the CVS respository. This '.
                                       'may be high volume at times of heavy development.')
));

layoutFooter();
?>
