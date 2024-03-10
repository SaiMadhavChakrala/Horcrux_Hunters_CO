Phase-2

09-03-2024

Added the feature the choose data forwarding to be operational or not. Some minor bugs were fixed.


06-03-2024
Data Forwarding

Data forwarding is implemented. In case of any data dependencies on the previous arithmetic instructions in the pipeline, if the dependency is after the execution stage of the arithmetic instruction then the data is forwarded to the instruciton which has the dependency. This is achieved by writing back at the end of the execution stage.
Similarly, if the dependency is after the memory stage of a memory instruction then the data is forwarded to the instruction which has the dependency after the memory stage.


05-03-2024

The functions of the pipline are extended to execute memory instructions. The location at which the memory should be accessed is calculated at the execution stage, and the data transfer occurs at the memory stage.
Jump statements are implemented. A function to remove the details of the registers of the instruction whose pipeline is flushed is implemented to avoid inaccurate hazards. Pipelining without forwarding is completed.


04-03-2024

A data structure is implemented to store the register details of the current instruction's preceeding four instructions to check for any data hazards. Once the vector stores four instrucitons, after the end of the pipeline of every instruction, the first element of the vector is removed.
In case of any data hazards, stalls are implemented.


03-03-2024
Branch Statements 

The implementation of the functions of each stage is further extended to execute branch statements as well. The output of the branch statement becomes apparent at the end of the execution stage, but there is no stall until the execution stage.
The instruciton succeeding the branch instruction is introduced to the pipeline. After the execution stage of the branch instruction, if the branch is not taken, the pipeline continues without any stalls, else the pipeline of the instruction succeeding the branch instruction is flushed and the instruction at the label is introduced to the pipeline.


02-03-2024
Basic Pipelining

Basic pipelining is introduced by defining functions and classes for each stage of the execution. The funcitons are called in order opposite to pipelining to ensure the accordance of execution with the timeline.
The functions are implemented to execute basic arithmetic instructions through pipelining. 


Note :
The Latency of any instruction can be changed in the   intit()  function of Core.cpp



