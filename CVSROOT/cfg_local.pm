# $FreeBSD: CVSROOT/cfg_local.pm,v 1.11 2001/11/30 14:26:57 joe Exp $

####################################################################
####################################################################
# This file contains local configuration for the CVSROOT perl
# scripts.  It is loaded by cfg.pm and overrides the default
# configuration in that file.
#
# It is advised that you test it with
#     'env CVSROOT=/path/to/cvsroot perl -cw cfg.pm'
# before you commit any changes.  The check is to cfg.pm which
# loads this file.
####################################################################
####################################################################

#$CHECK_HEADERS = 1;
#$IDHEADER = 'FreeBSD';
#$UNEXPAND_RCSID = 1;

%TEMPLATE_HEADERS = (
	"Reviewed by"		=> '.*',
	"Submitted by"		=> '.*',
	"Obtained from"		=> '.*',
	"Approved by"		=> '.*',
	"SF Bug #"		=> '\d+',
);

# don't store a local commit summary
@LOG_FILE_MAP = ();

$MAILCMD = "/usr/lib/sendmail -odb -oem";
$MAIL_BRANCH_HDR  = "X-GLText-CVS-Branch";
$ADD_TO_LINE = 1;

$MAILADDRS = 'gltext-commits@lists.sourceforge.net';

@COMMIT_HOSTS = ();

$MAIL_TRANSFORM = sub {
   add_viewcvs_entry("http://cvs.sourceforge.net/cgi-bin/viewcvs.cgi/gltext",
                     '', @_);
};

# Sanity check to make sure we've been run through the wrapper and are
# now primary group 'ncvs'.
#
#$COMMITCHECK_EXTRA = sub {
#	my $GRP=`/usr/bin/id -gn`;
#	chomp $GRP;
#	unless ( $GRP =~ /^ncvs$/ ) {
#		print "You do not have group ncvs (commitcheck)!\n";
#		exit 1;	# We could return false here.  But there's
#			# nothing to stop us taking action here instead.
#	}
#	return 1;
#};

# Wrap this in a hostname check to prevent mail to the FreeBSD
# list if someone borrows this file and forgets to change it.
#my $hostname = `/bin/hostname`;
#die "Can't determine hostname!\n" if $? >> 8;
#chomp $hostname;
#if ($hostname =~ /^freefall\.freebsd\.org$/i) {
#	my $meister;
#
#	$MAILADDRS='cvs-committers@FreeBSD.org cvs-all@FreeBSD.org';
#	$MAILADDRS = 'cvs@FreeBSD.org' if $DEBUG;
#
#	@COMMIT_HOSTS = qw(freefall.freebsd.org);
#}


#@LOG_FILE_MAP = (
#	'CVSROOT'	=> '^CVSROOT/',
#	'distrib'	=> '^distrib/',
#	'doc'		=> '^doc/',
#	'ports'		=> '^ports/',
#	'projects'	=> '^projects/',
#	'www'		=> '^www/',
#
#	'bin'		=> '^src/bin/',
#	'contrib'	=> '^src/contrib/',
#	'eBones'	=> '^src/eBones/',
#	'etc'		=> '^src/etc/',
#	'games'		=> '^src/games/',
#	'gnu'		=> '^src/gnu/',
#	'include'	=> '^src/include/',
#	'kerberosIV'	=> '^src/kerberosIV/',
#	'lib'		=> '^src/lib/',
#	'libexec'	=> '^src/libexec/',
#	'lkm'		=> '^src/lkm/',
#	'release'	=> '^src/release/',
#	'sbin'		=> '^src/sbin/',
#	'share'		=> '^src/share/',
#	'sys'		=> '^src/sys/',
#	'tools'		=> '^src/tools/',
#	'usrbin'	=> '^src/usr\.bin/',
#	'usrsbin'	=> '^src/usr\.sbin/',
#	'user'		=> '^src/',
#
#	'other'		=> '.*'
#);

# For some reason this file doesn't inherit the add_veiewcvs_entry function from
# the calling package cfg.pm
sub add_viewcvs_entry
{
   my $cgi_url   = shift;
   my $www_repos = shift;
   my @input     = @_;
   my @revs      = ();
   my @output    = ();

   while ( 1 )
   {
      my $line = shift(@input);
      last unless defined($line);

      push(@output, "$line");
      last if $line =~ /^\s*Revision\s*Changes\s*Path\s*$/;
   }

   foreach ( @input )
   {
      push(@output, "$_");
      push(@revs, "$_");
   }

   push(@output, '');

   my $skip = 0;
   foreach ( @revs )
   {
      # The revision block is terminated with an empty line.
      $skip = 1 if $_ =~ /^\s*$/;

      next if $skip;

      my ($rev, $add, $sub, $file, $status) = split;

      $rev =~ /(?:(.*)\.)?([^\.]+)\.([^\.]+)$/;
      my ($base, $r1, $r2) = ($1, $2, $3);
      my $prevrev = "";
      if ( $r2 == 1 )
      {
         $prevrev = $base;
      }
      else
      {
         $prevrev = "$base." if $base;
         $prevrev .= "$r1." . ($r2 - 1);
      }

      my $baseurl = "$cgi_url/$file";
      my $extra;

      if ( defined($status) )
      {
         $rev   = $prevref if $status =~ /dead/;
         $extra = "?rev=$rev&content-type=text/plain";
      }
      else
      {
         $extra = ".diff?r1=$prevrev&r2=$rev&diff_format=h";
      }

      push(@output, "$baseurl$extra$www_repos");
   }

   return @output;
}

1; # Perl requires all modules to return true.  Don't delete!!!!
#end
