import string
import pandas as pd
import matplotlib.pyplot as plt
from pandas.core.frame import DataFrame

def read( file_name ):
    file = open( file_name )
    text = file.readlines()
    iterations = []
    values = []
    for line in text:
        s = line.replace('\n','').split( ";" )
        if s[ 0 ] == "iteracao" and s[ 1 ] == "valor":
            continue
        iterations.append( int( s[ 0 ] ) )
        values.append( float( s[ 1 ] ) )
    return iterations, values

def seila( iterations, values ):
    new_iterations = []
    new_values = []

    if iterations[ 0 ] != 1:
        for i in range( iterations[ 0 ] ):
            new_iterations.append( i )
            new_values.append( 0.0 )
    
    for i in range( 1, len( iterations ) ):
        diff = iterations[ i ] - iterations[ i-1 ]

        for j in range( iterations[ i-1 ], iterations[ i-1 ] + diff ):
            new_iterations.append( j )
            new_values.append( values[ i-1 ] )
    return new_iterations, new_values

def create_graphic( name: string ):
    iterations, values = read( name + ".csv" )
    iterations, values = seila( iterations, values )
    plt.plot( iterations, values )

plt.xlabel("Iterações")
plt.ylabel("Qualidade da solução")

create_graphic( "4_2_m_grasp" )
create_graphic( "4_2_m_ga" )
# create_graphic( "5_4_m" )

plt.savefig( "4_2_m.png" )
plt.close()