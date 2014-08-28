library(GOSemSim)

mRNA = read.table(file.choose(),sep="\t")

row = nrow(mRNA)

for (i in 1:row)
{
  gene1 = mRNA[i,1]
  gene2 = mRNA[i,2]
  gene1 = as.character(gene1)
  gene2 = as.character(gene2)

  a = geneSim(gene1, gene2, ont = "BP", organism = "arabidopsis", measure="Wang")
  fun_sim = a[[1]]
  out = paste(gene1,gene2,fun_sim,sep="\t")
  write(x=out,file="GoNetwork_BP_Wang",append=TRUE)

  a = geneSim(gene1, gene2, ont = "MF", organism = "arabidopsis", measure="Wang")
  fun_sim = a[[1]]
  out = paste(gene1,gene2,fun_sim,sep="\t")
  write(x=out,file="GoNetwork_MF_Wang",append=TRUE)

  a = geneSim(gene1, gene2, ont = "CC", organism = "arabidopsis", measure="Wang")
  fun_sim = a[[1]]
  out = paste(gene1,gene2,fun_sim,sep="\t")
  write(x=out,file="GoNetwork_CC_Wang",append=TRUE)

  info = paste(i,gene1,gene2,sep = "-")
  print(info)
}
