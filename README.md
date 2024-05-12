## CO - Dual Core Processor
**Team-Horcrux Huters**
----

Open the folder Web in the termianl and run the commands 

```
set FLASK_APP=main.py
python main.py --m flask run
```
or
```
set FLASK_APP=main.py
flask --app main run
```
And click on the URL generated.

Refer to out.txt for the ouput/memory/reg values/miss rate/IPC/CPI...

Refer out1.csv and out2.csv for Pipeline Diagrams of corresponding cores.

Cache configuration can be changed by altering the value in Cache.hpp.

## Phase - 4

Added GUI.
![WhatsApp Image 2024-05-12 at 09 58 20_7ee1b7df](https://github.com/SaiMadhavChakrala/Horcrux_Hunters_CO/assets/143097157/ea07d632-8071-4a7a-b4d3-9c7bfe38ef94)
![WhatsApp Image 2024-05-12 at 09 58 43_0180f3af](https://github.com/SaiMadhavChakrala/Horcrux_Hunters_CO/assets/143097157/0028b995-53ab-43e0-8510-bde6746f5657)


---


## Phase - 3

* 10-04-2024
Random Replacement Policy implemented for Data Forwarding

Random Replacement Policy is similar to the LRU policy. However here, instead of replacing the least accessed data which is the head of the list corresponding to the set, the data at a random location in the list is replaced.

* 08-04-2024
LRU implemented 

In each memory instruction, the corresponding index of the set for the given address is found by bit manipulation. Then the address is searched in the corersponding index. If it is not found and the corresponding set is completely filled(i.e the size of the list equals associativity), then the first element(front element of the list) which is the least accessed address is deleted and the current memory addres is appended to the list(i.e added at the back).If the required memory location is found, we find it, delete it and append it to the list again.
If the required location is found the latency of the MEM step remains the same else its latency would be updated to the miss penalty.

* 03-04-2024
Implemented Cache for memory instructions

The class Cache is declared, it is implemented by vectors of Sets. The Sets in the cache are implemented by Lists of Tags. Each list represents a Set. The idea of implementing Sets by lists will be helpful while implementing LRU policy.
The List contains an object Tag which contains value and a integer core_bit.

The core_bit represents whether the value stored is an address or a PC value. Now, at  each Read instruction of memory, if the address that is being searched is in the cache, then the latency of the instruction remains the same, else the latency of the instruction is increased and the address from the memory is stored in the cache.

Write After Write hazards and Write After Read hazards which are possible due to variable latency of the memory instructions are checked, and corresponding stalls are implemented.




Refer to out.txt for the ouput/memory/reg values

---

## Phase-2

* 09-03-2024

Added the feature the choose data forwarding to be operational or not. Some minor bugs were fixed.


* 06-03-2024
Data Forwarding

Data forwarding is implemented. In case of any data dependencies on the previous arithmetic instructions in the pipeline, if the dependency is after the execution stage of the arithmetic instruction then the data is forwarded to the instruciton which has the dependency. This is achieved by writing back at the end of the execution stage.
Similarly, if the dependency is after the memory stage of a memory instruction then the data is forwarded to the instruction which has the dependency after the memory stage.


* 05-03-2024

The functions of the pipline are extended to execute memory instructions. The location at which the memory should be accessed is calculated at the execution stage, and the data transfer occurs at the memory stage.
Jump statements are implemented. A function to remove the details of the registers of the instruction whose pipeline is flushed is implemented to avoid inaccurate hazards. Pipelining without forwarding is completed.


* 04-03-2024

A data structure is implemented to store the register details of the current instruction's preceeding four instructions to check for any data hazards. Once the vector stores four instrucitons, after the end of the pipeline of every instruction, the first element of the vector is removed.
In case of any data hazards, stalls are implemented.


* 03-03-2024
Branch Statements 

The implementation of the functions of each stage is further extended to execute branch statements as well. The output of the branch statement becomes apparent at the end of the execution stage, but there is no stall until the execution stage.
The instruciton succeeding the branch instruction is introduced to the pipeline. After the execution stage of the branch instruction, if the branch is not taken, the pipeline continues without any stalls, else the pipeline of the instruction succeeding the branch instruction is flushed and the instruction at the label is introduced to the pipeline.


* 02-03-2024
Basic Pipelining

Basic pipelining is introduced by defining functions and classes for each stage of the execution. The funcitons are called in order opposite to pipelining to ensure the accordance of execution with the timeline.
The functions are implemented to execute basic arithmetic instructions through pipelining. 


Note :
The Latency of any instruction can be changed in the   intit()  function of Core.cpp

---

## Phase-1



* 7th commit : 25-02-2024

Introduced aliases to the registers,added printing feature,some minor bugs were fixed. 

The registors of each core can now be acessessed by their aliases as well. Processing 'ecall' statetement was added to print data of the memory and the registers.





* 6th commit : 24-02-2024

Upgraded the data segement to store string values as well.

The ASCII value each character of the string is stored in one byte of the memory. After storing the last charachter of the string, the remaining bytes of the 4-byte memory element stores '0', similar to how RIPES simulator does.  





* 5th commit : 23-02-2024

Upgraded the GUI, added editors to both input files in the GUI and files can be run using GUI.Added some more branching statements




* 4th commit : 21-02-2024

Added basic data segement to store integer variables in the memory.

Defined a Class called Variable to store the name, value, address, etc of the declared variable. The values of array are stored in contiguous memory locations in the memory of the Processor.





* 3rd commit : 20-02-2024

Added GUI to represent registers of both cores. 





* 2nd commit : 18-02-2024

Implementation of JAL and J added.

J is implemented similar to previous branch statements that were implemented except the PC value is updated without any condition to check.
JAL is implemented using return address stack in which the PC value of the instruction with opcode JAL is stored before updating the current PC value to label. If another JAL instruction is read at the label before RET, it's PC value is pushed to the stack. In this way, at an RET instruction the current PC value is updated to the value at the top of the Retrun Address Stack each time.




* 1st commit : 17-02-2024

Rough initialisation of Core and Processor. Core can execute some of the commands like add, sub, lw , sw , bne, la....

Each line is split in to opcode, registers, etc. and depending upon the op code, the source and destination registers if mentioned are referenced and made changes to destination registers.
For branch statements, if the label was already declared in the previous instructions, it's PC is found using the map in which it was stored at the declaration statement. If it was not stored, then rest of the rest of the instructions are searched for the declaration of the label and after pointing it, it's PC value is stored in the map and current PC value is changed to the label's PC  value.




