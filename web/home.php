<?php
// $Id: home.php,v 1.3 2002-12-23 23:44:40 nonchocoboy Exp $
include 'common.inc';
layoutHeader('home', 'home');
?>

<h1>Introduction</h1>

<p>
GLText is a highly portable font rendering library for OpenGL applications
usable from C++ applications. It uses FreeType2 to read and render high quality
TrueType fonts with a minimal footprint. With just a few easy lines of C++, you
can add gorgeously rendered text to your graphical applications.
</p>

<p>
GLText is an <a href="http://opensource.org">open source</a> project licensed
under the <a href="http://opensource.org/licenses/lgpl-license.html">LPGL</a>.
Basically this means that you can use and link your application with it
<b>regardless of what license your application uses.</b> If you make changes to
GLText, however, you must make those changes open source under the LGPL.
</p>

<p>
Written with portablility in mind, GLText works on Windows, Linux, and IRIX -
virtually anywhere that FreeType2 supports.
</p>

<h2>News</h2>

<h3>GLText 0.2.0 Released [2002.12.23]</h3>
<p>
GLText 0.2.0 has been released just in time for Christmas. Here are the major
changes since the last release.
</p>

<ul>
 <li>New FontStream interface for an STL iostream-like interface to writing text
     to the screen.</li>
 <li>All objects are now ref-counted. Use the XXXPtr classes to have the
     reference counting managed for you. You won't have to worry about when to
     delete GLText objects any more.</li>
 <li>You can now query a renderer for the width a string will be when
     rendered.</li>
</ul>

<h3>GLText 0.1.0 Released [2002.07.04]</h3>
<p>
GLText 0.1.0 has been released. Here are the major features:
</p>

<ul>
 <li>Supports any TrueType font using FreeType2 as the backend.</li>
 <li>Anti-aliased pixmap rendering.</li>
 <li>Fast aliased bitmap rendering.</li>
 <li>Doxygen API documentation.</li>
</ul>

<?php
layoutFooter();
?>
