# CFD_01_Heat-Convection
(Note: There's a naming error, this task is heat conduction instead of heat convection)
Instructions:  
1. Installation and Configuration of MPI in Visual Studio:  
  a) Download: https://www.microsoft.com/en-us/download/details.aspx?id=100593 (perhaps)  
  b) cd ./CFD_01_Heat-Convection-> Double clicking to open up "CFD_01_Heat-Convection.sln"  
  c) Project-> CFD_01_Heat-Convection Property(P):  
    i. C/C++-> Additional Include Directory-> Edit-> New Line-> C:\Program Files (x86)\Microsoft SDKs\MPI\Include  
    ii. Linker-> Additional Library Directories-> C:\Program Files (x86)\Microsoft SDKs\MPI\Lib\x86  
    iii. Linker-> Input-> Additional Dependenies-> Edit-> "msmpi.lib"  
2. Identify the desired mesh number N in the #define  
3. "Build" the Source.cpp so as to generate .exe file  
4. Execute the .exe file in the CLI: mpiexec -n 4 CFD_1_MPI_HW1.exe  
5. Post process the "result.csv" via "CFD_Postprocess.m".
