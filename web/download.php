<?php
// $Id: download.php,v 1.1 2002-06-08 00:43:18 nonchocoboy Exp $
include 'common.inc';
layoutHeader('download', 'download');

/**
 * Creates a new file that is part of a release.
 */
function releaseFile($name, $desc)
{
   return <<<EOD
<tr>
 <td><a href="http://prdownloads.sf.net/gltext/$name">$name</a></td>
 <td>$desc</td>
</tr>
EOD;
}

/**
 * Creates the HTML that is associated with a release.
 */
function release($name, $version, $files)
{
   $html = <<<EOD
<table class="filerelease">
 <tr>
  <td colspan=3 class="filerelease_header">
   <b>$name $version</b>
  <td>
 </tr>
EOD;
   $html .= join("\n", $files);
   $html .= "</table>\n";

   return $html;
}

?>

<h1>Download</h1>
<p>
The current release of GLText is <b>0.1.0</b>. This is a <b>beta</b> release for
testing the design. Download it here as binary or source.
</p>

<h2>Releases</h2>
<?php
echo release('GLText', '0.1.0',
   array(
      releaseFile('gltext-0.1.0.tar.gz',     'Gzipped tarball of the source.'),
      releaseFile('gltext-0.1.0.zip',        'Zip of the source.'),
      releaseFile('gltext-0.1.0-1.i586.rpm', 'RPM for RedHat/Mandrake Linux.'),
      releaseFile('gltext-0.1.0-1.src.rpm',  'Source RPM for RedHat/Mandrake Linux.'),
      releaseFile('gltext-0.1.0.win32.exe',  'Win32 installer.')
   )
);

?>

<h2>CVS</h2>
<p>
Need the latest and greatest, unstable code? Grab the latest copy from the CVS
repository. Instructions for anonymous CVS access are available at:
</p>
<blockquote>
<a href="http://sourceforge.net/cvs/?group_id=55024">http://sourceforge.net/cvs/?group_id=55024</a>
</blockquote>

<?php
layoutFooter();
?>