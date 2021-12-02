from warnings import filters
import matplotlib.pyplot as plt
import scipy.stats as stats
import re

def process_name( name: str ):
    name = name.split( ".txt")
    name = name[ 0 ]
    name = name.split( "/" )
    name = name[ 2 ]
    return name

def read( file_name, filters: list ):
    file = open( file_name )
    text = file.readlines()
    list = []
    for line in text:
        s = line.split( ";" )
        aux = s[ 0 ]

        is_ok = False
        for f in filters:
            if f in aux:
                is_ok = True
                break
        if is_ok:
            list.append( float( s[ 1 ] ) )
    return list

def anova_all( data1, data2 ):
    fvalue, pvalue = stats.f_oneway( data1, data2 )
    print( pvalue )

def make_all( filters:list, png_name:str ):
    instances_grasp = read( "grasp.csv", filters )
    instances_ga = read( "ga.csv", filters )

    plt.xlabel("Algoritmo")
    plt.ylabel("Qualidade da solução")
    plt.boxplot( instances_grasp, labels=["GRASP"], positions=[1], widths=[0.7] )
    plt.boxplot( instances_ga, labels=["GA"], positions=[2], widths=[0.7] )
    plt.savefig( png_name+".png" )
    plt.close()

    print( png_name )
    anova_all( instances_grasp, instances_ga )

make_all( ["p1.", "p2.", "p3."], "lower_instances" )
make_all( ["p2.", "p5."], "upper_instances" )