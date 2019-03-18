tiff("seq_heatmap.tiff", height = 4, width = 4, units = 'in', res=1600)

mat <- read.csv(".\\seq.csv", sep=",")
matrix <- data.matrix(mat)
par(cex.main=0.5)
mat_heatmap <- heatmap(matrix, Rowv=NA, Colv=NA, col = heat.colors(256), scale="column",labRow = FALSE, labCol = FALSE,margins=c(1,1),main="\nHeatmap for generated Random Numbers(Sequential)")

dev.off()
