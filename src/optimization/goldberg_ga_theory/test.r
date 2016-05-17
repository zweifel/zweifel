#plot(data)

#v <- c(-5,-2,0,2,5)

#plot(tanh(v))

#curve(tanh(x), from=-100, to=100, add=TRUE)


########################
#x <- seq(-4,4,length=200)
#y <- x^2
#z <- tanh(x)

#plot(x,y,type="l")
#lines(x,x*tanh(x),lty=2)
#######################

name <- "data"

data <- read.table(name, header=T)

png("output.png")

plot(0, type = "n", main = "Plot Title", ylab = "Crossover", xlab = "Selection Pressure", xlim = c(0,1), ylim = c(0,1))
grid()                              # add grid
points(data[,2], data[,1], type="p", pch=19)  # draw first dataset
#lines(data[,1], data[,3], lty = 2)  # draw second dataset
#legend("topright", c("first dataset", "second dataset"), lty = c(1, 2) )

dev.off()

