# -*- coding: utf-8 -*-
from lib_openimu.algorithm import Algorithm
from lib_openimu import schemas
from bson.objectid import ObjectId
from math import sqrt
import numpy as np
#import matplotlib.pyplot as plt

class stepCounter(Algorithm):
    #This is the base threshold between each peak on the x axis
    spacing = 14

    def __init__(self):
        super(stepCounter, self).__init__()
        self.description = "Compteur de pas"
        self.author = "L'équipe d'OpenIMU"
        self.name = "Compteur de pas"
        self.filename = "stepCounter"
        self.details = "Le compteur de pas permet de détecter le nombre de pas effectué sur un enregistrement, l'algorithme se base la magnitude des accélérations en X,Y et Z."

        self.params.uuid = 0
        self.infos.uuid = "Identifiant unique d'un enregistrement"
        self.possible.uuid = "Un identifiant ObjectId"

    def run(self):
        """
        Algorithme pour  un compteur de pas
        Étape 1 : Importer les données de l'enregistrement provenant de la base de données
        Étape 2 : Calculater la moyenne mobile sur les données
        Étape 3 : Identifier les sommets séparer par un certain intervale et une limite
        :return: Rien par défaut, mais self.ouput et quand même utile à retourner
        """
        schema = schemas.Sensor(many=True)
        ref = self.database.db.accelerometres.find({'ref': str(self.params.uuid)})
        data, errors = schema.dump(ref)

        if len(data)/2 < self.spacing : self.spacing = round(len(data)/2 - 1)

        filtereddata = self.moving_average(data)
        peaks = self.find_peaks(filtereddata,spacing = self.spacing,limit = 8250)

        # If you have imported matplotlib, you can decomment the following section. It block the cpu.
        #t = np.linspace(0, 1, len(filtereddata))
        #plt.plot(t,filtereddata)
        #plt.plot(t[peaks],filtereddata[peaks],'ro')
        #plt.show()

        self.output.result = len(peaks)

        return self.output

    def moving_average(self,data):
        magnetude = [sqrt(i.get('x')**2 + i.get('y')**2 + i.get('z')**2)
                         for i in data]

        N = self.spacing
        V = np.ones((N,))/N

        result = np.convolve(magnetude, V, mode='valid')[(N-1):]
        return  result

    def find_peaks(self,data,spacing = 1, limit = None):
        """Identifier les sommets dans les données qui sont séparé par un espacement et supérieur à une limite.
        :param data: valeur
        :param spacing: espacement minimum avant le prochain sommets (devrais être 1 ou plus)
        :param limit: sommets devrais avoir un sommets supérieurs ou égal
        :return: Liste des position des sommets
        """
        len = data.size
        x = np.zeros(len + 2 * spacing)
        x[:spacing] = data[0] - 1.e-6
        x[-spacing:] = data[-1] - 1.e-6
        x[spacing:spacing + len] = data
        peak_candidate = np.zeros(len)
        peak_candidate[:] = True
        for s in range(spacing):
            start = spacing - s - 1
            h_b = x[start: start + len]  # before
            start = spacing
            h_c = x[start: start + len]  # central
            start = spacing + s + 1
            h_a = x[start: start + len]  # after
            peak_candidate = np.logical_and(peak_candidate, np.logical_and(h_c > h_b, h_c > h_a))
        ind = np.argwhere(peak_candidate)
        ind = ind.reshape(ind.size)
        if limit is not None:
            ind = ind[data[ind] > limit]
        return ind

