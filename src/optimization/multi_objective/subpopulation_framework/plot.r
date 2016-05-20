
require("eaf")

png("plot.png", width=1000, height=1000)
#pdf("plot.pdf")

#i <- read.csv("results/wfg1")
i <- read.csv("solutions")
#i <- read.csv("../gde3/solutions")
#i <- i[,7:8]
i <- i[,25:26]
i <- i*-1

#OFFICIAL WFG TOOLKIT
#p <- read.table("../benchmarks/wfg5_20_4")
p <- read.table("/tmp/wfg8_20_4")
#p <- read.table("../benchmarks/wfg8")
#p <- read.table("/tmp/bbb")

#PISA FRAMEWORK
#k <- read.table("../benchmarks/wfg1_nsga2")
#k <- read.table("../benchmarks/wfg1_nsga2")
#k <- k[2:3]

#JMETAL FRAMEWORK
#k <- read.table("../jmetal/nsga2/wfg1")
#k <- read.table("../jmetal/NSGAII/WFG1")
#k <- read.table("../jmetal/GDE3/WFG1")
#k <- read.csv("../jmetal/GDE3/results")
#k <- k*-1

#OWN GDE3
#k <- read.csv("../gde3/results/25000_wfg1")
#k <- read.csv("solutions")
#k <- read.csv("../gde3/solutions")
#k <- k[,7:8]
#k <- k[,25:26]
k <- k*-1

plot(p, xlim=c(0,4),ylim=c(0,4),col="yellow")
#points(k,col="blue")
points(i,col="red")


#eafplot(i)

dev.off()
