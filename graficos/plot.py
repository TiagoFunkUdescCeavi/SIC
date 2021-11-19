import string
import pandas as pd
import matplotlib.pyplot as plt

def create_graphic( name: string ):
    data = pd.read_csv( name+".csv", sep=";" )
    p = data.plot( x="iteracao", y="valor", label=name )
    plt.xlabel("Iterações")
    plt.ylabel("Qualidade da solução")
    fig = p.get_figure()
    fig.savefig( name+".png" )
    plt.close()

create_graphic( "5_3_m" )
create_graphic( "5_3_w" )
create_graphic( "5_4_m" )