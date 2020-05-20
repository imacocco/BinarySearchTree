import numpy as np
import matplotlib.pyplot as plt

Dir="Benchmark/"
Dir1="Benchmark_unordered/"
def print_averages(Directory,nome_file):
	ordered_tree=np.loadtxt("Benchmark_unordered/Balanced_tree.txt")
	unbalanced_tree=np.loadtxt(Directory+"Unbalanced_tree.txt")
	unordered_map=np.loadtxt(Directory+"Unordered_map.txt")
	ordered_map=np.loadtxt(Directory+"Ordered_map.txt")
	#plt.plot(time_balancing[:,0],time_balancing[:,1]/10**9,"-o")


	plt.errorbar(ordered_tree[:,0]*1000,ordered_tree[:,1],yerr=ordered_tree[:,2],label="Balanced_tree")
	plt.errorbar(unbalanced_tree[:,0]*1000,unbalanced_tree[:,1],yerr=unbalanced_tree[:,2],label="Unbalanced_tree")
	plt.errorbar(ordered_map[:,0],ordered_map[:,1],yerr=ordered_map[:,2],label="Ordered_map")
	plt.errorbar(unordered_map[:,0],unordered_map[:,1],yerr=unordered_map[:,2],label="Unordered_map")
	plt.legend()
	plt.xlabel("Members of the tree/map")
	plt.ylabel("Find time [ns]")
	plt.title(nome_file)
	plt.savefig(Directory+nome_file+"_1.png")
	plt.show()


def main():
	print_averages(Dir,"Ordered_data")

if( __name__ == '__main__' ):
    main()