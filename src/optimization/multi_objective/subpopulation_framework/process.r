
a <- read.csv("solutions",header=F)

len <- length(a)

#a <- a[,(len-1):(len)]*-1
a <- a[,25:len]*-1

write.table(a,"processed_solutions",col.names=F,row.names=F)
