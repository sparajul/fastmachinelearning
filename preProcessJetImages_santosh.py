import uproot as up 
import numpy as np
#from skimage import transform
from pylab import figure, cm
import matplotlib.pyplot as plt
import matplotlib

# Find the longest subarray with consequent terms. 
# The datasets has been preprocessed to return 200 jet constituents. If there are jets that has less than 200 subconsequents the arrays are padded with mean of the eta,phi,energy constituents. 


# This function returns the index at which a constant subarray starts, using a sliding window algorithm

def getNonDuplicateSubArrayMaxIdx(array):
    # Implemntation using two pointer algorithm technique
    left=0
    val = array[left]
    for right in range(1,len(array)):
        while  val != array[right]:
            left +=1
            val = array[left]
        
    return left


def translate(jet_eta,jet_phi, arr_clusEta, arr_clusPhi,idx):
    tmp_clusEta = arr_clusEta
    tmp_clusPhi = arr_clusPhi

    for i,e in enumerate(arr_clusPhi):
         tmp_clusPhi[i] = extend_phi(tmp_clusPhi[i], jet_phi)

    for i,e in enumerate(arr_clusEta):
        tmp_clusEta[i] = arr_clusEta[i] - jet_eta
        tmp_clusPhi[i] = arr_clusPhi[i] - jet_phi

    return (tmp_clusEta, tmp_clusPhi)

def extend_phi(phi, jet_phi):
    """
    If a jet center is close to either 0 or 2*pi, its constituents could be on the other side
    of the periodicity line. This takes care of this problem by remapping phi to be either
    above 2*pi or below zero.
    """
    if abs(jet_phi + np.pi)<1.: # phi close to -pi
        return phi-2*np.pi*int(abs(phi-np.pi) <1-abs(jet_phi + np.pi))
    elif abs(jet_phi - np.pi)<1.: # phi close to pi
        return phi+2*np.pi*int(abs(-phi-np.pi) < 1-abs(jet_phi - np.pi)) 
    else: 
        return phi



#def pixelize(data, edges, cutoff=0.1):
#    """Return eta-phi histogram of transverse energy deposits.
#    Optionally set all instensities below cutoff to zero.
#    """
#    image, _, _ = np.histogram2d(
#        data[0],data[1],   #Eta and phi
#        bins=(edges[0], edges[1]), # bin edges #
#        weights=data[2] * (data[2] > cutoff)) # bin weights with cutoff
#    return image


def pixelize(data, edges, cutoff=0.1, center_max_energy=True):
    """Return eta-phi histogram of transverse energy deposits.
    Optionally set all intensities below cutoff to zero.
    """
    image, _, _ = np.histogram2d(
        data[0], data[1],   # Eta and phi
        bins=(edges[0], edges[1]), # Bin edges
        weights=data[2] * (data[2] > cutoff)) # Bin weights with cutoff
    if center_max_energy:
        # Shift the image so that the maximum energy deposit is at the center
        max_eta, max_phi = np.unravel_index(image.argmax(), image.shape)
        shift_eta = edges[0][int(edges[0].shape[0] / 2)] - edges[0][max_eta]
        shift_phi = edges[1][int(edges[1].shape[0] / 2)] - edges[1][max_phi]
        image = np.roll(image, int(shift_eta / (edges[0][1] - edges[0][0])), axis=0)
        image = np.roll(image, int(shift_phi / (edges[1][1] - edges[1][0])), axis=1)
    return image



def getJetImages(df):
    eta = noTranslate(df,['AntiKt10LCTopoLeadJets_clus_calEta','AntiKt10LCTopoLeadJets_clus_calPhi'])[0]
    phi = noTranslate(df,['AntiKt10LCTopoLeadJets_clus_calEta','AntiKt10LCTopoLeadJets_clus_calPhi'])[1]
    eng = df.AntiKt10LCTopoLeadJets_clus_calE.values
    
    edges = pixel_edges()
    li_images = []
    for i in range(eta.shape[0]):
        li_images.append(pixelize([eta[i],phi[i],eng[i]],edges))
    return li_images


def pixel_edges(jet_size=1.0, pixel_size=(0.2, 0.2), border_size=0.5):
    """Return pixel edges required to contain all clusters.
    border_size is interpreted as a fraction of the jet_size
    """
    im_edge = (1. + border_size) * jet_size
    return (np.arange(-im_edge, im_edge+pixel_size[0], pixel_size[0]), np.arange(-im_edge, im_edge+pixel_size[1], pixel_size[1]))



def createImage(data, edges, cutoff=0.1):
    """Return eta-phi histogram of transverse energy deposits.
    Optionally set all instensities below cutoff to zero.
    """
    image, _, _ = np.histogram2d(
        data[0],data[1],
        bins=(edges[0], edges[1]),
        weights=data[2] * (data[2] > cutoff))
    return image 

def normalize(histo, multi=255):
    """
    Normalize picture in [0,multi] range, with integer steps. E.g. multi=255 for 256 steps.
    """
    return (histo/np.max(histo)*multi).astype(int)


import argparse

parser = argparse.ArgumentParser()
parser.add_argument('--quark',action='store_true')
parser.add_argument('--gluon', action='store_true')
parser.add_argument('--ztt', action='store_true')
parser.add_argument('--print', action='store_true')
args = parser.parse_args()


#gluon_events   = up.open("/data/rohin/ttbar_Akt10.root")['ntuple']
quark_events = up.open("/data/santosh/qgdata/multijet_quark_smallpt.root")['ntuple']
#quark_events   = up.open("/data/rohin/ztt_Akt10.root")['ntuple']
#qcd_events   = up.open("/data/rohin/multijet_j1.root")['ntuple']
gluon_events = up.open("/data/santosh/qgdata/multijet_gluon_smallpt_events.root")['ntuple']

if args.quark:
    arrays = quark_events.arrays()
if args.gluon:
    arrays = gluon_events.arrays()
if args.ztt :
    arrays = ztt_events.arrays()

pack = zip(arrays[b'AntiKt10LCTopoLeadJets_partonTruthLabel'],arrays[b'AntiKt10LCTopoLeadJets_pt'], arrays[b'AntiKt10LCTopoLeadJets_eta'], arrays[b'AntiKt10LCTopoLeadJets_phi'], arrays[b'AntiKt10LCTopoLeadJets_clus_calEta'], arrays[b'AntiKt10LCTopoLeadJets_clus_calPhi'], arrays[b'AntiKt10LCTopoLeadJets_clus_calE'])

image_li = []
for i, (trth,jet_pt,jet_eta,jet_phi, clus_eta, clus_phi, clus_E) in enumerate(pack):
    idx      = getNonDuplicateSubArrayMaxIdx(clus_eta)
    clus_eta = clus_eta[:idx]
    clus_phi = clus_phi[:idx]
    clus_E   = clus_E[:idx]
    max_idx=np.argsort(clus_E)[-1]


    clus_eta,clus_phi = translate(jet_eta,jet_phi,clus_eta,clus_phi,max_idx)
    etaedges,phiedges = pixel_edges()

    img = createImage((clus_eta,clus_phi,clus_E), (etaedges,phiedges), )
    img = normalize(img)
    image_li.append(img)

img = np.average(image_li,axis=0)
plt.imshow(img, norm=matplotlib.colors.LogNorm())
if args.gluon:
    plt.savefig("average_gluon.png")
if args.quark:
    plt.savefig("average_quark.png")

#if args.print:
#    plt.figure().clear() 
#    rand = np.random.randint(10,len(image_li)-10)
#    low  = rand -5
#    high = rand +5
#    for i in range(low,high):
#        img = image_li[i]
#        plt.imshow(img, norm=matplotlib.colors.LogNorm())
#        plt.savefig('img-rndm-%d.png'%i)

if args.quark:
    np.savez_compressed('quark_leading_jet.npz', image_li)
if args.gluon:
    np.savez_compressed('gluon_leading_jet.npz', image_li)
if args.ztt:
    np.savez_compressed('ztt_leading_jet.npz',image_li)


