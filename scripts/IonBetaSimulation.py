import math
import numpy as np
import matplotlib.pyplot as plt
import numpy.random as npr

from tqdm import tqdm

class IonBetaSimulation(object):
    """
    Class that will produce a simulation of implantation - beta decay correlation in a syncatron beam (pulsed).
    Simulation assumes implantation rate is constant and pulsed. Each implantation is independant of each other.
    Only one particular isotope is being implanted, and the implantation rate is homogeneous throughout the detector.
    
    !!! Currently no detector segmentation is accounted for & random coincidences are global all throughout the detector !!!

    !!! Simulation assumes all time units are given in seconds & Hz !!!

    !!! Simulation assumes beam onspill period starts at t=0 !!!

    Base code adapted from Johan Emil Larsson
    """

    def __init__(self, implantationRate, betaHalfLife, onspillPeriod, repetitionPeriod, verbose=False):
        """
        Class constructor
        """
        self.implantationRate   = implantationRate
        self.betaDecayRate      = math.log(2)/betaHalfLife
        self.onspillPeriod      = onspillPeriod
        self.repetitionPeriod   = repetitionPeriod
        self._offspillPeriod    = repetitionPeriod - onspillPeriod

        self._verbose           = False

    def defineTimeParameters(self, startTime, endTime, timestep, timeWindow):
        """
        Define all the time information for the simulation
        """
        self.startTime      = startTime
        self.endTime        = endTime
        self._timestep      = timestep
        self.timeWindow     = timeWindow
        
        # Define an array contning all the timestep taken in the simulation
        self.timeArray = np.arrange(self.startTime, self.endTime, self._timestep) 

    def _isOnspill(self, time):
        """
        Return true if beam is onspill at a given time
        """
        # Find where in any given cycle we are in
        cyclePosition = time % self.repetitionPeriod
        return cyclePosition < self.onspillPeriod

    def _nextImplantationTime(self, currentTime):
        """
        Find the next implantation time based on the previous time of implantation
        """
        return currentTime + npr.exponential(scale=1/self.implantationRate)

    def _getDecayTime(self, currentTime):
        """
        Find the time of beta decay for a given isotope according to lifetime.
        """
        return currentTime + npr.exponential(scale=1/self.betaDecayRate)

    def _flipSpill(self, currentTime, nextSpillChangeTime, onspillFlag):
        """
        Determine if spill flag needs to change and detemine next time for spill flag change
        """
        if onspillFlag:
            onspillFlag = False
            nextSpillChangeTime = currentTime + self._offspillPeriod
        if not onspillFlag:
            onspillFlag = True
            nextSpillChangeTime = currentTime + self._onspillPeriod

        return nextSpillChangeTime, onspillFlag
        

    def simulateImplantations(self):
        """
        Iterate through timesteps and simulate implantations and their subsequent decay time
        """
        
        # Check if time information has been provided to class instance
        if self.timeArray is None: 
            return Exception("No time information for MC Simulation has been provided. Call .defineTimeParameters() before calling this method.")

        # Define vector to hold implant times and their corresponding decay times
        self.implantMcVector = [] # Each entry is a tuple holding implant time & subsequent decay time

        nextImplantTime = -1. # Define starting time for next implant time 
        nextSpillChangeTime = self.onspillPeriod
        onspillFlag = False
        lastImplantTime = 0.

        # Define tqdm object for timestep loop
        timestepLoopCli = tqdm(self.timeArray, desc="Timestep Loop")

        # Loop over timesteps and sumilate implant occutences and their corresponding 
        for currentTime in timestepLoopCli:
            if currentTime > nextImplantTime and onspillFlag:
                nextImplantTime = self._nextImplantationTime(currentTime)
                if self._verbose:
                    print(f"current implant = {currentTime} ")
                    print(f"next implant = {nextImplantTime} ")
                betaDecayTime = self._getDecayTime(currentTime)
                self.implantMcVector.append((currentTime, betaDecayTime))
                lastImplantTime = currentTime

            if currentTime > nextSpillChangeTime: 
                nextSpillChangeTime, onspillFlag = self._flipSpill(currentTime, nextSpillChangeTime, onspillFlag)

        print(f"\nTimestep loop has terminated. {int(len(self.implantMcVector))} implants have been simulated.")

    def correlateImplantDecays(self):
        """
        Correlate implant and decays 
        """

    def getSimulatedImplants(self):
        """
        Getter for simulated implants
        """
        if self.implantMcVector is None:
            return Exception("No implants have been simulated. Run .simulateImplantations() before calling this method.")



            




        
