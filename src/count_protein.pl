#!/usr/bin/perl -w
use strict;

my $input = shift;
my $output = shift;
my $log = shift;

open IN,"<$input";
open OUT,">$output";
open LOG,">>$log";

print LOG "count the amount of proteins...","\n";

my %hash;
my $num = 0;
while (<IN>) {
	chomp;
	/^(.*)\t(.*)\t(.*)$/;
	if (!exists($hash{$1})) {
		$hash{$1} = 1;
		$num++;
	}
	if (!exists($hash{$2})) {
		$hash{$2} = 1;
		$num++;
	}
}

print OUT $num;
print "\n";

close IN;
close OUT;