<?php
// $Id: home.php,v 1.6 2003-11-26 19:16:07 aegis Exp $
include 'common.inc';
layoutHeader('home', 'home');
?>

<h1>Introduction</h1>

<p>
GLText is a portable font rendering library for C++ OpenGL
applications.  It uses <a
href="http://www.freetype.org/">FreeType2</a> to read and render
high-quality TrueType fonts with a minimal footprint. With just a few
easy lines of C++, you can add gorgeously rendered text to your
graphical applications.
</p>

<p>
GLText is an <a href="http://opensource.org">open source</a> project licensed
under the <a href="http://opensource.org/licenses/lgpl-license.html">LGPL</a>.
Basically this means that you can use and link your application with it
<b>regardless of what license your application uses.</b> If you make changes to
GLText, however, you must make those changes open source under the LGPL.
</p>

<p>
Written with portablility in mind, GLText works on Windows, Linux, and IRIX -
virtually anywhere that FreeType2 supports.
</p>

<h2>News</h2>

<h3>GLText 0.3.1 Released [2003.11.26]</h3>
<p>
GLText 0.3.1, a minor bugfix release, is out.  The automake build
includes OpenGL.h, so you can actually compile it now.
</p>
<p>
Windows users should continue using 0.3.0.
</p>

<h3>GLText 0.3.0 Released [2003.08.04]</h3>
<p>
GLText 0.3.0 has been released. Changes since 0.2.0 include:
</p>

<ul>
 <li>New streaming interface derived from C++ iostreams.  Now you can
     overload <code>operator&lt;&lt;(ostream& out, ...)</code> for your
     custom classes and output them to GLText.  This also improves DLL
     binary compatibility in the streaming interface.</li>
 <li>Renderers always draw with the current position being the upper
     left corner of the text.</li>
 <li>Improved text appearance by using kerning information in TrueType
     files.</li>
 <li>Added getFont() and getHeight() to FontRenderer.</li>
 <li>Added getDPI() to Font.</li>
 <li>When a renderer encounters a \n in the text stream, it drops down
     to the next line rather than trying to draw the glyph for \n.</li>
 <li>Renamed CreateFont to OpenFont, which now takes an optional dpi
     argument.</li>
 <li>Got rid of FontStyle because it was never used anyway.</li>
 <li>Made method calls use the __stdcall convention on Windows so they
     are compatible with COM.</li>
 <li>Added the TEXTURE and MIPMAP renderer types, which support alpha
     blending.</li>
 <li>Removed setFont() from renderers, requiring that they take a font
     on construction.</li>
 <li>Greatly reduced DLL size by removing exceptions and usages of
     iostreams in the library itself.</li>
</ul>


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
