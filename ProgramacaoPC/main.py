#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# Created By: P&D - Poli Cerevisiae
# Created Date: 09/08/2022
# version = 1.0

import serial
import time
import csv
import os


# Cria o arquivo CSV de acordo com as entradas
def criaCSV():
   nomeCSV = input("Insira o nome do arquivo CSV: ");
   localCSV = input("Insira o local do arquivo CSV: ");
   print("")
   print("---------------------------X-----------------------------")
   caminhoCSV = os.path.join(localCSV, nomeCSV)
   return caminhoCSV


# Cria o arduino
def arduino():
   porta = input("Insira a porta serial conectada no arduino (ex: COM5): ")
   arduino = serial.Serial(porta, 9600, timeout=0)
   return arduino


# Lê a porta serial e escreve o arquivo CSV
def leSerial(arduino):
   arduino.flushInput()
   with open(criaCSV(), "w", encoding='UTF8', newline='') as csvFile:
       writer = csv.writer(csvFile)
       writer.writerow(["Tint[ºC],Text[ºC],Umid[%]"])
       print("Tint[ºC] | Text[ºC] | Umid[%]")
       while True:
           leitura = arduino.readline().decode()
           if leitura != "":
               writer.writerow([leitura])
               print(leitura.replace(",","       "))


def main():
   print("Poli Cerevisiae - Sensor de temperatura interna, externa e de umidade")
   print("---------------------------X-----------------------------")
   print("")
   ard = arduino()
   leSerial(ard)


main()
