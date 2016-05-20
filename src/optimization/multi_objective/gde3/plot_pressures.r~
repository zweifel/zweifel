
#problem <- "wfg4"

#pdf(paste("forces_",problem,".pdf"))

pdf("rose.pdf")
#par(mfrow=c(2,1))

require(CircStats)

#k <- read.table("all_evaluations")

k <- read.table("all_forces")
k <- k[ k[,1] > -500, ]

#nrow(k)

#print(k)
#print(a)

x <- k[,1]
y <- k[,2]
#x <- rep(-0.002,1000)
#y <- rep(-0.002,1000)

#write.table(atan2(y,x),"aaa")

rose.diag(atan2(y,x), bins = 36, main = 'Stacked Points', pts=F)

dev.off()
