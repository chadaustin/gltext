%define name gltext
%define version 0.3.0
%define release 1

Summary: an OpenGL TrueType font rendering API
Name: %{name}
Version: %{version}
Release: %{release}
Source: %{name}-%{version}.tar.gz
License: GNU LGPL
Group: Development/Libraries
BuildRoot: %{_tmppath}/%{name}-buildroot
Prefix: %{_prefix}
Vendor: Ben Scott <nonchocoboy@users.sourceforge.net>
Packager: Ben Scott <nonchocoboy@users.sourceforge.net>
URL: http://gltext.sourceforge.net

%description
GLText is a font rendering library for OpenGL applications usable from C++
applications. It uses FreeType to read and render high-quality TrueType fonts
with a minimal footprint.

%prep
%setup

%build
configure --prefix=$RPM_BUILD_ROOT/usr
gmake

%install
gmake install

%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root)
/usr/include/gltext.h
/usr/lib/libgltext-%{version}.so
/usr/lib/libgltext.a
/usr/lib/libgltext.la
/usr/lib/libgltext.so
