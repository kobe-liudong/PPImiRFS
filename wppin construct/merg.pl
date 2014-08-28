#!/usr/bin/perl -w
use strict;

my $input1 = shift;
my $input2 = shift;
my $input3 = shift;
my $output = shift;

open IN1,"<$input1";
open IN2,"<$input2";
open IN3,"<$input3";
open OUT,">$output";

my @go1 = <IN1>;
my @go2 = <IN2>;
my @go3 = <IN3>;

for (my $i = 0; $i < 14 ; ++$i) {
	chomp $go1[$i];
	chomp $go2[$i];
	chomp $go3[$i];

	my @temp1 = split "	",$go1[$i];
	my @temp2 = split "	",$go2[$i];
	my @temp3 = split "	",$go3[$i];

	$temp1[2] =~ tr/[NA]/[0.0]/;
	$temp2[2] =~ tr/[NA]/[0.0]/;
	$temp3[2] =~ tr/[NA]/[0.0]/;

    my $member = $temp1[2]*$temp1[2]+$temp2[2]*$temp2[2]+$temp3[2]*$temp3[2];
	my $denominator = $temp1[2]+$temp2[2]+$temp3[2];
	my $merg;
	if ($denominator == 0) {
		$merg = 0;
	}
	else {
		$merg = $member/$denominator;
	}

    $merg = sprintf "%.6f",$merg;
	print OUT $temp1[0],"	",$temp1[1],"	",$merg,"\n";

    print $i+1,"\n";
}

close IN1;
close IN2;
close IN3;
close OUT;