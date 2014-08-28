/*
 *  PPImiRFS v1.0
 *  Inference of the functional similarity score of microRNAs
 *  
 *  Copyright (C) 2014  Dong Liu
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 * 
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

PPImiRFS 1.0 Help file
Author : Dong Liu
kobe_liudong@mail.dlut.edu.cn
2014

=====DESCRIPTION=====
Plant microRNAs (miRNAs) play critical roles in response to abiotic and biotic stresses. But the functions of most plant miRNAs are still unknown. Some methods have been proposed to infer the potential functions of miRNAs by comparing the functional similarities among miRNAs.
PPImiRFS is based on the protein-protein interaction network with GO semantic similarity weighting and graph theoretic property.

PPImiRFS works in three steps: 
- Input one pair of predicted miRNAs
- Extract the target gene set of each miRNA of the predicted miRNA pair
- Compute the functional similarity score of the two target gene sets, namely, the functional similarity score of the two miRNAs

=====REQUIRED SOFTWARES=====
- Activeperl installed (you can dowload it at http://www.perl.org/get.html)
- R installed (you can dowload it at http://www.r-project.org/)

=====USAGE=====
MiRdup may be executed in this way:

- PPImiRFS.exe -i predicted_miRNA_pairs.txt -p wppin.txt -o result.txt

The file predicted_miRNA_pairs.txt must be in tabbed format, separated by tabulations (\t): 
miRNA1	miRNA2
miRNA3	miRNA4
...

The file wppin.txt must be in tabbed format, separated by tabulations (\t): 
gene1	gene2	score
gene3	gene4	score
...

This software includes the target genes of Arabidopsis thaliana miRNAs and the weighted protein-protein interaction network of Arabidopsis thaliana
This software provides the R program and Perl program to construct the weighted protein-protein interaction network of other species

=====PPImiRFS OPTIONS=====

-i
    Predicted miRNA pairs file

-p
    Weighted protein-protein interaction network file

-o
    The functional similarity scores of predicted miRNA pairs
    
-h
    Help information 
    
-v
    version information
    	
=====OUTPUT FILES=====
The result of functional similarity scores is in tabbed format, separated by tabulations (\t):
miRNA1	miRNA2	score
miRNA3	miRNA4	score
...

=====REFERENCES=====
miRbase
Griffiths-Jones, S., Grocock, R. J., van Dongen, S., Bateman, A. & Enright, A. J. (2006), ‘mirbase: microrna sequences, targets and gene nomenclature’, Nucleic Acids Res 34(Database issue), D140–4.
http://www.mirbase.org/