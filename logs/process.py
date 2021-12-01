import matplotlib.pyplot as plt
import scipy.stats as stats

def process_name( name: str ):
    name = name.split( ".txt")
    name = name[ 0 ]
    name = name.split( "/" )
    name = name[ 2 ]
    return name

def read( file_name ):
    file = open( file_name )
    text = file.readlines()
    list = []
    for line in text:
        s = line.split( ";" )
        list.append( float( s[ 1 ] ) )
    return list

def anova_all( data1, data2 ):
    fvalue, pvalue = stats.f_oneway( data1, data2 )
    print( pvalue )

instances_grasp = read( "grasp.csv" )
instances_ga = read( "ga.csv" )

plt.xlabel("Algoritmo")
plt.ylabel("Qualidade da solução")
plt.boxplot( instances_grasp, labels=["GRASP"], positions=[1], widths=[0.7] )
plt.boxplot( instances_ga, labels=["GA"], positions=[2], widths=[0.7] )
plt.savefig( "algorithms.png" )
plt.close()

anova_all( instances_grasp, instances_ga )