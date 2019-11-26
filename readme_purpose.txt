EXPERIMENTAL OVERVIEW:
   
        The High Energy Physics Group, led by Dr. Shuichi Kunori at Texas Tech University, has created a portable prototype muon ray telescope which in the experiment is used to measure the muon flux at any given angle. Our experiment concerns with the use of this telescope to create tomographical images; we point the telescope towards a Water Tower located at the Reese Technology Center and record the muon flux for a period of time. Using this data and the known behavior of muon physics, we generate a shadow image of the water tower. This image gives us information of the structural integrity of the water tower, which basically means we can infer the different materials used in the construction of the tower and the level of water inside the tower.

PURPOSE OF ARDUINO DAQ CODE:

        All the versions of the Arduino DAQ code uploaded to this directory has been implemented to our muon telescope in our development phase. The DAQ code allows the electronic data that we recieve from our telescope to be digitized and sent to our computer for storage. Using this code, we record the ADC count for each of the channels we have connected to the scintillator bars used in our detector, and the timing information of all measurements we make. This code helps us identify which signals are created by actual muons going through and what is noise. 
